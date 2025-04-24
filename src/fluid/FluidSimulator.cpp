#include "FluidSimulator.h"

#include <QtLogging>
#include <cmath>
#include <random>
#include <unordered_map>
//#include <functional>

Simulator::Simulator(int particleNums) {
	init(particleNums);
}

// ----------- 运算函数 -----------
//namespace std{
//	template<>
//	struct std::hash<glm::ivec3> {
//		size_t operator()(const glm::ivec3& v) const {
//			return std::hash<int>()(v.x) ^ std::hash<int>()(v.y) ^ std::hash<int>()(v.z);
//		}
//	};
//};
namespace {
	struct glm_ivec3_hash {
		std::size_t operator()(const glm::ivec3& v) const {
			return std::hash<int>()(v.x) ^
				   std::hash<int>()(v.y) ^
				   std::hash<int>()(v.z);
		}
	};
}


glm::ivec3 Simulator::getCell(glm::vec3 pos) {
	return glm::ivec3{
			static_cast<int>(pos.x * cellRecpr),
			static_cast<int>(pos.y * cellRecpr),
			static_cast<int>(pos.z * cellRecpr)
	};
}
int Simulator::roundUp(float val, float step) {
	return static_cast<int>(std::floor(val * cellRecpr / step + 1) * step);
}
const std::vector<Particle>& Simulator::getParticles() {
	return particles;
}
float Simulator::computeScorr(glm::vec3 pos_i, glm::vec3 pos_j) {
	float scorr = 0.0f;
	glm::vec3 s = pos_i - pos_j; // 计算粒子间的距离
	float r = glm::length(s);
	scorr = poly6Value(r, 1.1f) / poly6Value(0.33f, 1.1f); // 计算粒子压力矫正因子
	scorr = scorr * scorr * scorr * scorr;
	return scorr * (-0.001f);
}
glm::vec3 Simulator::confineParticle(glm::vec3 pos){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(0.0f, 1.0f); // 创建一个随机数生成器, 范围在0到1之间
	glm::vec3 minBound = glm::vec3(-1.0f, -1.0f, -1.0f);
	glm::vec3 maxBound = glm::vec3(1.0f, 1.0f, 1.0f);
	if(pos.x < minBound.x) pos.x = minBound.x + dis(gen);
	if(pos.y < minBound.y) pos.y = minBound.y + dis(gen);
	if(pos.z < minBound.z) pos.z = minBound.z + dis(gen);
	if(pos.x > maxBound.x) pos.x = maxBound.x - dis(gen);
	if(pos.y > maxBound.y) pos.y = maxBound.y - dis(gen);
	if(pos.z > maxBound.z) pos.z = maxBound.z - dis(gen);
	return pos;
}
bool Simulator::isInRange(const glm::ivec3 &cell) {
	return cell.x >= 0 && cell.x < gridSize.x &&
		   cell.y >= 0 && cell.y < gridSize.y &&
		   cell.z >= 0 && cell.z < gridSize.z;
}
float Simulator::poly6Value(float r, float h) { // 计算核函数
	float ret = 0.0f;
	float h2 = h * h;
	if(0 < r && r < h){
		float r2 = r * r;

		ret = 315.0f / (64.0f * M_PI * pow(h, 9)) * pow(h2 - r2, 3);
	}
	return ret;
}

// ----------- PBF -----------
void Simulator::init(int particleNums) {
	for (int i = 0; i < particleNums; i++) {
	}
}
void Simulator::runPBF() {
	prologue();
	for(int i = 1; i <= pbfNumIters; i++){
		update();
	}
	epilogue();
}
void Simulator::prologue() {

	for (auto& p : particles) {
		p.neighbour.clear(); // 清空邻居粒子
		p.oldPos = p.pos; // 备份粒子坐标
	}
	for (auto& p : particles){
		glm::vec3 g = glm::vec3(0.0f, -9.8f, 0.0f); // 重力加速度
		glm::vec3 pos_i = p.pos;
		glm::vec3 vel_i = p.vel;
		vel_i += g * dt; // 更新速度
		pos_i += vel_i * dt; // 更新位置
		p.pos = confineParticle(pos_i); // 检查粒子是否在边界内
	}
	for(auto p:particles){
		p.neighbour.clear(); // 清空邻居粒子
	}
	// 初始化网格变量
	std::unordered_map<glm::ivec3, std::vector<Particle*>, glm_ivec3_hash> gridToParticles;
	std::unordered_map<glm::ivec3, int, glm_ivec3_hash> gridToParticleCount;
	for(auto& p:particles){
		glm::ivec3 grid = getCell(p.pos); // 计算粒子所在的网格
		gridToParticles[grid].push_back(&p); // 将粒子添加到网格中
		gridToParticleCount[grid]++; // 记录网格中粒子的数量
	}
	/*
	 * 遍历所有粒子，计算粒子所在的网格，并将粒子添加到网格中
	 * 通过检查粒子所在网格与临近网格，可以以较高效率获取邻居粒子
	 */
	for(auto& p:particles){
		glm::ivec3 grid = getCell(p.pos); // 计算粒子所在的网格
		glm::vec3 pos_i = p.pos;

		for(int i = -1; i <= 1; i++){
			for(int j = -1; j <= 1; j++) {
				for (int k = -1; k <= 1; k++) {
					glm::ivec3 grid_i = grid + glm::ivec3{i, j, k}; // 遍历周边网格
					if(!isInRange(grid_i)) continue;
					for(auto J:gridToParticles[grid_i]){
						if(*J == p) continue;
						glm::vec3 pos_j = J->pos;
						float r = glm::length(pos_i - pos_j);
						if(p.neighbour.size() < maxNeighbour && r < neighbourRadius && pos_i != pos_j){ // 粒子在半径范围内，数量小于最大邻居数量，且距离小于邻居半径，则添加到邻居列表中
							p.neighbour.push_back(J);
						}
					}
				}
			}
		}
	}
}
void Simulator::update() {    // 在这里不写 while-loop，因为渲染不在这里
	/*
	* 借鉴SPH和PBF论文，考虑单个粒子的受力情况
	* 1.粒子间的作用力
	* (1) 通过粒子的密度关系，求解粒子的约束坐标
	* (2) 按照PBH算法的顺序依次计算参数并最终更新
	* 2.粒子遇到外界边界和固定物体的作用力
	* 3.不可压缩的粒子的实现
	* 4.粒子粘滞系数带来的受力
	*/
	// 计算拉格朗日乘数
	for(auto& p: particles){
		glm::vec3 pos_i = p.pos;
		glm::vec3 grad_i = glm::vec3(0.0f);
		float densityConstraint = 0.0f; // 密度约束
		float sumSqrGrad = 0.0f; // 梯度平方和
		for(auto& q: p.neighbour){
			if(q == &p) continue; // 自身不计算
			glm::vec3 pos_j = q->pos;
			glm::vec3 s = pos_i - pos_j; // 计算粒子间的距离
			float r = glm::length(s);
			float h = 1.1f; // 初始化核半径
			float poly6 = poly6Value(r, h); // 计算核函数
			float poly6Grad = -945.0f / (32.0f * M_PI * pow(h, 9)) * pow(h, 3) * pow(h - r, 2); // 计算核函数的梯度
			glm::vec3 grad = poly6Grad * s / r; // 计算梯度
			grad_i += grad; // 累加梯度
			densityConstraint += poly6; // 累加密度约束
			sumSqrGrad += glm::dot(grad, grad); // 累加梯度平方和
		}
		p.density = densityConstraint; // 更新粒子密度
		glm::vec3 grad_iNorm = glm::normalize(grad_i); // 归一化梯度
		sumSqrGrad = glm::dot(grad_iNorm, grad_iNorm); // 计算梯度平方和
		p.lambda = -1.0f * (p.density - 1.0f) / sumSqrGrad; // 计算拉格朗日乘子
	}
	// 计算粒子位置增量
	glm::vec3 posDelta = glm::vec3(0.0f);
	for(auto& p: particles){
		glm::vec3 pos_i = p.pos;
		float lambda_i = p.lambda;
		glm::vec3 grad_i = glm::vec3(0.0f);
		for(auto& q: p.neighbour){
			if(q == &p) continue; // 自身不计算
			float lambda_j = q->lambda;
			glm::vec3 pos_j = q->pos;
			// 粒子压力矫正因子
			float scorr_ij = computeScorr(pos_i, pos_j);
			posDelta += (lambda_i + lambda_j) * scorr_ij; // 计算位置增量
		}
		posDelta /= 1.0f; // 平均位置增量, 除以水的密度
		p.pos += posDelta; // 更新粒子位置
	}
}
void Simulator::epilogue() {
	for(auto& p: particles){
		auto pos = p.pos;
		p.pos = confineParticle(pos);
	}
	for(auto& p: particles){
		p.vel = (p.pos - p.oldPos) / dt;
	}
}
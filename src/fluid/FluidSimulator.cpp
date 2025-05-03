#include "FluidSimulator.h"

#include <QtLogging>
#include <cmath>
#include <random>
#include <unordered_map>
#include "Log.cpp"
//#include <functional>

Simulator::Simulator(int particleNums) {
	LOG_INFO << "FluidSimulator init";
	init(particleNums);
}

// ----------- 运算函数 -----------
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
	std::uniform_real_distribution<float> dis(0.0f, epsilon); // 创建一个随机数生成器, 范围在0到1e-5之间
	glm::vec3 minBound = glm::vec3(0, 0, 0);
	glm::vec3 maxBound = glm::vec3(boundary.x, boundary.y, boundary.z);
#ifdef DEBUG
	LOG_INFO << "Before confine particle is " << pos << ". ";
#endif
	if(pos.x < minBound.x) pos.x = minBound.x + dis(gen);
	if(pos.y < minBound.y) pos.y = minBound.y + dis(gen);
	if(pos.z < minBound.z) pos.z = minBound.z + dis(gen);
	if(pos.x > maxBound.x) pos.x = maxBound.x - dis(gen);
	if(pos.y > maxBound.y) pos.y = maxBound.y - dis(gen);
	if(pos.z > maxBound.z) pos.z = maxBound.z - dis(gen);
#ifdef DEBUG
	LOG_INFO << "After confine particle is " << pos << ". ";
#endif
	return pos;
}
bool Simulator::isInRange(const glm::ivec3 &cell) {
	return cell.x >= 0 && cell.x < gridSize.x &&
		   cell.y >= 0 && cell.y < gridSize.y &&
		   cell.z >= 0 && cell.z < gridSize.z;
}
float Simulator::poly6Value(float r, float h) { // 计算核函数
	float ret = 0.0f;
//	float h2 = h * h;
//	if(0 < r && r < h){
//		float r2 = r * r;
//
//		ret = 315.0f / (64.0f * M_PI * pow(h, 9)) * pow(h2 - r2, 3);
//	}
	float ploy6Factor = 315.0f / 64.0f / M_PI;
	if(0 < r && r < h){
		float x = (h * h - r * r) / h * h * h;
		ret = ploy6Factor * x * x * x;
	}
	return ret;
}

// ----------- PBF -----------
void Simulator::init(int particleNums) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-0.25f, 0.25f); // 创建一个随机数生成器, 范围在-0.25到0.25之间
	LOG_INFO << "FluidSimulator init";
	glm::vec3 initPos = glm::vec3(10.0f, 10.0f, 10.0f);
	LOG_INFO << "boundary = " << boundary << ", grid = " << gridSize << ", cellSize = " << cellSize << ". ";
	float CubeSize = 10.0f;
	float spacing = 1.0f;
	int numPerRow = (int)(CubeSize / spacing) + 1;
	int numPerFloor = numPerRow * numPerRow;
	for (int i = 0; i < particleNums; i++) {
		int floor = i / numPerFloor;
		int row = (i % numPerFloor) / numPerRow;
		int col = (i % numPerFloor) % numPerRow;
		glm::vec3 pos = glm::vec3(static_cast<float>(col) * spacing + dis(gen),
								  static_cast<float>(floor) * spacing + dis(gen),
								  static_cast<float>(row) * spacing + dis(gen)) + initPos;
		particles.emplace_back(pos);
	}
	LOG_INFO << "Init particle nums is " << particleNums << ". " << "Finished init.";
}
void Simulator::runPBF() {
//#ifdef DEBUG
//	LOG_INFO << "Init PBF";
//#endif
	prologue();
	for(int i = 1; i <= pbfNumIters; i++){
//#ifdef DEBUG
//		LOG_INFO << "Run PBF in " << i << " iterations.";
//#endif
		update();
	}
//#ifdef DEBUG
//	LOG_INFO << "Finished PBF.";
//#endif
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
#ifdef DEBUG
			LOG_INFO << "s is " << s;
#endif
			float r = glm::length(s);
			float h = 1.1f; // 初始化核半径
			float poly6 = poly6Value(r, h); // 计算核函数
//			float poly6Grad = -945.0f / (32.0f * M_PI * pow(h, 9)) * pow(h * h - r * r, 2) * 2.0f * r; // 计算核函数的梯度
//			glm::vec3 grad = poly6Grad * s / r; // 计算梯度
			glm::vec3 grad = spikyGradient(s, h);
			grad_i += grad; // 累加梯度
//#ifdef DEBUG
//			LOG_INFO << "grad_i is " << grad_i;
//#endif
			densityConstraint += poly6; // 累加密度约束
			sumSqrGrad += glm::dot(grad, grad); // 累加梯度平方和
//#ifdef DEBUG
//			if(std::isnan(grad_i.x)){
//				LOG_ERROR << "Unexpected nan. ";
//				LOG_ERROR << "grad_i is " << grad_i << ". And pos_i is " << pos_i << ". And pos_j is " << pos_j << ". And s is " << s << ". And r is " << r << ". And h is " << h << ". ";
//				LOG_ERROR << "grad is " << grad << ". And poly6 is " << poly6 << ". And sumSqrGrad is " << sumSqrGrad << ". ";
//				exit(1);
//			}
//			if(grad_i == glm::vec3(0.0f)){
//				LOG_WARNING << "grad_i is zero.";
//				LOG_INFO << "p neighbour number is " << p.neighbour.size() << ". ";
//				LOG_INFO << "grad_j is " <<  grad << ". S is " << s << ". And r is " << r << ". And h is " << h << ". ";
//			}
//#endif
		}
		p.density = ((mass * densityConstraint / rho) - 1.0f); // 更新粒子密度
//		glm::vec3 grad_iNorm = glm::normalize(grad_i); // 归一化梯度
//		sumSqrGrad += glm::dot(grad_iNorm, grad_iNorm); // 计算梯度平方和
		sumSqrGrad += glm::dot(grad_i, grad_i);
		p.lambda = (-1.0f * p.density) / (sumSqrGrad + lambdaEpsilon); // 计算拉格朗日乘子
//#ifdef DEBUG
//		if(std::isnan(sumSqrGrad)){
//			LOG_ERROR << "Unexpected nan. ";
//			LOG_ERROR << "grad_i is " << grad_i << ". ";
//			LOG_ERROR << "sumSqrGrad is nan.";
//			exit(1);
//		}
//		if(std::isnan(p.lambda)){
//			LOG_ERROR << "Unexpected nan. ";
//			LOG_ERROR << "mass is  " << mass << ". And density is " << p.density << ". And rho is " << rho << ". And lambdaEpsilon is " << lambdaEpsilon << ". ";
//			LOG_ERROR << "sumSqrGrad is " << sumSqrGrad << ". ";
//			exit(1);
//		}
//#endif
	}
	// 计算粒子位置增量
	for(auto& p: particles){
		glm::vec3 posDelta = glm::vec3(0.0f);
		glm::vec3 pos_i = p.pos;
		float lambda_i = p.lambda;
		glm::vec3 grad_i = glm::vec3(0.0f);
		for(auto& q: p.neighbour){
			if(q == &p) continue; // 自身不计算
			float lambda_j = q->lambda;
			glm::vec3 pos_j = q->pos;
			// 粒子压力矫正因子
			float scorr_ij = computeScorr(pos_i, pos_j);
//#ifdef DEBUG
//			LOG_INFO << "lambda_j is " << lambda_i << ". And lambda_j is " << lambda_j << ". And scorr_ij is " << scorr_ij << ".";
//			LOG_INFO << "difference of posDelta is " << (lambda_i + lambda_j) * scorr_ij << ". ";
//			if(std::isnan((lambda_i + lambda_j) * scorr_ij)){
//				LOG_ERROR << "Unexpected nan. ";
//				exit(1);
//			}
//#endif
			posDelta += (lambda_i + lambda_j + scorr_ij) * spikyGradient(pos_i - pos_j, h); // 计算位置增量
		}
//#ifdef DEBUG
//		if(posDelta.x - 0.0f < 1e-6){
//			LOG_ERROR << "posDelta is zero.";
//		}
//#endif
		posDelta /= rho; // 平均位置增量, 除以水的密度
//#ifdef DEBUG
//		LOG_WARNING << "posDelta is " << posDelta << ". " << "Finished update.";
//		if(std::isnan(posDelta.x)){
//			LOG_ERROR << "posDelta is nan.";
//			LOG_INFO << "p.pos is " << p.pos << ". And p.oldPos is " << p.oldPos << ".";
//			LOG_INFO << "p.neighbour is " << p.neighbour.size() << ". And p.density is " << p.density << ".";
//			LOG_INFO << "p.lambda is " << p.lambda << ". And lambda_i is " << lambda_i << ".";
//
//
//			exit(1);
//		}
//#endif
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

const std::vector<glm::vec3> &Simulator::getParticlePos() {
	particlePos.clear();
	for(auto& p: particles){
		particlePos.push_back(p.pos);
	}
	return particlePos;
}

glm::vec3 Simulator::spikyGradient(glm::vec3 s, float h){
	glm::vec3 ret = glm::vec3(0.0f);
	float rLength = glm::length(s);
	float spikyGradientFactor = -45.0f / M_PI;
	if(0 < rLength && rLength < h){
		float x = (h - rLength) / (h * h * h);
		float g_factor = spikyGradientFactor * x * x;
		ret = s * g_factor / rLength;
	}
	return ret;
}

glm::vec3 Simulator::getBoundingBox() {
	return boundary;
}

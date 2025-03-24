#include "FluidSimulator.h"

#include <QtLogging>

void Simulator::init(int particleNums) {
	for (int i = 0; i < particleNums; i++) {
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
	for (auto& p: particles) {// 用上一帧计算得到的加速度更新这一帧的速度
		p.vel += gravity * dt;
		// TODO: pridict position x_i* \leftarrow x_i + \Delta t v_i
	}
	std::vector<Particle>* neighbourParticles;
	for (auto& p: particles) {// 获取相邻粒子，便于计算密度和约束函数
		/*
		 * 邻居定义为小于核半径的粒子
		 * TODO:初始化核半径
		 */

	}
}
void Simulator::runPBF() {
	prologue();
	for(int i = 1; i <= pbfNumIters; i++){
		update();
	}
	epilogue();
}
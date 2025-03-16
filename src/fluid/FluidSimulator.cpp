#include "FluidSimulator.h"

#include <QtLogging>

void Simulator::init(int particleNums) {
    for(int i = 0; i < particleNums; i++) {
    }
}
void Simulator::update() { // 在这里不写 while-loop，因为渲染不在这里
    for(auto &p: particles) { // 用上一帧计算得到的加速度更新这一帧的速度
        p.vel[0] += gravity[0] * dt;
        p.vel[1] += gravity[1] * dt;
        p.vel[2] += gravity[2] * dt;
    }
    for(auto &p: particles) { // 更新粒子的受力情况
        float force[3];
        for(int i = 0; i < 3; i++) {
            force[i] = 0;
        }
        /*
         * 借鉴SPH和PBF论文，考虑单个粒子的受力情况
         * 1.粒子间的作用力
         * (1) 通过粒子的密度关系，求解粒子的约束坐标
         * 2.粒子遇到外界边界和固定物体的作用力
         * 3.不可压缩的粒子的实现
         * 4.粒子粘滞系数带来的受力
         */
    }
}
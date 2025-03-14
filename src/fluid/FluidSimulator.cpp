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

    }
}
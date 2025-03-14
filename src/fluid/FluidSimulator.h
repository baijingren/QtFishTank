#ifndef FLUID_SIMULATOR_H
#define FLUID_SIMULATOR_H

#include <QtOpenGLWidgets/QOpenGLWidget>

#include "Particle.h"

class Simulator{ // 使用拉格朗日法求粒子在每一帧的更新
    Q_OBJECT
public:
    Simulator(int ); // 初始化
    void update(); // 当更新帧时，调用该函数更新流体状态(拉格朗日法)
    void init(int particleNums); // 初始化对象
    void fluidSimulation(); // 不通过渲染器的界面更新
    void calculateDensityAndPressure(); // 计算粒子的密度和压力
    void move(); // 将计算结束的粒子移动到计算结果处
    const std::vector<Particle>& getParticles(); // 获得粒子对象
    ~Simulator(); // 销毁
private:
    int dx = 64, dy = 64, dz = 64; // 采样范围，默认64*64*64
    double dt = 0.1; // 更新时间间隔
    std::vector<Particle> particles;
    float gravity[3];
};

#endif
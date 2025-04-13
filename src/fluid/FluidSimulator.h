#ifndef FLUID_SIMULATOR_H
#define FLUID_SIMULATOR_H

#include <QtOpenGLWidgets/QOpenGLWidget>

#include "Particle.h"

class Simulator{ // 使用拉格朗日法求粒子在每一帧的更新
public:
    Simulator(int ); // 初始化
    void init(int particleNums);

    void update(); // 当更新帧时，调用该函数更新流体状态(拉格朗日法)
	void runPBF(); // 执行PBF算法
	void prologue();
	void epilogue();
	float poly6Value(float, float h); // 计算核函数
    const std::vector<Particle>& getParticles(); // 获得粒子对象
	glm::vec3 checkBoundary(glm::vec3 pos); // 检查粒子是否在边界内
    ~Simulator(); // 销毁
private:
    int dx = 64, dy = 64, dz = 64; // 采样范围，默认64*64*64
    float dt = 0.1; // 更新时间间隔
    std::vector<Particle> particles; // 粒子对象
    glm::vec3 gravity;
	int pbfNumIters = 5;
	float screenToWorldRatio = 10.0;
	float computeScorr(glm::vec3 pos_i, glm::vec3 pos_j); // 计算粒子压力矫正因子
	glm::vec3 confineParticle(glm::vec3 pos);
};

#endif
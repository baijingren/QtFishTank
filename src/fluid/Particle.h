//
// Created by jingrenbai on 25-3-14.
//

#ifndef PARTICLE_H
#define PARTICLE_H



class Particle {
public:
    float pos[3]; // 粒子位置
    float vel[3]; // 粒子速度
    float density; // 粒子密度（使用sph方法）
};



#endif //PARTICLE_H

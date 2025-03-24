//
// Created by jingrenbai on 25-3-14.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include "DataType/Vec.h"

class Particle {
public:
    Vec3f pos; // 粒子位置
    Vec3f vel; // 粒子速度
    float density; // 粒子密度（使用sph方法）
};



#endif //PARTICLE_H

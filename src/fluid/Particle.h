//
// Created by jingrenbai on 25-3-14.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>
#include <vector>

class Particle {
public:
	Particle() = default;
    glm::vec3 pos; // 粒子位置
    glm::vec3 vel; // 粒子速度
    float density; // 粒子密度（使用sph方法）
	int _h; // 最大邻居数
	std::vector<Particle*> neighbour; // 邻居粒子
	float lambda; // 拉格朗日乘子
	glm::vec3 oldPos;
	~Particle() = default;

	bool operator==(const Particle& rhs) const;
};



#endif //PARTICLE_H

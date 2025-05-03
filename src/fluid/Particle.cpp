//
// Created by jingrenbai on 25-3-14.
//

#include "Particle.h"

Particle::Particle(glm::vec3 pos, glm::vec3 vel, float density, int _h) {
	this->pos = pos;
	this->vel = vel;
	this->density = density;
	this->_h = _h;
}
bool Particle::operator==(const Particle &rhs) const {
    return pos == rhs.pos &&
		   vel == rhs.vel &&
	       density == rhs.density;
}

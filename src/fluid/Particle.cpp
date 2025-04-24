//
// Created by jingrenbai on 25-3-14.
//

#include "Particle.h"

bool Particle::operator==(const Particle &rhs) const {
    return pos == rhs.pos &&
		   vel == rhs.vel &&
	       density == rhs.density;
}

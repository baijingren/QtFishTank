#include "Ball.h"

Ball::Ball(float r, glm::vec3 position, glm::vec4 color) {

}

float Ball::getR() {
	return r;
}

glm::vec3 Ball::getPosition() {
	return position;
}

glm::vec4 Ball::getColor() {
	return color;
}

void Ball::setR(float m_r) {
	this->r = m_r;
}

void Ball::setPosition(glm::vec3 m_position) {
	this->position = m_position;
}

void Ball::setColor(glm::vec4 m_color) {
	this->color = m_color;
}

std::string Ball::getTexturePath() {
	return texturePath;
}

void Ball::setTexturePath(const std::string &m_texturePath) {
	texturePath = m_texturePath;
}

glm::vec3 Ball::getNormalVector(glm::vec3 &normal, glm::vec3 &point) {
	return glm::normalize(point - position);
}

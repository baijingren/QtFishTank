#include "Fish.h"

#include <utility>

Fish::Fish(std::string m_modelPath, glm::vec3 m_position, float m_alpha) {
	modelPath = std::move(m_modelPath);
	position = m_position;
	alpha = m_alpha;
}

std::string Fish::getModelPath() {
	return modelPath;
}

glm::vec3 Fish::getPosition() {
	return position;
}

float Fish::getAlpha() const {
	return alpha;
}

void Fish::setModelPath(const std::string& m_modelPath) {
	modelPath = m_modelPath;
}

void Fish::setPosition(glm::vec3 m_position) {
	position = m_position;
}

void Fish::setAlpha(float m_alpha) {
	alpha = m_alpha;
}

std::string Fish::getTexturePath() {
	return texturePath;
}

void Fish::setTexturePath(const std::string &m_texturePath) {
	texturePath = m_texturePath;
}
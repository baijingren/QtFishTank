#ifndef FISH_H
#define FISH_H

#include <string>
#include <glm/glm.hpp>

class Fish{
private:
	std::string modelPath;
	std::string texturePath;
	glm::vec3 position{};
	float alpha;
public:
	Fish(std::string modelPath, glm::vec3 position, float alpha);
	std::string getModelPath();
	std::string getTexturePath();
	glm::vec3 getPosition();
	[[nodiscard]] float getAlpha() const;
	void setModelPath(const std::string& m_modelPath);
	void setTexturePath(const std::string& m_texturePath);
	void setPosition(glm::vec3 m_position);
	void setAlpha(float m_alpha);
};

#endif
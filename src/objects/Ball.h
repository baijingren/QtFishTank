#ifndef BALL_H
#define BALL_H

#include <glm/glm.hpp>
#include <string>

class Ball{
private:
	float r;
	glm::vec3 position;
	glm::vec4 color;
	std::string texturePath;
public:
	Ball(float r, glm::vec3 position, glm::vec4 color);
	float getR();
	glm::vec3 getPosition();
	glm::vec4 getColor();
	std::string getTexturePath();
	void setR(float m_r);
	void setPosition(glm::vec3 m_position);
	void setColor(glm::vec4 m_color);
	void setTexturePath(const std::string& m_texturePath);
};

#endif

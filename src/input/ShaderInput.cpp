//
// Created by Jingren Bai on 25-5-1.
//

#include <fstream>
#include <sstream>
#include "ShaderInput.h"

std::string ShaderInput::readShaderFile(const std::string& path) {
	std::ifstream file(path);
	std::string shaderCode = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return shaderCode;
}
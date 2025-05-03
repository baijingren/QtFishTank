#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 v_color;

uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * vec4(position, 1.0);
    v_color = color;
} 

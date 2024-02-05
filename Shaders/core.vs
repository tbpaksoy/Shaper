#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 ourColor;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
 gl_Position = projection * view * model * vec4(aPos, 1.0);
 ourColor = color;
}
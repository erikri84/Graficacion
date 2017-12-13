#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
out vec4 color;

uniform mat4 transform;
uniform vec4 cColor;

void main() 
{
	color = cColor;
	vec4 newPos = transform * vPosition; // Mat4
	gl_Position = newPos; // Posición Principal
}
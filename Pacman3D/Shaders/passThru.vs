#version 430 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
out vec4 color;

//uniform float fAngle;
uniform mat4 transform;

void main() {
	color = vColor;
	vec4 newPos = transform * vPosition; // Mat4
	//vec4 newPos = vPosition;
	//newPos.x = newPos.x * cos(fAngle * 3.141592 / 180.0);

	gl_Position = newPos; // Posición central del programa
}
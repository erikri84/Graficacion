#version 430 core

layout (location = 0) in vec4 vPosition;

uniform mat4 mTransform;

out vec4 color;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
	gl_Position = mTransform * vPosition;
}

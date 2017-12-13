#version 430 

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

uniform mat4 mTransform;

out vec2 texCoord;
out vec4 color;

void main()
{
	vec4 newPos = vPosition;
	texCoord = vTexCoord;
	gl_Position = mTransform * newPos;
}

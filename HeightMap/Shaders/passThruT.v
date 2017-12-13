#version 430 core

out vec4 fColor;
in vec2 texCoord;

uniform sampler2D theTexture;//Variable para manejar Texturas 

void main()
{
fColor = texture(theTexture, texCoord);
}

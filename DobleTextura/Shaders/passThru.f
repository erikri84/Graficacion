#version 430 

uniform sampler2D textura0;
uniform sampler2D textura1;

out vec4 fColor;
in vec2 texCoord;

void main() 
{
   // fColor = texture(textura0, texCoord);
   fColor = texture(textura0, texCoord) * texture(textura1, texCoord);
}

#pragma once
#include <vector>
#include <string>
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>


GLuint CreateShader(GLenum eShaderType, const std::string &strShaderFile);
GLuint CreateProgram(const std::vector<GLuint> &shaderList);
void InitializeProgram(GLuint& theProgram, const std::string& strVertexShader, const std::string& strFragmentShader);
std::string loadTextFile(const std::string& filename);


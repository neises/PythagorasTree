#ifndef SHADER_H
#define SHADER_H

#include <GL\glew.h>
#include <iostream>

#include <fstream>
#include <streambuf>
#include <string>
#include <cerrno>

namespace RTR
{
	enum SHADERTYPE
	{
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Geometry = GL_GEOMETRY_SHADER
	};

class Shader
{
public:
	Shader(RTR::SHADERTYPE shadertye, std::string const &filename);
	~Shader();
	const GLuint getID() const;
private:
	GLuint m_shaderID;
};
}


#endif
#include "Shaderprogram.h"

#include <iostream>
#include <GL\glew.h>
#include <assert.h>

using namespace RTR;

Shaderprogram::Shaderprogram()
{
	m_programID = glCreateProgram();
}
Shaderprogram::~Shaderprogram()
{
	glDeleteProgram(m_programID);
}

void Shaderprogram::attachShader(Shader shader)
{
	glAttachShader(m_programID,shader.getID());
}

void Shaderprogram::linkShader()
{
	glLinkProgram(m_programID);
	GLint status;
	glGetProgramiv(m_programID,GL_LINK_STATUS,&status);
	if(status != GL_TRUE)
	{
		GLint infoLenght;
		glGetProgramiv(m_programID,GL_INFO_LOG_LENGTH,&infoLenght);
		GLchar* buf = new GLchar[infoLenght];

		GLsizei bufferSize;
		glGetProgramInfoLog(m_programID,infoLenght,&bufferSize,buf);
		std::cout << buf << std::endl;
		delete[] buf;
	}
}

void Shaderprogram::useProgram()
{
	glUseProgram(m_programID);
}
const GLuint Shaderprogram::getID() const
{
	return m_programID;
}

void Shaderprogram::setTransfromFeedbackvaryings(const GLchar** varyings)
{
	glTransformFeedbackVaryings(m_programID, 3, varyings, GL_INTERLEAVED_ATTRIBS);

}

GLint Shaderprogram::getAttributLocation(std::string name)
{
	return glGetAttribLocation(m_programID,name.c_str());
}

void Shaderprogram::setUniform(GLint location, glm::mat3 const &value)
{
	glUseProgram(m_programID);
	glUniformMatrix3fv(location, 1, false, (GLfloat*) &value);
}

void Shaderprogram::setUniform(GLint location, glm::mat4 const &value)
{
	glUseProgram(m_programID);
	glUniformMatrix4fv(location, 1, false, (GLfloat*) &value);
}
GLint Shaderprogram::getUniformLocation(std::string uniformName)
{
	return glGetUniformLocation(m_programID, uniformName.c_str());
}


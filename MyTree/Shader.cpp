#include "Shader.h"

using namespace RTR;

Shader::Shader(SHADERTYPE shadertye, std::string const &filename)
{
	if(filename.c_str()<0)
		printf("ERROR: Reading Shaderfile");

	std::ifstream in(filename.c_str());
	std::string shadersource((std::istreambuf_iterator<char>(in)),std::istreambuf_iterator<char>());
	const char* tmpSource = (char*)shadersource.c_str();

	m_shaderID = glCreateShader(shadertye);
	glShaderSource(m_shaderID,1,&tmpSource,NULL);
	glCompileShader(m_shaderID);

	GLint status;
	glGetShaderiv(m_shaderID,GL_COMPILE_STATUS,&status);
	
	if(status == GL_FALSE)
	{
		char buf[1024];
		fprintf (stderr, "ERROR: GL shader index %i did not compile\n", m_shaderID);
		glGetShaderInfoLog(m_shaderID,1024,nullptr,buf);
		printf("shader compiler %s",buf);
		glDeleteShader(m_shaderID);
	}
	
}
Shader::~Shader()
{
	glDeleteShader(m_shaderID);
}

const GLuint Shader::getID() const
{
	return m_shaderID;
}
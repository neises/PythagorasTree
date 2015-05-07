#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "Shader.h"
#include <iostream>
#include <vector>
#include "glm\glm.hpp"
#include "math_helper.h"

namespace RTR
{
	class Shaderprogram
	{
	public:
		Shaderprogram();
		~Shaderprogram();

		void attachShader(Shader shader);
		void useProgram();
		void linkShader();
		void setTransfromFeedbackvaryings(const char** varyings);
		GLint getAttributLocation(std::string name);
		GLint getUniformLocation(std::string uniformName);
		const GLuint getID() const;

		void setUniform(GLint location, glm::mat3 const &value);
		void setUniform(GLint location, glm::mat4 const &value);

		template <class T>
		void setUniform(std::string uniformName, T &t)
		{
			GLint uniformLocation = getUniformLocation(uniformName);
			setUniform(uniformLocation, t);
		}

	private:
		GLuint m_programID;
	};

}



#endif
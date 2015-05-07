#ifndef BUFFER_H
#define BUFFER_H

#include "GL\glew.h"

namespace RTR
{
	class Buffer
	{
	public:
		Buffer(GLenum target);
		~Buffer();
		void bindBuffer();
		void unbindBuffer();
		void bufferDataDraw(GLsizeiptr size, const GLvoid *data);
		void bufferDataRead(GLsizeiptr size, const GLvoid *data);
		void subData(GLsizeiptr size, const GLvoid * data);
		GLuint getBuffer();
		void EnableVertexAttribArray(GLint index);
		void VertexAttribPointer(GLint index, GLint size, GLsizei strider, const GLvoid* pointer);

		void beginTransformFeedback();
		void endTransformFeedback();

	private:
		GLuint m_buffer;
		GLenum m_target;
	};

}

#endif // BUFFER_H

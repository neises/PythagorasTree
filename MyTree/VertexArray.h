#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <GL/glew.h>
#include "buffer.h"

class VertexArray
{
public:
	VertexArray();
	VertexArray(GLsizei n, GLuint * arrays); 
	~VertexArray();
	void bind();
	void unbind();
	void bindBuffer(GLuint buffer);
	void enableVertexAttribArray(GLuint index);
	void vertexAttribPointer(GLuint index, GLint size,  GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
private:
	GLuint m_vertexArray;
};

#endif // VERTEXARRAY_H
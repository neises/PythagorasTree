#include "vertexarray.h"

#include "buffer.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_vertexArray);
}

VertexArray::VertexArray(GLsizei n, GLuint* arrays)
{
	glGenVertexArrays(n,arrays);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_vertexArray);
}

void VertexArray::bind()
{
	glBindVertexArray(m_vertexArray);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}

void VertexArray::enableVertexAttribArray(GLuint index)
{
	glEnableVertexAttribArray(index);
}

void VertexArray::vertexAttribPointer(GLuint index, GLint size,  GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
{
	glVertexAttribPointer(index, size,type,normalized,stride,pointer);
}

void VertexArray::bindBuffer(GLuint buffer)
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}
#include "Buffer.h"
#include "assert.h"
#include <iostream>
#include <string>

using namespace RTR;

Buffer::Buffer(GLenum target) : m_target(target)
{
	glGenBuffers(1, (GLuint*) &m_buffer);
}
Buffer::~Buffer()
{
	glDeleteBuffers(1, (GLuint*) &m_buffer);
}

void Buffer::bindBuffer()
{
	glBindBuffer(m_target, m_buffer);
}

void Buffer::unbindBuffer()
{
	glBindBuffer(m_target, 0);
}

void Buffer::bufferDataDraw(GLsizeiptr size, const GLvoid *data)
{
	glBufferData(m_target, size, data, GL_STATIC_DRAW);
}

void Buffer::bufferDataRead(GLsizeiptr size, const GLvoid *data)
{
	glBufferData(m_target, size, data, GL_STATIC_READ);
}

void Buffer::subData(GLsizeiptr size, const GLvoid * data)
{

	glBufferSubData(m_target, 0, size, data);

}

GLuint Buffer::getBuffer()
{
	return m_buffer;
}

void Buffer::EnableVertexAttribArray(GLint index)
{
	glEnableVertexAttribArray(index);
}

void Buffer::VertexAttribPointer(GLint index, GLint size, GLsizei strider, const GLvoid* pointer)
{
	glVertexAttribPointer(index,size,GL_FLOAT,GL_FALSE, strider, pointer);
}



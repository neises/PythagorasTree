#include "GL\glew.h";
#include "GLFW\glfw3.h";
#include <stdio.h>
#include "math_helper.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "glm\ext.hpp"
#include "glm\glm.hpp"
#include "Shader.h"
#include "Shaderprogram.h"
#include "Buffer.h"
#include "VertexArray.h"


using namespace RTR;

int g_glWidth = 640;
int g_glHeight = 480;

struct vertexData
{
	float vertexPoints[3];
	float vertexNormal[3];
}vertexData;

struct treeVertex {
	glm::vec3 position;
	float length;
	glm::vec3 normal;

	treeVertex(float x, float y, float z, float length)
	{
		position = glm::vec3(x,y,z);
		this->length = length;
		this->normal = glm::vec3(0.0f, 1.0f, 0.0f);
	}
};

int nTriangles(int numberOfIterations);
int nVertices(int numberOfIterations);

int main()
{
	/* create a Window where we can print our scene*/
	GLFWwindow* window = NULL;

	/* just for the report*/
	const GLubyte* renderer;
	/* just for the report*/
	const GLubyte* version;

	/* shaders */
	GLuint vs,fs,gs;
	/* shader program*/
	GLuint shader_programm;

	/* a vertex array object, we will use it later*/
	GLuint vao;
	/* a vertex buffer object, we will use it later*/
	GLuint vbo;
	/* another vertex buffer object, we will use it later*/
	GLuint vbo_color;


	if(!glfwInit())
	{
		fprintf(stderr,"ERROR: Could not start GLfw");
		return 1;
	}

	/* we are goint to use opengl 4.1*/
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* bring up our window*/
	window = glfwCreateWindow (g_glWidth, g_glHeight, "My Tree", NULL, NULL);

	if (!window) {
		fprintf (stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent (window);
	/* start GLEW extension handler */
	glewExperimental = GL_TRUE;
	glewInit ();

	/* get version info */
	renderer = glGetString (GL_RENDERER); /* get renderer string */
	version = glGetString (GL_VERSION); /* version as a string */
	printf ("Renderer: %s\n", renderer);
	printf ("OpenGL version supported %s\n", version);



	/* vertex buffer object is created here in order to save 
	the data on graphic cards memory*/
	Shader vertexShader(RTR::Vertex,"shader\\tree.vert");
	Shader geometryShader(RTR::Geometry,"shader\\tree.geo");
	Shaderprogram geoProgram;
	geoProgram.attachShader(vertexShader);
	geoProgram.attachShader(geometryShader);

	const GLchar* varyings[] = {"out_position","out_length","out_normal"};

	geoProgram.setTransfromFeedbackvaryings(varyings);
	geoProgram.linkShader();
	geoProgram.detatchShaders();
	

	Shader renderVertexShader(RTR::Vertex,"shader\\render.vert");
	Shader renderFragmentShader(RTR::Fragment,"shader\\render.frag");
	Shaderprogram renderProgram;
	renderProgram.attachShader(renderVertexShader);
	renderProgram.attachShader(renderFragmentShader);
	renderProgram.linkShader();

	Buffer triangleVertexBuffer(GL_ARRAY_BUFFER);
	Buffer transformFeedbackBufferA(GL_ARRAY_BUFFER);


	float scl = 4.0f;
	float length = 4.f;
//	treeVertex data[3] = {
//		treeVertex(-1.0f*scl,0.0f*scl,-1.0f*scl, length*scl),
//		treeVertex(1.0f*scl,0.0f*scl,-1.0f*scl, length*scl),
//		treeVertex(0.0f*scl,0.0f*scl,1.0f*scl, length*scl)};

	float a = 6.0f;
	float h = std::sqrt(3) * a * 0.5f;

	float halfA = a*0.5f;

	treeVertex data[3] = {
		treeVertex(-halfA	,0.0f	,0.0f	, length*scl),
		treeVertex(halfA	,0.0f	,0.0f	, length*scl),
		treeVertex(0.0f		,0.0f	,h		, length*scl)};

	int numberOfIterations = 6;

	std::cout << "nVertices( " << numberOfIterations << " ) = " << nVertices(numberOfIterations) << std::endl;

	triangleVertexBuffer.bufferDataStaticRead(sizeof(treeVertex) * nVertices(numberOfIterations), nullptr);
	transformFeedbackBufferA.bufferDataStaticRead(sizeof(treeVertex) * nVertices(numberOfIterations), nullptr);

	triangleVertexBuffer.subData(sizeof(data), data);


	VertexArray genVertexArray;
	GLint position_location = geoProgram.getAttributLocation("position");
	GLint length_location = geoProgram.getAttributLocation("length");
	GLint normal_location = geoProgram.getAttributLocation("normal");
	genVertexArray.enableVertexAttribArray(0);
	genVertexArray.enableVertexAttribArray(1);
	genVertexArray.enableVertexAttribArray(2);
	genVertexArray.vertexAttribPointer(triangleVertexBuffer, position_location, 3, GL_FLOAT, GL_FALSE, sizeof(treeVertex), (GLvoid*) offsetof(treeVertex, position));
	genVertexArray.vertexAttribPointer(triangleVertexBuffer, length_location, 1,  GL_FLOAT, GL_FALSE, sizeof(treeVertex), (GLvoid*) offsetof(treeVertex, length));
	genVertexArray.vertexAttribPointer(triangleVertexBuffer, normal_location, 3, GL_FLOAT, GL_FALSE, sizeof(treeVertex), (GLvoid*) offsetof(treeVertex, normal));

	VertexArray renderVertexArray;
	GLint renderPosition_location = geoProgram.getAttributLocation("position");
	GLint renderLength_location = geoProgram.getAttributLocation("length");
	GLint renderNormal_location = geoProgram.getAttributLocation("normal");
	renderVertexArray.enableVertexAttribArray(0);
	renderVertexArray.enableVertexAttribArray(1);
	renderVertexArray.enableVertexAttribArray(2);
	renderVertexArray.vertexAttribPointer(transformFeedbackBufferA, renderPosition_location, 3, GL_FLOAT, GL_FALSE, sizeof(treeVertex), (GLvoid*) offsetof(treeVertex, position));
	renderVertexArray.vertexAttribPointer(transformFeedbackBufferA, renderLength_location, 1, GL_FLOAT, GL_FALSE, sizeof(treeVertex), (GLvoid*) offsetof(treeVertex, length));
	renderVertexArray.vertexAttribPointer(transformFeedbackBufferA, renderNormal_location, 3, GL_FLOAT, GL_FALSE, sizeof(treeVertex), (GLvoid*) offsetof(treeVertex, normal));

	VertexArray* currentVertexArray = &genVertexArray;
	Buffer* currentTransformFeedbackBuffer = &transformFeedbackBufferA;

	VertexArray* lastVertexArray = &renderVertexArray;
	Buffer* lastTransformFeedbackBuffer = &triangleVertexBuffer;


	//Was vor den Passes in data[] liegt:
	std::cout << "Inhalt des data[] arrays." << std::endl;
	for(int i = 0; i < 3; i++) {
		int vertexStart = i * 4;
		std::cout << "Vertex " << i << "\t:("
					 << ((float*)data)[vertexStart+0] << "\t, "
					 << ((float*)data)[vertexStart+1] << "\t, "
					 << ((float*)data)[vertexStart+2] <<  "\t)\tlength = "
					 << ((float*)data)[vertexStart+3] << std::endl;
	}
	std::cout << "-----------------------------------" << std::endl;


	//Was vor den Passes im Array liegt:
	std::cout << "Inhalt des Buffers vor dem ersten Pass:" << std::endl;
	triangleVertexBuffer.bindBuffer();
	GLfloat feedback[20];
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(feedback), feedback);
	triangleVertexBuffer.unbindBuffer();
	for(int i = 0; i < nVertices(0); i++) {
		int vertexStart = i * 4;
		std::cout << "Vertex " << i << "\t:("
					 << feedback[vertexStart+0] << "\t, "
					 << feedback[vertexStart+1] << "\t, "
					 << feedback[vertexStart+2] <<  "\t)\tlength = "
					 << feedback[vertexStart+3] << std::endl;
	}
	std::cout << "-----------------------------------" << std::endl;


	for(int pass = 0; pass < numberOfIterations; pass++) {
		currentVertexArray->bind(); //das VertexArray weiß selbst aus welchem Buffer es die Daten lesen soll.
		geoProgram.useProgram();

		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, currentTransformFeedbackBuffer->getBuffer());
		glBeginTransformFeedback(GL_TRIANGLES);
		int n = nVertices(pass);
		//glDrawArrays(GL_TRIANGLES, 0, n);

		glEndTransformFeedback();
		glFlush();
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, 0);

		currentTransformFeedbackBuffer->bindBuffer();
		/*
		GLfloat feedback[20];
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(feedback), feedback);
		currentTransformFeedbackBuffer->unbindBuffer();

		std::cout << "Inhalt des Buffers nach dem " << pass+1 << "ten pass:" << std::endl;
		for(int i = 0; i < nVertices(pass+1); i++) {
			int vertexStart = i * 7;
			std::cout << "Vertex " << i << "\t:("
						 << feedback[vertexStart+0] << "\t, "
						 << feedback[vertexStart+1] << "\t, "
						 << feedback[vertexStart+2] << "\t)\tlength = "
						 << feedback[vertexStart+3] << "\t normal( "
						 << feedback[vertexStart+4] << ", "
						 << feedback[vertexStart+5] << ", "
						 << feedback[vertexStart+6] << " )"
						 << std::endl;
		}
		std::cout << "-----------------------------------" << std::endl;
		*/
		geoProgram.unuseShader();

		currentVertexArray->unbind();

		//Buffer und Vertexarrays durchtauschen
		VertexArray* swapVertexArray = currentVertexArray;
		Buffer* swapTransformFeedbackBuffer = currentTransformFeedbackBuffer;
		currentVertexArray = lastVertexArray;
		currentTransformFeedbackBuffer = lastTransformFeedbackBuffer;
		lastVertexArray = swapVertexArray;
		lastTransformFeedbackBuffer = swapTransformFeedbackBuffer;
	}



	glEnable(GL_DEPTH_TEST); /*enable depth testing*/
	glDepthFunc(GL_LESS); /* depth-testing interprets a smaller value*/
	glClearColor(1.0f,1.0f,1.0f,0.0f);

	glm::dvec2 mouseDelta;
	glm::vec3 cameraPosition(0, 0, 250);

	float modelRotaitonX = 0.0f;
	float modelRotationY = 0.0f;

	while(!glfwWindowShouldClose(window))
	{

//Update
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwGetWindowSize(window, &g_glWidth, &g_glWidth);

		glm::dvec2 mousePosition;
				glfwGetCursorPos(window, &mousePosition.x, &mousePosition.y);
				mouseDelta = mousePosition;
				glfwSetCursorPos(window, 0.0, 0.0);

		if(mouseDelta.x != 0 || mouseDelta.y != 0 ) {
			std::cout <<"mp("<<mousePosition.x<<", "<<mousePosition.y<<")" <<std::endl<< "MouseX: " << mouseDelta.x << "  MouseY: " << mouseDelta.y << std::endl;
		}

		//Model Matix
		glm::mat4 model  = glm::mat4(1.0f);
		modelRotaitonX += mouseDelta.y * 0.01;
		modelRotationY += mouseDelta.x * 0.01;
		model = glm::rotate(model, modelRotaitonX, glm::vec3(1.0f,0.0f,0.0f));
		model = glm::rotate(model, modelRotationY, glm::vec3(0.0f,1.0f,0.0f));

		//View Matrix
		glm::mat4 view = glm::lookAt(
					cameraPosition,
					glm::vec3(0.0f,0.0f,0.0f), // and looks at the origin
					glm::vec3(0,1,0)
					);

		glm::mat4 projection = glm::perspective(
					50.f,
					(float) g_glWidth / (float)g_glWidth,
					0.1f,
					10000.0f
					);

		glm::mat4 MVP	= projection * view * model;
		glm::mat4 M	= model;
		glm::vec3 lightPosition(10.f ,13.f, 30.f);

		renderProgram.setUniform(std::string("MVP"), MVP);
		renderProgram.setUniform(std::string("M"), M);
		renderProgram.setUniform(std::string("lightposition"), lightPosition);

		//RENDER:
		currentVertexArray->bind();
		renderProgram.useProgram();

		glDrawArrays(GL_TRIANGLES, 0, nVertices(numberOfIterations));

		renderProgram.unuseShader();
		currentVertexArray->unbind();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);

	}

	glfwTerminate();
	return 0;
}

int nTriangles(int numberOfIterations) {
	assert (numberOfIterations >= 0);
	return 4*std::pow(3,numberOfIterations) - 3;
}

int nVertices(int numberOfIterations) {
	return nTriangles(numberOfIterations) * 3;
}
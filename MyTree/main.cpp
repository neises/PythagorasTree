#include "GL\glew.h";
#include "GLFW\glfw3.h";
#include <stdio.h>
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


struct testStruct
{
	glm::vec3 position;
	testStruct(float x, float y , float z)
	{
		position = glm::vec3(x,y,z);
	}
};

/* a struct which contains the positions, length and the normals */
/* tip Rezk-Salama*/
struct testStruct2
{
	glm::vec3 position;
	float _length;
	glm::vec3 normal;
	testStruct2(float x, float y , float z,float length)
	{
		position = glm::vec3(x,y,z);
		_length = length;
		this->normal = glm::vec3(0.0f,1.0f,0.0f);
	}
};

int g_numberofIteration = 10;
int g_numberofVertices = 0;
int g_numberofTriangles = 0;

/* returns the number of triangles */
int countofTriangles(int numberOfIterations) {
	return 4*std::pow(3,numberOfIterations) - 3;
}
/* returns the number of vertices used */
void countofVertices(int numberOfIterations) {
	g_numberofTriangles = countofTriangles(numberOfIterations);
	g_numberofVertices = g_numberofTriangles* 3;
}



int main()
{
	/* create a Window where we can print our scene*/
	GLFWwindow* window = NULL;
	const GLubyte *renderer;
	const GLubyte *version;

	/* if something went wrong -> exit!*/
	if(!glfwInit())
	{
		fprintf(stderr,"ERROR: Could not start GLfw");
		return 1;
	}

	/* we are goint to use opengl 4.2*/
	glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 2);
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

	
	/* shader for vert/teststruct1 */
	/*
	Shader renderVertexShader(RTR::Vertex,"shader\\testRender.vert");
	Shader renderFragmentShader(RTR::Fragment,"shader\\testRender.frag");
	Shaderprogram renderProgram;
	renderProgram.attachShader(renderVertexShader);
	renderProgram.attachShader(renderFragmentShader);
	renderProgram.linkShader();
	*/

	/*shader for vert2/teststruct2 and rendering*/
	Shader renderVertexShader(RTR::Vertex,"shader\\teststruct2Render.vert");
	Shader renderFragmentShader(RTR::Fragment,"shader\\teststruct2Render.frag");
	Shaderprogram renderProgram;
	renderProgram.attachShader(renderVertexShader);
	renderProgram.attachShader(renderFragmentShader);
	renderProgram.linkShader();

	/*shader for geometry */	
	Shader geoVertexShader(RTR::Vertex,"shader\\tree.vert");
	Shader geoGeometyShader(RTR::Geometry,"shader\\tree.geo");
	Shaderprogram geoProgram;
	geoProgram.attachShader(geoVertexShader);
	geoProgram.attachShader(geoGeometyShader);
	
	/* our value we want to know from the pipeline */
	const GLchar* varyings[] = {"out_position","out_length","out_normal"};
	geoProgram.setTransfromFeedbackvaryings(varyings);
	geoProgram.linkShader();
	
	/*
	testStruct vert[]=
	{
		testStruct(+0.0f, +1.0f, 0.0f),
		testStruct(-1.0f, -1.0f, 0.0f),
		testStruct(+1.0f, -1.0f, 0.0f)
	};
	*/
	testStruct2 vert2[]= 
	{
		testStruct2(+0.0f, +0.5f, 0.0f,1.0f),
		testStruct2(-0.5f, -0.5f, 0.0f,1.0f),
		testStruct2(+0.5f, -0.5f, 0.0f,1.0f)

	};
	/* buffer für vert*/
	/*
	Buffer mybuffer(GL_ARRAY_BUFFER);
	mybuffer.bindBuffer();
	mybuffer.bufferDataStaticDraw(sizeof(vert),vert);
	*/


	/* calculate the number of vertices */
	countofVertices(g_numberofIteration);


	/*generate buffers for triangle */
	Buffer mybufferTriangle(GL_ARRAY_BUFFER);
	mybufferTriangle.bindBuffer();
	mybufferTriangle.bufferDataDraw(sizeof(vert2)*g_numberofVertices,nullptr);
	mybufferTriangle.subData(sizeof(vert2),vert2);
	
	
	/* create a vertex array object */
	VertexArray vertexArr;
	vertexArr.bind();
	vertexArr.bindBuffer(mybufferTriangle.getBuffer());
	GLint pos = geoProgram.getAttributLocation("position");
	vertexArr.enableVertexAttribArray(pos);
	vertexArr.vertexAttribPointer(pos,3,GL_FLOAT,GL_FALSE, sizeof(float)*7,0);
	GLint length = geoProgram.getAttributLocation("length");
	vertexArr.enableVertexAttribArray(length);
	vertexArr.vertexAttribPointer(length,1,GL_FLOAT,GL_FALSE,sizeof(float)*7,(void*)(sizeof(float)*3));
	//vertexArr.vertexAttribPointer(1,1,GL_FLOAT,GL_FALSE,sizeof(float)*4,(void*)offsetof(testStruct2,_length));
	GLint normal = geoProgram.getAttributLocation("normal");
	vertexArr.enableVertexAttribArray(normal);
	vertexArr.vertexAttribPointer(normal,3,GL_FLOAT,GL_FALSE,sizeof(float)*7,(void*)(sizeof(float)*4));
	
	/* create a buffer for the transform feedback */
	Buffer mybufferFeedback(GL_ARRAY_BUFFER);
	mybufferFeedback.bindBuffer();
	mybufferFeedback.bufferDataRead(sizeof(vert2)*g_numberofVertices,nullptr);
	//mybufferFeedback.unbindBuffer();
	
	

	/* another vertexarray */
	/* it represents another vertexarrayobject where we store the vertecies we recieve form the transformfeedbackbuffer */
	/* later we will use it to draw */
	VertexArray renderVertex;
	renderVertex.bind();
	renderVertex.bindBuffer(mybufferFeedback.getBuffer());
	GLint renderpos = renderProgram.getAttributLocation("position");
	renderVertex.enableVertexAttribArray(renderpos);
	renderVertex.vertexAttribPointer(renderpos,3,GL_FLOAT,GL_FALSE,sizeof(float)*7,0);
	GLint renderlength = renderProgram.getAttributLocation("length");
	renderVertex.enableVertexAttribArray(renderlength);
	renderVertex.vertexAttribPointer(renderlength,1,GL_FLOAT,GL_FALSE,sizeof(float)*7,(void*)(sizeof(float)*3));
	GLint rendernormal = renderProgram.getAttributLocation("normal");
	renderVertex.enableVertexAttribArray(rendernormal);
	renderVertex.vertexAttribPointer(rendernormal,3,GL_FLOAT,GL_FALSE,sizeof(float)*7,(void*)(sizeof(float)*4));
	
	/* set a pointer of our vertexArr and our buffer for swapping them later */

	std::cout << &vertexArr << std::endl;
	VertexArray *currentVertexArray; 
	currentVertexArray= &vertexArr;
	std::cout << &mybufferFeedback << std::endl;
	Buffer *currentFeedbackbuffer = &mybufferFeedback;
	
	std::cout << &renderVertex << std::endl;
	VertexArray *lastVertexArray = &renderVertex;
	std::cout << &mybufferTriangle << std::endl;
	Buffer *lastFeedbackbuffer = &mybufferTriangle;
	
	/* loop through the iterations and build the tree */
	for(int i = 0; i < g_numberofIteration;++i)
	{
		currentVertexArray->bind();
		geoProgram.useProgram();
		currentFeedbackbuffer->bindBuffer();
		glEnable(GL_RASTERIZER_DISCARD);
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER,0,currentFeedbackbuffer->getBuffer());
		glBeginTransformFeedback(GL_TRIANGLES);
			glDrawArrays(GL_TRIANGLES,0,g_numberofVertices);
		glEndTransformFeedback();
		glDisable(GL_RASTERIZER_DISCARD);
		glFlush();

		/* after this we swap the vertexArray to fill the new vertexArray with the new verticies we recieved*/
		VertexArray *swapVertexArray = currentVertexArray;
		currentVertexArray = lastVertexArray;
		lastVertexArray = swapVertexArray;

		/* buffer to swap */
		Buffer *swapFeedbackBuffer = currentFeedbackbuffer;
		currentFeedbackbuffer = lastFeedbackbuffer;
		lastFeedbackbuffer = swapFeedbackBuffer;	

	}
	
	/* clear Color */
	glClearColor(0.5f,0.2f,0.3f,0.0f);

	/* camara Position */
	glm::vec3 camaraPos(0,0,50);

	float rotationX = 0.0f;
	float rotationY = 0.0f;
	float aspect = (float)g_glWidth/(float)g_glHeight;
	while(!glfwWindowShouldClose(window))
	{
			
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		static double previous_seconds = glfwGetTime ();
		double current_seconds = glfwGetTime ();
		double elapsed_seconds = current_seconds - previous_seconds;
		previous_seconds = current_seconds;
	
		renderVertex.bind();
		renderProgram.useProgram();

		glDrawArrays(GL_TRIANGLES, 0, g_numberofVertices);
		glfwPollEvents ();
	
		glfwSwapBuffers(window);
		if(GLFW_PRESS == glfwGetKey(window,GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(window,1);
		if(glfwGetKey(window,GLFW_KEY_W))
			camaraPos.z += -10.0f * elapsed_seconds;
		if(glfwGetKey(window,GLFW_KEY_S))
			camaraPos.z += 10.0f * elapsed_seconds;
		if(glfwGetKey(window,GLFW_KEY_A))
			rotationX += 10.f * elapsed_seconds;
		if(glfwGetKey(window,GLFW_KEY_D))
			rotationX -= 10.f * elapsed_seconds;
		if(glfwGetKey(window,GLFW_KEY_E))
			rotationY = +1.f * elapsed_seconds;
		if(glfwGetKey(window,GLFW_KEY_Q))
			rotationY = -1.f * elapsed_seconds;

		// modelmatrix
		glm::mat4 tree = glm::mat4(1.0f);
		tree = glm::rotate(tree, rotationX, glm::vec3(1.0f,0.0f,0.0f));
		tree = glm::rotate(tree, rotationY, glm::vec3(0.0f,1.0f,0.0f));

		//viewmatrix
		glm::mat4 view = glm::lookAt(camaraPos,glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));

		//perspektive
		glm::mat4 proj = glm::perspective(50.0f,aspect,0.1f,100.0f);

		
		//setunifrom´s matrix
		GLint treei = renderProgram.getUniformLocation("model");
		renderProgram.setUniform("model",tree);
		GLint viewi = renderProgram.getUniformLocation("view");
		renderProgram.setUniform("view",view);
		GLint proji = renderProgram.getUniformLocation("proj");
		renderProgram.setUniform("proj",proj);


		/* Poll for and process events */
	}

	glfwTerminate();
	return 0;
}

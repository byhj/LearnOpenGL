#include <common/learnApp.h>
#include <common/shader.h>
#include <iostream>

class RectangleApp: public byhj::Application
{
public:
	RectangleApp(): program(0), vao(0), vbo(0), ibo(0) { }
	~RectangleApp() {}

public:
	void v_Init()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		init_shader();
		init_buffer();
		init_vertexArray();
	}

	void v_Render()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);
		glBindVertexArray(vao);

		//We set the display mode is line
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUseProgram(0);
		glBindVertexArray(0);
	}
	void v_Shutdown()
	{
		glDeleteProgram(program);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ibo);
	}

private:
	void init_buffer();
	void init_shader();
	void init_vertexArray();

	GLuint vbo, vao, ibo, program;
	Shader RectangleShader;
};

CALL_MAIN(RectangleApp);

//////////////////////////Data///////////////////////////
const static GLfloat VertexData[] = 
{
	-0.5f, -0.5f,
	 0.5f, -0.5f,
	 0.5f,  0.5f,
	-0.5f,  0.5f,
};
const static GLsizei VertexSize = sizeof(VertexData);

const static GLuint IndexData[] = 
{
	0, 1, 2,
	2, 3, 0,
};
const static GLsizei IndexSize = sizeof(IndexData);

//////////////////////////Data////////////////////////////


void RectangleApp::init_shader()
{
	RectangleShader.init();
	RectangleShader.attach(GL_VERTEX_SHADER, "rectangle.vert");
	RectangleShader.attach(GL_FRAGMENT_SHADER, "rectangle.frag");
	RectangleShader.link();
	RectangleShader.interfaceInfo();
	program = RectangleShader.GetProgram();
}

void RectangleApp::init_buffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);    //load the vertex data
	glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);    //load the vertex data
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexSize, IndexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void RectangleApp::init_vertexArray()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);   //bind the vbo to vao, send the data to shader
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
}

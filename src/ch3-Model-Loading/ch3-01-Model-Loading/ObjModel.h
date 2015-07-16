#ifndef OBJMODEL_H
#define OBJMODEL_H

#include "ogl/oglShader.h"
#include "ogl/oglUtility.h"
#include "ogl/model.h"

namespace  byhj
{

class ObjModel
{
public:
	ObjModel() {}
	~ObjModel() {}

public:
	void Init();
	void Render(const byhj::MvpMatrix matrix);
	void Shutdown();

private:
	void init_shader();
	void init_buffer();

	GLuint program;
	GLuint model_loc ,view_loc, proj_loc;
	GLuint ambient_loc, diffuse_loc, specular_loc;

	OGLShader CubeShader;		
	OGLShader ObjShader;
	byhj::Model modelLoad;
};

}
#endif
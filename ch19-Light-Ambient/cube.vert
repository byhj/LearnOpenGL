#version 130

//#version 330 core
//layout (location = 0) in vec3 position;

attribute vec3 position;
uniform mat4 mvp_matrix;

void main()
{
    gl_Position = mvp_matrix * vec4(position, 1.0f);
} 
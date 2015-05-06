#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec2 tc;
out vec3 vColor;

void main()
{
   gl_Position = vec4(position, 1.0f);
   tc = vec2(texCoord.x, 1.0f - texCoord.y);
   vColor = color;
}
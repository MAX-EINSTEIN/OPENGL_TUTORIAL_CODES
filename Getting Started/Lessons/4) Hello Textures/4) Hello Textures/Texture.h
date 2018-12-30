#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
class Texture
{
	unsigned int texture;
	GLenum TexUnit;
public:
	Texture(const char * filename, GLenum texUnit);
	void Bind();
	void Activate();
	~Texture();
};


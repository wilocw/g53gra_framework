#pragma once

#include "DisplayableObject.h"

class Skybox : 
	public DisplayableObject
{
public:
	Skybox(GLuint texTop, GLuint texBottom, GLuint texLeft, GLuint texRight, GLuint texNear, GLuint texFar);
	~Skybox();

	void Display();

private:
	GLuint _texTop, _texBottom, _texLeft, _texRight, _texNear, _texFar;

};
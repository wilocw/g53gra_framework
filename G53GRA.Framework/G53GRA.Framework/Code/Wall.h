#pragma once

#include "DisplayableObject.h"

class Wall :
	public DisplayableObject
{
public:
	Wall();
	~Wall() {};

	void Display();

private:

	GLfloat *_mat_ambient, *_mat_diffuse, *_mat_specular, _mat_shininess;

};


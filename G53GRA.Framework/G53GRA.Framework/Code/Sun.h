#pragma once

#include "DisplayableObject.h"

#include "Animation.h"

class Sun :
	public DisplayableObject,
	public Animation
{
public:
	Sun();
	~Sun();

	void Display();

	void Update(const double& deltaTime);

private:

	GLfloat *_ambient, *_diffuse, *_specular;

	float _runtime;

};


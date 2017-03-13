#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

class Teapot :
	public DisplayableObject,
	public Animation
{
public:
	Teapot();
	~Teapot();

	void Display();
	void Update(const double& deltaTime);

	inline void ToggleAnimation() { _flagAnimation = !_flagAnimation; }

private:
	GLboolean _flagAnimation;
	// Animation rotation rate (degrees per second)
	GLfloat _yrot;
	// Teapot material lighting properties
	GLfloat *_mat_ambient, *_mat_diffuse, *_mat_specular, *_mat_shininess;
};


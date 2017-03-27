#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"

class Light :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Light();

	Light(GLenum lightSrc, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat *position);

	~Light();

	void Display();

	void Update(const double& deltaTime);
	
	void HandleKey(unsigned char key, int state, int mx, int my);

	inline void ToggleVisualisation() { _flagVisualise = !_flagVisualise; }

private:

	GLboolean _flagVisualise;

	GLenum _lightSrc;

	GLfloat *_ambient, *_diffuse, *_specular, *_position;

	GLfloat _c_falloff, _l_falloff, _q_falloff;

};
#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"


#define _LIGHT_0 0
#define _LIGHT_1 4
#define _LIGHT_2 8
#define _LIGHT_3 12

class MultiLight :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	MultiLight();
	~MultiLight();

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);

	inline void ToggleVisualiseLights() { _flagVisualise = !_flagVisualise; }

private:
	// member variable indicating program runtime
	double _runtime;
	// member variable describing radius for rotation
	double _radius;

	// reflectance model parameters for LIGHTS
	GLfloat *_position, *_ambient, *_diffuse, *_specular;

	// flag for showing lights 0-3
	GLboolean _showLight0, _showLight1, _showLight2, _showLight3;

	// flag to visualise light sources
	GLboolean _flagVisualise;
};

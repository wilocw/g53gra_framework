#pragma once

#define direction(x,y,z) position(x,y,z);

#include "DisplayableObject.h"
#include "Animation.h"

class SunLight :
	public DisplayableObject,
	public Animation
{
public:
	SunLight();
	~SunLight();

	void Display(){}; // Override virtual function but do not draw any object (unseen light source)

	void Update(const double& deltaTime);

//	inline void direction(float dx, float dy, float dz) { position(dx, dy, dz); }

private:
	float ambient[4], diffuse[4], specular[4]; // member variables for the reflectance model parameters
};


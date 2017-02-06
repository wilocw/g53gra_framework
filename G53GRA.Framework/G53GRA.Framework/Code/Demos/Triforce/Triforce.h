#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

class Triforce :
	public DisplayableObject,
	public Animation
{
public:
	Triforce();
	~Triforce();

	// Override the DisplayableObject's Draw function
	void Display();
	// Override the Animation Update function
	void Update(const double& deltaTime);

private:
	void DrawBasicTriforce();
	void Draw3DTriangle(float cx, float cy, float cz);


	// Private members to track the rotation of the Triforce
	GLfloat xrot, yrot, zrot;
};


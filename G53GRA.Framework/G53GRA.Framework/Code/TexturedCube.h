#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

#include <string>

class TexturedCube :
	public DisplayableObject,
	public Animation
{
public:
	TexturedCube();
	TexturedCube(const std::string& filename);
	~TexturedCube(){}

	void Display();
	void Update(const double& deltaTime);

private:
	void DrawCube();

	// Rate of rotation in x and y (degrees per second) 
	float _xrot, _yrot;

	GLint texID;
};


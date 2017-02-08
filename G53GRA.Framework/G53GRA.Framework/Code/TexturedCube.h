#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

#include <string>

class TexturedCube :
	public DisplayableObject,
	public Animation
{
public:
	TexturedCube(const std::string& filename);

	~TexturedCube(){};

	void Display();
	void Update(const double& deltaTime);

private:
	void DrawCube();

	GLint texID;
};


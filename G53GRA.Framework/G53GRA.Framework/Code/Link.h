#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"

#include <string>

class Link :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Link(const float& width, const float& height, const std::string& filename);
	~Link();

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleMouse(int button, int state, int x, int y);

private:

	int texID;

	float width, height;
	
	float texCoords[8];
	int spriteWidth;
	int spriteFrame;
	bool runAnimate;
	double time;

	float dx;
};


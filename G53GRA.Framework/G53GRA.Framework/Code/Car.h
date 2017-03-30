#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"

class Car :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Car();
	~Car();

	void Display();
	
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int mx, int my);
	void HandleSpecialKey(int key, int state, int mx, int my);

protected:
	
	float _loopPosition, _velocity;

	void DrawWheel();

};


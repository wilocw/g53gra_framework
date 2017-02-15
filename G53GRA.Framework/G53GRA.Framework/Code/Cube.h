#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"

#define _INIT_SIZE 50.0f

class Cube :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Cube();
	~Cube() { };

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);
	
private:
	void DrawCube();

	// key press flags
	GLboolean _iKey, _jKey, _kKey, _lKey, _oKey, _uKey;
	GLboolean _plusKey, _minusKey, _upKey, _downKey, _leftKey, _rightKey;
	GLboolean _flagReset;
};
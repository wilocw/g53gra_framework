#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"

class FaceCull :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	FaceCull();
	~FaceCull(){};

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int mX, int mY);

	inline void ToggleFaceCulling() { _flagCullFace = !_flagCullFace; }

private:

	GLfloat _roty;
	GLboolean _flagCullFace;

};


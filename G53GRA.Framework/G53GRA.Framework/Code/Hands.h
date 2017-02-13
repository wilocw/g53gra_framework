#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

#define _NUM_JOINTS 14
#define _JOINTS_PER_FINGER 3
#define _FINGER_INDEX 0
#define _FINGER_MIDDLE 1
#define _FINGER_RING 2
#define _FINGER_LITTLE 3


class Hands :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Hands();
	~Hands() {};

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);

	inline void ToggleWireFrame() { _flagWireFrame = !_flagWireFrame; }
	inline void ToggleAnimation() { _flagAnimationActive = !_flagAnimationActive; }
	inline void ToggleHandedness() { _flagLeftHanded = !_flagLeftHanded; }

	inline void SetAnimationControl(const char key) { _control = key; }
	

private:
	void Palm();
	void Finger(const unsigned char finger);
	void Thumb();
	void SubFinger(float _bendAngle);

	void FlexThumb();
	void FlexFinger(const unsigned char finger);

	GLboolean _flagWireFrame, _flagAnimationActive, _flagLeftHanded, _flagAnimationUninitiated, _flagShowroomActive;
	
	unsigned short _keyframe;
	char _control;
	const float _rot = 18.0f;
	float _animateTime, _animateRotation, _showAngle;
	float _jointAngles[_NUM_JOINTS];

};


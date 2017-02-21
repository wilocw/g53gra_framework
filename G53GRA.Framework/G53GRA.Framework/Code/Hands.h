#pragma once

#include "DisplayableObject.h"
#include "Animation.h"

#define _NUM_JOINTS 14
#define _JOINTS_PER_FINGER 3
#define _FINGER_INDEX 0
#define _FINGER_MIDDLE 1
#define _FINGER_RING 2
#define _FINGER_LITTLE 3

// Public DisplayableObject with Animation and Input (key/mouse control)
class Hands :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Hands();
	~Hands() {};

	// Override Display from DisplayableObject
	void Display();
	// Override Update from Animation
	void Update(const double& deltaTime);
	// Override HandleKey from Input
	void HandleKey(unsigned char key, int state, int x, int y);

	// Toggle function to switch Wire Frame flag
	inline void ToggleWireFrame() { _flagWireFrame = !_flagWireFrame; }
	// Toggle function to switch Animation flag
	inline void ToggleAnimation() { _flagAnimationActive = !_flagAnimationActive; }
	// Toggle function to switch Handedness (left/right) flag
	inline void ToggleHandedness() { _flagLeftHanded = !_flagLeftHanded; }

	// Assigns key character to toggle animation (default 'x') 
	inline void SetAnimationControl(const char key) { _control = key; }

private:
	// Render palm
	void Palm();
	// Render finger of given id (_FINGER_{INDEX,MIDDLE,RING,LITTLE})
	void Finger(const unsigned char finger);
	// Render thumb
	void Thumb();
	// Render finger joint and sub-finger rotated by given angle
	void SubFinger(float bendAngle);
	// Render skeleton (Wire Frame only)
	void Skeleton();
	// Render fingers in skeleton
	void SkeletonFinger(const unsigned char finger);
	// Render skeleton joints and sub-finger rotated by given angle (Wire Frame only)
	void SubSkeleton(float bendAngle);

	// Animation control for thumb
	void FlexThumb();
	// Animation control for given id (_FINGER_{INDEX,MIDDLE,RING,LITTLE})
	void FlexFinger(const unsigned char finger);

	// Property flag
	GLboolean _flagWireFrame, _flagAnimationActive, _flagLeftHanded, _flagAnimationUninitiated, _flagShowroomActive;
	// Animation state
	unsigned short _keyframe;
	// Assigned key control (default 'x')
	char _control;
	// Rate of global rotation per second
	const float _ROT = 18.0f;
	// Animation parameter
	float _animateTime, _animateRotation, _showAngle;
	// Array for all joints bend angles in hand
	float _jointAngles[_NUM_JOINTS];

};


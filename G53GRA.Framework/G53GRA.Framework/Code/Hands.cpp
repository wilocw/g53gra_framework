#include "Hands.h"

// Initialise the Hand and its properties
Hands::Hands() :
	_flagWireFrame(false),
	_flagAnimationActive(false),
	_flagLeftHanded(false),
	_flagAnimationUninitiated(true),
	_flagShowroomActive(true),
	_keyframe(0),
	_animateTime(0.0f),
	_animateRotation(0.0f),
	_showAngle(0.0f),
	_control('x')
{
	// Set all joint angles to 0 (no bend)
	for (int i = 0; i < _NUM_JOINTS; ++i)
		_jointAngles[i] = 0.0f;
}

void Hands::Display()
{
	// Push MODELVIEW matrix onto stack (save all transformation changes)
	glPushMatrix();
	
	// Apply rotation to all following calls
	// This will rotate everything drawn about the origin by _showAngle
	// _showAngle is incremented in Update()
	glRotatef(_showAngle, 0.0f, 1.0f, 0.0f);

	// Translate to specified position
	glTranslatef(pos[0], pos[1], pos[2]);
	// Rotate around Y, Z and X axes
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
	// Scale by given size
	glScalef(scale[0], scale[1], scale[2]);

	// If left hand, invert x-axis (left becomes right, right becomes left)
	if (_flagLeftHanded) glScalef(-1.0f, 1.0f, 1.0f);

	// Save state of attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// Set colour to mid green (0.5,1.0,0.5)
	glColor3ub(128, 255, 128); // 0-255

	// If Wire Frame enabled, draw Skeleton inside Hand
	if (_flagWireFrame) Skeleton();
	
	// Draw Hand
	// First, draw Palm of hand
	Palm();
	// LITTLE FINGER
	// Save MODELVIEW matrix at centre of palm
	glPushMatrix();
		// Translate to base of first finger
		glTranslatef(-2.25f, 2.5f, 0.0f);
		// Draw LITTLE FINGER (75% size of middle finger)
		glScalef(0.75f, 0.75f, 0.75f);
		Finger(_FINGER_LITTLE);
		// Revert MODELVIEW matrix to centre of palm
	glPopMatrix();
	// RING FINGER
	// Save MODELVIEW matrix at centre of palm (again)
	glPushMatrix();
		// Translate to base of second finger
		glTranslatef(-1.15f, 2.5f, 0.0f);
		// Draw RING FINGER (90% size of middle finger)
		glScalef(0.9f, 0.9f, 0.9f);
		Finger(_FINGER_RING);
		// Revert MODELVIEW matrix to centre of palm
	glPopMatrix();
	// MIDDLE FINGER
	// Save MODELVIEW matrix to centre of palm (again)
	glPushMatrix();
		// Translate to base of third finger
		glTranslatef(-0.05f, 2.5f, 0.0f);
		// Draw MIDDLE FINGER (100% size of middle finger, duh)
		glScalef(1.0f, 1.0f, 1.0f); // redundant
		Finger(_FINGER_MIDDLE);
	// Revert MODELVIEW matrix to centre of palm
	glPopMatrix();
	// INDEX FINGER
	// Save MODELVIEW matrix to centre of palm (last time)
	glPushMatrix();
		// Translate to base of fourth finger
		glTranslatef(1.05f, 2.5f, 0.0f);
		// Draw INDEX FINGER (90% size of middle finger)
		glScalef(0.9f, 0.9f, 0.9f);
		Finger(_FINGER_INDEX);
	// Revert MODELVIEW matrix to centre of palm
	glPopMatrix();

	// Could push matrix again, but not needed as nothing is drawn after Thumb
	// Final pop will return to original state anyway
//	glPushMatrix();
		// Translate to position of thumb
		glTranslatef(2.25f, -1.25f, 0.0f);
		// Draw THUMB
		Thumb();
	// If aforementioned push is included, this pop is required
//	glPopMatrix();

	// Revert style to before changes were made in this method
	glPopAttrib();
	// Revert MODLEVIEW matrix to original state at beginning of method
	glPopMatrix();
}

void Hands::Palm()
{
	// Push matrix as we are scaling a unit cube to create the palm
	glPushMatrix();
		// Scale along x and y to stretch 1x1x1 cube
		glScalef(4.5f, 4.5f, 1.0f);
		// Render cube (now scaled)
		_flagWireFrame ? glutWireCube(1.0f) : glutSolidCube(1.0f);
	// Pop matrix to undo scaling (equiv to glScalef(1.f/4.5f,1.f/4.5f,1.f) if push matrix weren't used)
	glPopMatrix();
}

void Hands::Finger(const unsigned char finger)
{
	// Offset joint index for this finger
	const unsigned char jID = finger*_JOINTS_PER_FINGER;

	// The values of _jointAngles indicate the degree
	// to which a finger joint is bent. This is controlled
	// by the Animation cycle, and set in Update().

	// Scale to elongate fingers in y-direction
	glScalef(1.0f, 1.8f, 1.0f);
	// Translate to centre of finger
	glTranslatef(0.5f, 0.0f, 0.0f);
	// Create first sub finger, bent at the joint
	SubFinger(_jointAngles[jID]);
	// Create second sub finger, bent at the joint
	SubFinger(_jointAngles[jID+1]);
	// Scale to shrink final sub finger by 20%
	glScalef(1.0f, 0.8f, 1.0f);
	// Create third sub finger, bent at the joint
	SubFinger(_jointAngles[jID+2]);
}

void Hands::Thumb()
{
	// The Thumb differs from a regular Finger as it has only two joints
	// and two sub-fingers. These joint bends are controlled by
	// _jointAngles[12] and _jointAngles[13], which are set in Update()
	// during the Animation.

	// Save transformation matrix (MODELVIEW) (this is perhaps unneccessary)
	glPushMatrix();
		// A thumb is wider and shorter than a finger
		glScalef(1.2f, 1.5f, 1.0f);
		// Thumb is about 45% out from hand
		glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
		// Create first sub finger, bent at joint
		SubFinger(_jointAngles[12]);
		// Create second sub finger, bent at joint
		SubFinger(_jointAngles[13]);
	// Revert matrix to previous state (before call to Thumb())
	glPopMatrix();
}

void Hands::SubFinger(float bendAngle)
{
	// A sub finger is a scaled cube, rotated at the
	// joint by bendAngle
	glRotatef(bendAngle, 1.0f, 0.0f, 0.0f);
	// Translate to centre of sub-finger
	glTranslatef(0.0f, 0.5f, 0.0f);
	// Render cube (now scaled)
	_flagWireFrame ? glutWireCube(1.0f) : glutSolidCube(1.0f);
	// Translate to top of sub-finger
	glTranslatef(0.0f, 0.5f, 0.0f);
}

void Hands::Skeleton()
{
	// Renders Skeleton, a set of lines indicating location
	// of joints and representing logic behind hierarchical modelling
	// Save Attribute (styling) state, as we are changing colour and linewidth
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// Make lines thicker to visualise better (and smooth this to avoid aliasing)
	glLineWidth(3.0f);
	glEnable(GL_LINE_SMOOTH);
	// Set colour to mid-red (1.0,0.5,0.5)
	glColor3ub(255, 128, 128); // 0-255

	// Push MODELVIEW matrix to stack
	glPushMatrix();
	
	// Create first line from base of palm to base of first finger
	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.5f, 0.0f);
		glVertex3f(-2.25f+0.75f*0.5f, 2.5f, 0.0f);
	glEnd();
	// Push MODELVIEW matrix to stack when drawing first finger
	glPushMatrix();
		// Translate to base of LITTLE FINGER
		glTranslatef(-2.25f, 2.5f, 0.0f);
		// LITTLE FINGER is 75% size of middle finger
		glScalef(0.75f, 0.75f, 0.75f);
		SkeletonFinger(_FINGER_LITTLE);
	// Pop MODELVIEW matrix to revert to base of palm
	glPopMatrix();
	// Create second line from base of palm to base of second finger
	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.5f, 0.0f);
		glVertex3f(-1.15f + 0.9f*0.5f, 2.5f, 0.0f);
	glEnd();
	// Push MODELVIEW matrix to stack when drawing second finger
	glPushMatrix();
		// Translate to base of RING FINGER
		glTranslatef(-1.15f, 2.5f, 0.0f);
		// RING FINGER is 90% size of middle finger
		glScalef(0.9f, 0.9f, 0.9f);
		SkeletonFinger(_FINGER_RING);
	// Pop MODELVIEW matrix to revert to base of palm
	glPopMatrix();
	// Create third line from base of palm to base of third finger
	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.5f, 0.0f);
		glVertex3f(-0.05f + 0.5f, 2.5f, 0.0f);
	glEnd();
	// Push MODELVIEW matrix to stack when drawing third finger
	glPushMatrix();
		// Translate to base of MIDDLE FINGER
		glTranslatef(-0.05f, 2.5f, 0.0f);
		SkeletonFinger(_FINGER_RING);
	// Pop MODELVIEW matrix to revert to base of palm
	glPopMatrix();
	// Create fourth line from base of palm to base of fourth finger
	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.5f, 0.0f);
		glVertex3f(1.05f + 0.9f*0.5f, 2.5f, 0.0f);
	glEnd();
	// Push MODELVIEW matrix to stack when drawing fourth finger
	glPushMatrix();
		// Translate to base of INDEX FINGER
		glTranslatef(1.05f, 2.5f, 0.0f);
		// INDEX FINGER is 90% size of middle finger
		glScalef(0.9f, 0.9f, 0.9f);
		SkeletonFinger(_FINGER_INDEX);
	// Pop MODELVIEW matrix to revert to base of palm
	glPopMatrix();

	// Create line from base of palm to base of thumb
	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.5f, 0.0f);
		glVertex3f(2.25f, -1.25f, 0.0f);
	glEnd();
	// Translate to base of THUMB
	glTranslatef(2.25f, -1.25f, 0.0f);
	// A thumb is wider and shorter than a finger
	glScalef(1.2f, 1.5f, 1.0f);
	// Thumb is about 45% out from hand
	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
	// Draw sub-finger skeletons at joint angles
	SubSkeleton(_jointAngles[12]);
	SubSkeleton(_jointAngles[13]);

	// Pop MODELVIEW matrix stack to revert all skeleton transformations
	glPopMatrix();
	// Revert all changes to the styling attributes (here, glColor, glLineWidth and GL_LINE_SMOOTH)
	glPopAttrib();
}

void Hands::SkeletonFinger(const unsigned char finger)
{
	// Offset joint index for this finger
	const unsigned char jID = finger*_JOINTS_PER_FINGER;

	// The values of _jointAngles indicate the degree
	// to which a finger joint is bent. This is controlled
	// by the Animation cycle, and set in Update().

	// Scale to stretch finger along y-axis
	glScalef(1.0f, 1.8f, 1.0f);
	// Translate to middle of finger base
	glTranslatef(0.5f, 0.0f, 0.0f);
	// Draw first sub-finger skeleton bent at joint angle
	SubSkeleton(_jointAngles[jID]);
	// Draw second sub-finger skeleton bent at joint angle
	SubSkeleton(_jointAngles[jID + 1]);
	// Scale to shrink final sub finger by 20%
	glScalef(1.0f, 0.8f, 1.0f);
	// Draw third sub-finger skeleton bent at joint angle
	SubSkeleton(_jointAngles[jID + 2]);
}

void Hands::SubSkeleton(float bendAngle)
{
	// A sub finger skeleton is line connecting joints,
	// rotated at the first joint by bendAngle
	glRotatef(bendAngle, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	// Translate to second of joint
	glTranslatef(0.0f, 1.0f, 0.0f);
}

void Hands::Update(const double& deltaTime)
{
	// The Update function is called every frame, and can be used to smoothly
	// update Animation parameters based on time passing, rather than per frame.
	// *** deltaTime is a double-precision floating point number indicating   ***
	// *** the number of seconds that have passed since the last Update cycle ***

	// In Hands, there are two Animated features.
	// The first, the "showroom", is the rotation of the hands about the origin
	// y-axis by _showAngle (only if _flagShowroomActive == true)
	// The second is the flexing of fingers in sequence (if _flagAnimationActive == true)

	// Update showroom angle
	if (_flagShowroomActive)
	{
		// Increment _showAngle at a rate of 18 degrees per second (defined by _ROT)
		_showAngle += _ROT*static_cast<float>(deltaTime);
		// If _showAngle exceeds 360 degrees, restart from 0 (prevents overflow in extreme case)
		if (_showAngle > 360.0f) _showAngle -= 360.0f;
	}

	// If animation is inactive, ignore animation cylce
	if (!_flagAnimationActive)
		return;

	// First time call, start animation from beginning of cycle
	if (_flagAnimationUninitiated)
	{
		_animateTime = 0.0f;
		_animateRotation = 0.0f;
		_flagAnimationUninitiated = false;
	}
	// Otherwise increment time and angles by on deltaTime
	else
	{
		// update the time and rotation steps
		_animateTime += static_cast<float>(deltaTime);
		_animateRotation += static_cast<float>(deltaTime);
	}

	// During Update(), depending on the keyframe, the _jointAngles are
	// smoothly interpolated between an initial angle (0.0) to a maximum angle
	// (MAX_FLEX, the value of which varies per finger joint) such that it
	// takes exactly 1 second to flex from 0 to max angle regardless of the value.
	// The reverse "stretch" interpolates the joint angles from MAX_FLEX to 0.0,
	// again in exactly 1 second. The following diagram describes the animation cycle, 
	// with brief description of the animation state during each keyframe. Each keyframe
	// is active for 1 second, the entire time it takes to flex or stretch a finger.

	//  Keyframe    Animation State
	// .––––,
	// ¦ .––0	    Start of animation (Fingers stretched)
	// ¦ '–>1––.    Flex thumb 
	// ¦ .––2<–'    Flex index finger
	// ¦ '–>3––.    Flex middle finger
	// ¦ .––4<–'    Flex ring finger
	// ¦ '–>5––.    Flex little finger
	// '–.––6<–|    Stretch all fingers
	//   '–>7––'    Flex all fingers


	// check if we hit the end of the animation (8 seconds), if so reset
	// Note, the animation cycle is setup to loop after 8 seconds, so this
	// should be a smooth reset
	if (_animateTime > 8.0f)
	{
		_animateTime = 0.0f;
		_animateRotation = 0.0f;
		// Key Frame 0 indicates animation ready to begin
		_keyframe = 0;
		for (int i = 0; i < _NUM_JOINTS; ++i)
			_jointAngles[i] = 0.0f;
	}
	// First second of animation cycle
	if (_animateTime < 1.0f)
	{
		// Increment animaton state if keyframe 0 
		if (_keyframe == 0)
		{
			// Flex thumb
			_keyframe = 1;
			// Initialise bend at 0
			_animateRotation = 0.0f;
		}
		// Flex Thumb during Key Frame 1
		FlexThumb();
	}
	// Second second of animation cycle
	else if (_animateTime < 2.0f)
	{
		// Follow on only from thumb flex
		if (_keyframe == 1)
		{
			// Flex index finger
			_keyframe = 2;
			// Initialise bend at 0
			_animateRotation = 0.0f;
		}
		// Flex Finger during Key Frame 2
		FlexFinger(_FINGER_INDEX);
	}
	// Third second of animation cycle
	else if (_animateTime < 3.0f)
	{
		// Follow on only from index finger flex
		if (_keyframe == 2)
		{
			// Flex middle finger
			_keyframe = 3;
			// Initialise bend at 0
			_animateRotation = 0.0f;
		}
		// Flex Finger during Key Frame 3
		FlexFinger(_FINGER_MIDDLE);
	}
	// Fourth second of animation cycle
	else if (_animateTime < 4.0f)
	{
		// Follow on only from middle finger flex
		if (_keyframe == 3)
		{
			// Flex ring finger
			_keyframe = 4;
			// Initialise bend at 0
			_animateRotation = 0.0f;
		}
		// Flex Finger during Key Frame 4
		FlexFinger(_FINGER_RING);
	}
	// Fifth second of animation cycle
	else if (_animateTime < 5.0f)
	{
		// Follow on only from ring finger flex
		if (_keyframe == 4)
		{
			// Flex little finger
			_keyframe = 5;
			// Initialise bend at 0
			_animateRotation = 0.0f;
		}
		// Flex Finger during Key Frame 5
		FlexFinger(_FINGER_LITTLE);
	}
	// Sixth and eighth seconds of animation cycle
	else if (_animateTime < 6.0f || _animateTime >= 7.0f)
	{
		// Follow on from little finger flex OR
		//     all finger flex
		if (_keyframe == 5 || _keyframe == 7)
		{
			// Stretch all fingers
			_keyframe = 6;
			// Initialise bend at 0
			_animateRotation = 0.0f;
		}
		// Stretch all fingers during Key Frame 6
		FlexFinger(_FINGER_LITTLE);
		FlexFinger(_FINGER_RING);
		FlexFinger(_FINGER_MIDDLE);
		FlexFinger(_FINGER_INDEX);
		FlexThumb();
	}
	// Seventh second of animation cycle
	else if (_animateTime < 7.0f)
	{
		// Follow on from finger stretch
		if (_keyframe == 6)
		{
			// Flex all fingers
			_keyframe = 7;
			// Initialise bend at 0
			_animateRotation = 0.0f;
		}
		// Flex all fingers during Key Frame 7
		FlexFinger(_FINGER_LITTLE);
		FlexFinger(_FINGER_RING);
		FlexFinger(_FINGER_MIDDLE);
		FlexFinger(_FINGER_INDEX);
		FlexThumb();
	}	
}

void Hands::FlexThumb()
{
	// The flexing and stretch of Thumb describes the bending sequentially
	// of both thumb joints between 0 and 45 degrees over 1 s
	const float MAX_FLEX = 45.0f;
	// Check the current state animation
	switch (_keyframe)
	{
	// Flex Thumb only
	case 1:
	// Flex all fingers (including Thumb)
	case 7:
		// Bend first joint for 0.5 s
		if (_jointAngles[13] < MAX_FLEX)
		{
			_jointAngles[13] = 2.0f * _animateRotation*MAX_FLEX;
			// Cap at MAX_FLEX (avoids f.p. overshoot)
			if (_jointAngles[13] > MAX_FLEX) _jointAngles[13] = MAX_FLEX;
		}
		// Then bend second joint for 0.5 s
		else if (_jointAngles[12] < MAX_FLEX)
		{
			_jointAngles[12] = 2.0f * (_animateRotation - 0.5f)*MAX_FLEX;
			// Cap at MAX_FLEX (avoids f.p. overshoot)
			if (_jointAngles[12] > MAX_FLEX) _jointAngles[12] = MAX_FLEX;
		}
		break;
	// Stretch all fingers (including Thumb)
	case 6:
		// Stretch second joint for 0.5 s
		if (_jointAngles[12] > 0.0f)
		{
			_jointAngles[12] = (1.0f - 2.0f * _animateRotation)*MAX_FLEX;
			// Cap at 0 (avoids f.p. undershoot)
			if (_jointAngles[12] < 0.0f) _jointAngles[12] = 0.0f;
		}
		// Stretch first joint for 0.5 s
		else if (_jointAngles[13] > 0.0f)
		{
			_jointAngles[13] = 2.0f * (1.0f - _animateRotation)*MAX_FLEX;
			// Cap at 0 (avoids f.p. undershoot)
			if (_jointAngles[13] < 0.0f) _jointAngles[13] = 0.0f;
		}
		break;
	}
}

void Hands::FlexFinger(const unsigned char finger)
{
	// The flexing and stretch of a Finger describes the bending sequentially
	// of the individual joints between 0 and 45, 90, and 45 degrees respectively
	// over 1 s
	const float MAX_FLEX[_JOINTS_PER_FINGER] = { 45.0f, 90.0f, 45.0f };
	const unsigned char jID = _JOINTS_PER_FINGER*finger;
	switch (_keyframe)
	{
	// Flex Index Finger
	case 2:
	// Flex Middle Finger
	case 3:
	// Flex Ring Finger
	case 4:
	// Flex Little Finger
	case 5:
	// Flex all Fingers
	case 7:
		// Flex first joint to 45 degrees over 0.33. s
		if (_jointAngles[jID] < MAX_FLEX[0])
		{
			_jointAngles[jID] = 3.0f * _animateRotation*MAX_FLEX[0];
			if (_jointAngles[jID] > MAX_FLEX[0]) _jointAngles[jID] = MAX_FLEX[0];
		}
		// Flex second joint to 90 degrees over 0.33. s
		else if (_jointAngles[jID + 1] < MAX_FLEX[1])
		{
			_jointAngles[jID + 1] = 3.0f * (_animateRotation - (1.0f / 3.0f))*MAX_FLEX[1];
			if (_jointAngles[jID + 1] > MAX_FLEX[1]) _jointAngles[jID + 1] = MAX_FLEX[1];
		}
		// Flex third joint to 45 degrees over 0.33. s
		else if (_jointAngles[jID + 2] < MAX_FLEX[2])
		{
			_jointAngles[jID + 2] = 3.0f * (_animateRotation - (2.0f / 3.0f))*MAX_FLEX[2];
			if (_jointAngles[jID + 2] > MAX_FLEX[2]) _jointAngles[jID + 2] = MAX_FLEX[2];
		}
		break;
	// Stretch all fingers
	case 6:
		// Stretch third joint to 0 degrees over 0.33. s
		if (_jointAngles[jID + 2] > 0.0f)
		{
			_jointAngles[jID + 2] = (1.0f - 3.0f * _animateRotation)*MAX_FLEX[2];
			if (_jointAngles[jID + 2] < 0.0f) _jointAngles[jID + 2] = 0.0f;
		}
		// Stretch second joint to 0 degrees over 0.33. s
		else if (_jointAngles[jID + 1] > 0.0f)
		{
			_jointAngles[jID + 1] = 2.0f * (1.0f - (3.0f / 2.0f)*_animateRotation)*MAX_FLEX[1];
			if (_jointAngles[jID + 1] < 0.0f) _jointAngles[jID + 1] = 0.0f;
		}
		// Stretch first joint to 0 degrees over 0.33. s
		else if (_jointAngles[jID] > 0.0f)
		{
			_jointAngles[jID] = 3.0f * (1.0f - _animateRotation)*MAX_FLEX[0];
			if (_jointAngles[jID] < 0.0f) _jointAngles[jID] = 0.0f;
		}
		break;
	}
}

void Hands::HandleKey(unsigned char key, int state, int x, int y)
{
	// If control key is pressed, toggle Animation
	if (key == _control && state)
		ToggleAnimation();
}

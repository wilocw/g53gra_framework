#include "Hands.h"


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
	for (int i = 0; i < _NUM_JOINTS; ++i)
		_jointAngles[i] = 0.0f;
}

void Hands::Display()
{
	glPushMatrix();
	
	glRotatef(_showAngle, 0.0f, 1.0f, 0.0f);

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
	glScalef(scale[0], scale[1], scale[2]);

	if (_flagLeftHanded) glScalef(-1.0f, 1.0f, 1.0f);

	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glColor3ub(128, 255, 128);

	if (_flagWireFrame) Skeleton();
	
	Palm();
	glPushMatrix();
		glTranslatef(-2.25f, 2.5f, 0.0f);
		glScalef(0.75f, 0.75f, 0.75f);
		
		Finger(_FINGER_LITTLE);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-1.15f, 2.5f, 0.0f);
		glScalef(0.9f, 0.9f, 0.9f);

		Finger(_FINGER_RING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.05f, 2.5f, 0.0f);
		glScalef(1.0f, 1.0f, 1.0f); // redundant

		Finger(_FINGER_MIDDLE);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(1.05f, 2.5f, 0.0f);
		glScalef(0.9f, 0.9f, 0.9f);

		Finger(_FINGER_INDEX);
	glPopMatrix();

	glPushMatrix();

		glTranslatef(2.25f, -1.25f, 0.0f);

		Thumb();

	glPopMatrix();

	glPopAttrib();
	glPopMatrix();
}

void Hands::Palm()
{
	glPushMatrix();
		glScalef(4.5f, 4.5f, 1.0f);

		_flagWireFrame ? glutWireCube(1.0f) : glutSolidCube(1.0f);
	glPopMatrix();
}

void Hands::Finger(const unsigned char finger)
{
	const unsigned char jID = finger*_JOINTS_PER_FINGER;

	glScalef(1.0f, 1.8f, 1.0f);

	glTranslatef(0.5f, 0.0f, 0.0f);

	SubFinger(_jointAngles[jID]);

	SubFinger(_jointAngles[jID+1]);
	
	glScalef(1.0f, 0.8f, 1.0f);

	SubFinger(_jointAngles[jID+2]);
}

void Hands::Thumb()
{
	glPushMatrix();
		glScalef(1.2f, 1.5f, 1.0f);

		glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);

		SubFinger(_jointAngles[12]);

		SubFinger(_jointAngles[13]);

	glPopMatrix();
}

void Hands::SubFinger(float bendAngle)
{
	glRotatef(bendAngle, 1.0f, 0.0f, 0.0f);

	glTranslatef(0.0f, 0.5f, 0.0f);

	_flagWireFrame ? glutWireCube(1.0f) : glutSolidCube(1.0f);

	glTranslatef(0.0f, 0.5f, 0.0f);
}

void Hands::Skeleton()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glLineWidth(3.0f);
	glEnable(GL_LINE_SMOOTH);
	glColor3ub(255, 128, 128);

	glPushMatrix();
	
	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.5f, 0.0f);
		glVertex3f(-2.25f+0.75f*0.5f, 2.5f, 0.0f);
	glEnd();

	glPushMatrix();

		glTranslatef(-2.25f, 2.5f, 0.0f);
		glScalef(0.75f, 0.75f, 0.75f);
		glScalef(1.0f, 1.8f, 1.0f);
		glTranslatef(0.5f, 0.0f, 0.0f);

		SubSkeleton(_jointAngles[_FINGER_LITTLE*_JOINTS_PER_FINGER]);
		
		SubSkeleton(_jointAngles[_FINGER_LITTLE*_JOINTS_PER_FINGER + 1]);

		glScalef(1.0f, 0.8f, 1.0f);
		SubSkeleton(_jointAngles[_FINGER_LITTLE*_JOINTS_PER_FINGER + 2]);
		
	glPopMatrix();
		
	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.5f, 0.0f);
		glVertex3f(-1.15f + 0.9f*0.5f, 2.5f, 0.0f);
	glEnd();

	glPushMatrix();

		glTranslatef(-1.15f, 2.5f, 0.0f);
		glScalef(0.9f, 0.9f, 0.9f);
		glScalef(1.0f, 1.8f, 1.0f);
		glTranslatef(0.5f, 0.0f, 0.0f);

		SubSkeleton(_jointAngles[_FINGER_RING*_JOINTS_PER_FINGER]);

		SubSkeleton(_jointAngles[_FINGER_RING*_JOINTS_PER_FINGER + 1]);

		glScalef(1.0f, 0.8f, 1.0f);
		SubSkeleton(_jointAngles[_FINGER_RING*_JOINTS_PER_FINGER + 2]);

	glPopMatrix();
	
	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.5f, 0.0f);
		glVertex3f(-0.05f + 0.5f, 2.5f, 0.0f);
	glEnd();

	glPushMatrix();

		glTranslatef(-0.05f, 2.5f, 0.0f);
		glScalef(1.0f, 1.8f, 1.0f);
		glTranslatef(0.5f, 0.0f, 0.0f);

		SubSkeleton(_jointAngles[_FINGER_MIDDLE*_JOINTS_PER_FINGER]);

		SubSkeleton(_jointAngles[_FINGER_MIDDLE*_JOINTS_PER_FINGER + 1]);

		glScalef(1.0f, 0.8f, 1.0f);
		SubSkeleton(_jointAngles[_FINGER_MIDDLE*_JOINTS_PER_FINGER + 2]);

	glPopMatrix();

	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.5f, 0.0f);
		glVertex3f(1.05f + 0.9f*0.5f, 2.5f, 0.0f);
	glEnd();

	glPushMatrix();

		glTranslatef(1.05f, 2.5f, 0.0f);
		glScalef(0.9f, 0.9f, 0.9f);
		glScalef(1.0f, 1.8f, 1.0f);
		glTranslatef(0.5f, 0.0f, 0.0f);

		SubSkeleton(_jointAngles[_FINGER_INDEX*_JOINTS_PER_FINGER]);

		SubSkeleton(_jointAngles[_FINGER_INDEX*_JOINTS_PER_FINGER + 1]);

		glScalef(1.0f, 0.8f, 1.0f);
		SubSkeleton(_jointAngles[_FINGER_INDEX*_JOINTS_PER_FINGER + 2]);

	glPopMatrix();

	glBegin(GL_LINES);
		glVertex3f(0.0f, -2.5f, 0.0f);
		glVertex3f(2.25f, -1.25f, 0.0f);
	glEnd();

	glTranslatef(2.25f, -1.25f, 0.0f);

	glScalef(1.2f, 1.5f, 1.0f);

	glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);

	SubSkeleton(_jointAngles[12]);

	SubSkeleton(_jointAngles[13]);


	glPopMatrix();
	glPopAttrib();
}

void Hands::SubSkeleton(float bendAngle)
{
	glRotatef(bendAngle, 1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
	glTranslatef(0.0f, 1.0f, 0.0f);
}

void Hands::Update(const double& deltaTime)
{
	if (_flagShowroomActive)
	{
		_showAngle += _rot*static_cast<float>(deltaTime);
		if (_showAngle > 360.0f) _showAngle -= 360.0f;
	}

	if (!_flagAnimationActive)
		return;

	if (_flagAnimationUninitiated)
	{
		_animateTime = 0.0f;
		_animateRotation = 0.0f;
		_flagAnimationUninitiated = false;
	}
	else
	{
		// update the time and rotation steps
		_animateTime += static_cast<float>(deltaTime);
		_animateRotation += static_cast<float>(deltaTime);
	}

	// check if we hit the end of the animation (8 seconds), if so reset
	if (_animateTime > 8.0f)
	{
		_animateTime = 0.0f;
		_animateRotation = 0.0f;
		_keyframe = 0;
		for (int i = 0; i < _NUM_JOINTS; ++i)
			_jointAngles[i] = 0.0f;
	}

	if (_animateTime < 1.0f)
	{
		if (_keyframe == 0)
		{
			_keyframe = 1;
			_animateRotation = 0.0f;
		}
		FlexThumb();
	}
	else if (_animateTime < 2.0f)
	{
		if (_keyframe == 1)
		{
			_keyframe = 2;
			_animateRotation = 0.0f;
		}
		FlexFinger(_FINGER_INDEX);
	}
	else if (_animateTime < 3.0f)
	{
		if (_keyframe == 2)
		{
			_keyframe = 3;
			_animateRotation = 0.0f;
		}
		FlexFinger(_FINGER_MIDDLE);
	}
	else if (_animateTime < 4.0f)
	{
		if (_keyframe == 3)
		{
			_keyframe = 4;
			_animateRotation = 0.0f;
		}
		FlexFinger(_FINGER_RING);
	}
	else if (_animateTime < 5.0f)
	{
		if (_keyframe == 4)
		{
			_keyframe = 5;
			_animateRotation = 0.0f;
		}
		FlexFinger(_FINGER_LITTLE);
	}
	else if (_animateTime < 6.0f || _animateTime >= 7.0f)
	{
		if (_keyframe == 5 || _keyframe == 7)
		{
			_keyframe = 6;
			_animateRotation = 0.0f;
		}
		FlexFinger(_FINGER_LITTLE);
		FlexFinger(_FINGER_RING);
		FlexFinger(_FINGER_MIDDLE);
		FlexFinger(_FINGER_INDEX);
		FlexThumb();
	}
	else if (_animateTime < 7.0f)
	{
		if (_keyframe == 6)
		{
			_keyframe = 7;
			_animateRotation = 0.0f;
		}
		FlexFinger(_FINGER_LITTLE);
		FlexFinger(_FINGER_RING);
		FlexFinger(_FINGER_MIDDLE);
		FlexFinger(_FINGER_INDEX);
		FlexThumb();
	}	
}

void Hands::FlexThumb()
{
	const float MAX_FLEX = 45.0f;
	switch (_keyframe)
	{
	case 1:
	case 7:
		if (_jointAngles[13] < MAX_FLEX)
		{
			_jointAngles[13] = 2.0f * _animateRotation*MAX_FLEX;
			if (_jointAngles[13] > MAX_FLEX) _jointAngles[13] = MAX_FLEX;
		}
		else if (_jointAngles[12] < MAX_FLEX)
		{
			_jointAngles[12] = 2.0f * (_animateRotation - 0.5f)*MAX_FLEX;
			if (_jointAngles[12] > MAX_FLEX) _jointAngles[12] = MAX_FLEX;
		}
		break;
	case 6:
		if (_jointAngles[12] > 0.0f)
		{
			_jointAngles[12] = (1.0f - 2.0f * _animateRotation)*MAX_FLEX;
			if (_jointAngles[12] < 0.0f) _jointAngles[12] = 0.0f;
		}
		else if (_jointAngles[13] > 0.0f)
		{
			_jointAngles[13] = 2.0f * (1.0f - _animateRotation)*MAX_FLEX;
			if (_jointAngles[13] < 0.0f) _jointAngles[13] = 0.0f;
		}
		break;
	}
}

void Hands::FlexFinger(const unsigned char finger)
{
	const float MAX_FLEX[_JOINTS_PER_FINGER] = { 45.0f, 90.0f, 45.0f };
	const unsigned char jID = _JOINTS_PER_FINGER*finger;
	switch (_keyframe)
	{
	case 2:
	case 3:
	case 4:
	case 5:
	case 7:
		if (_jointAngles[jID] < MAX_FLEX[0])
		{
			_jointAngles[jID] = 3.0f * _animateRotation*MAX_FLEX[0];
			if (_jointAngles[jID] > MAX_FLEX[0]) _jointAngles[jID] = MAX_FLEX[0];
		}
		else if (_jointAngles[jID + 1] < MAX_FLEX[1])
		{
			_jointAngles[jID + 1] = 3.0f * (_animateRotation - (1.0f / 3.0f))*MAX_FLEX[1];
			if (_jointAngles[jID + 1] > MAX_FLEX[1]) _jointAngles[jID + 1] = MAX_FLEX[1];
		}
		else if (_jointAngles[jID + 2] < MAX_FLEX[2])
		{
			_jointAngles[jID + 2] = 3.0f * (_animateRotation - (2.0f / 3.0f))*MAX_FLEX[2];
			if (_jointAngles[jID + 2] > MAX_FLEX[2]) _jointAngles[jID + 2] = MAX_FLEX[2];
		}
		break;
	case 6:
		if (_jointAngles[jID + 2] > 0.0f)
		{
			_jointAngles[jID + 2] = (1.0f - 3.0f * _animateRotation)*MAX_FLEX[2];
			if (_jointAngles[jID + 2] < 0.0f) _jointAngles[jID + 2] = 0.0f;
		}
		else if (_jointAngles[jID + 1] > 0.0f)
		{
			_jointAngles[jID + 1] = 2.0f * (1.0f - (3.0f / 2.0f)*_animateRotation)*MAX_FLEX[1];
			if (_jointAngles[jID + 1] < 0.0f) _jointAngles[jID + 1] = 0.0f;
		}
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
	if (key == _control && state)
		ToggleAnimation();
}

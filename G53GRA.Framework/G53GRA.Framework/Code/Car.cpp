#include "Car.h"

#include "VectorMath.h"

#define _TRACK_RADIUS 20.0f
#define _ACCELERATION 10.0f

Car::Car() : _loopPosition(0.0f), _velocity(0.0f)
{

}


Car::~Car()
{

}

void Car::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);

	glTranslatef(_TRACK_RADIUS, 0.0f, 0.0f);
	glPushMatrix();
	{
		glScalef(2.0f, 1.0f, 3.0f);
		glColor3f(0.7f, 0.0f, 0.0f);
		glutSolidCube(1.0);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(-1.0f, -0.5f, -1.5f);
		DrawWheel();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1.0f, -0.5f, -1.5f);
		DrawWheel();
	}
	glPopMatrix();
		
	glPushMatrix();
	{
		glTranslatef(-1.0f, -0.5f, 1.5f);
		DrawWheel();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1.0f, -0.5f, 1.5f);
		DrawWheel();
	}
	glPopMatrix();
	

	glPopAttrib();
	glPopMatrix();
}

void Car::DrawWheel()
{

	glScalef(0.2f, 0.5f, 0.5f);
	glColor3f(0.0f, 0.0f, 0.0f);

	float th = 0.0f;
	float res = 2.0f * M_PI / 20.0f;
	float y = 1.0f, z = 0.0f;

	do
	{
		glBegin(GL_QUADS);
		{
			glNormal3f(0.0f, y, z);
			glVertex3f(0.5f, y, z);
			glVertex3f(-0.5f, y, z);

			th += res;
			y = cos(th); z = sin(th);

			glNormal3f(0.0f, y, z);
			glVertex3f(-0.5f, y, z);
			glVertex3f(0.5f, y, z);
		}
		glEnd();
	} while (th <= 2.0f * M_PI);

	y = 1.0f, z = 0.0f; th = 0.0f;
	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.5f, 0.0f, 0.0f);
		do
		{
			glVertex3f(0.5f, y, z);
			th += res;
			y = cos(th); z = sin(th);
			glVertex3f(0.5f, y, z);
		} while (th <= 2.0f * M_PI);
	}
	glEnd();

	y = 1.0f, z = 0.0f;

	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-0.5f, 0.0f, 0.0f);

		do
		{
			glVertex3f(-0.5f, y, z);
			th -= res;
			y = cos(th); z = sin(th);
			glVertex3f(-0.5f, y, z);
		} while (th >= 0.0f);
	}
	glEnd();
}


void Car::Update(const double& deltaTime)
{
	rotation[1] += static_cast<float>(deltaTime) *_velocity;

}

void Car::HandleKey(unsigned char key, int state, int mx, int my)
{
	if (!state) return;

	switch (key)
	{
	case '+':
	case '=':
		_velocity += _ACCELERATION;
		break;
	case '-':
		_velocity -= _ACCELERATION;
		break;
	}

	if (_velocity > 180.0f)
		_velocity = 180.0f;
	else if (_velocity < 0.0f)
		_velocity = 0.0f;
}

void Car::HandleSpecialKey(int key, int state, int mx, int my)
{

}
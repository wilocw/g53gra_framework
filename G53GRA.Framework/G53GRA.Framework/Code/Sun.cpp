#include "Sun.h"


Sun::Sun() : _runtime(0.0f)
{
	static GLfloat ambient[] =
	{
		0.1f, 0.1f, 0.1f, 1.0f
	};

	static GLfloat diffuse[] =
	{
		0.9f, 0.8f, 0.4f, 1.0f
	};

	static GLfloat specular[] =
	{
		1.0f, 1.0f, 0.0f, 1.0f
	};

	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
}


Sun::~Sun()
{
}

void Sun::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glDisable(GL_LIGHTING);

		glTranslatef(pos[0], pos[1], pos[2]);

		glColor4fv(_diffuse);
		glutSolidSphere(100.0, 10, 10);

		glEnable(GL_LIGHTING);
	}
	glPopAttrib();
	glPopMatrix();
}

void Sun::Update(const double& deltaTime)
{
	_runtime += static_cast<float>(deltaTime);
/*
	pos[0] = scale[0]*sin(_runtime);
	pos[1] = scale[1]*cos(_runtime);
*/
	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, _ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, _diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, _specular);

	GLfloat lightpos[] = { pos[0], pos[1], pos[2], 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glEnable(GL_LIGHT0);
}
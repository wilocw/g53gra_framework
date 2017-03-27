#include "Wall.h"

#define _TESSELATION_RES 100.0f;

Wall::Wall()
{
	// Grey
	static GLfloat mat_ambient[] =
	{
		0.5f, 0.5f, 0.5f, 1.0f
	};
	_mat_ambient = mat_ambient;
	// White
	static GLfloat mat_diffuse[] =
	{
		1.0f, 1.0f, 1.0f, 1.0f
	};
	_mat_diffuse = mat_diffuse;
	// No specular (black)
	static GLfloat mat_specular[] =
	{
		0.0f, 0.0f, 0.0f, 1.0f
	};
	_mat_specular = mat_specular;
	// Matte (not shiny)
	_mat_shininess = 1.0f;
}

void Wall::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, _mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, _mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, _mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, _mat_shininess);

	GLfloat _element_size = 1.0f / _TESSELATION_RES;

	for (GLfloat i = -0.5f; i < 0.5f; i += _element_size)
	{
		for (GLfloat j = -0.5f; j < 0.5f; j += _element_size)
		{
			glBegin(GL_TRIANGLES);
			{
				glNormal3f(0.0f, 0.0f, 1.0f);

				glVertex3f(i, j, 0.0f);
				glVertex3f(i + _element_size, j, 0.0f);
				glVertex3f(i, j + _element_size, 0.0f);

				glVertex3f(i + _element_size, j, 0.0f);
				glVertex3f(i + _element_size, j + _element_size, 0.0f);
				glVertex3f(i, j + _element_size, 0.0f);
			}
			glEnd();
		}
	}

	glPopAttrib();
	glPopMatrix();
}
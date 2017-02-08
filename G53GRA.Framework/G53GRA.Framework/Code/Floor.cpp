#include "Floor.h"

void Floor::Display()
{
	// Draws an exciting chequered floor
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_COLOR_MATERIAL);
	float bDiffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float wDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float shininess = 128.0f;

	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_SPECULAR, static_cast<GLfloat*>(specular));
	glMaterialf(GL_FRONT, GL_SHININESS, static_cast<GLfloat>(shininess));

	for (int i = -10; i < 10; i++)
	{
		for (int j = -10; j < 10; j++)
		{
			if (i % 2)
			{
				if (j % 2)
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(bDiffuse));
				else
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(wDiffuse));
			}
			else
			{
				if (j % 2)
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(wDiffuse));
				else
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(bDiffuse));
			}
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i)+scale[0], -100.0f, scale[2] * static_cast<float>(j)+scale[2]);
			glVertex3f(scale[0] * static_cast<float>(i)+scale[0], -100.0f, scale[2] * static_cast<float>(j));
			glVertex3f(scale[0] * static_cast<float>(i), -100.0f, scale[2] * static_cast<float>(j));
			glVertex3f(scale[0] * static_cast<float>(i), -100.0f, scale[2] * static_cast<float>(j)+scale[2]);
		}
	}
	glEnd();
	glEnable(GL_COLOR_MATERIAL);
	glPopAttrib();
	glPopMatrix();
}
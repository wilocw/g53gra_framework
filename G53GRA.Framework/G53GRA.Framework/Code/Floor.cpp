#include "Floor.h"


Floor::Floor()
{
}


Floor::~Floor()
{
}

void Floor::Display()
{
	// Draws an exciting chequered floor
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
    glDisable(GL_COLOR_MATERIAL);
    float bDiffuse[] = {0.f,0.f,0.f,1.f};
    float wDiffuse[] = {1.f,1.f,1.f,1.f};
    float specular[] = {1.f,1.f,1.f,1.f};
    float shininess  = 128;
    
	glBegin(GL_QUADS);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    
	for (int i = -10; i < 10; i++)
	{
		for (int j = -10; j < 10; j++)
		{
			if (i % 2)
			{
                if (j % 2)
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bDiffuse);
				else
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wDiffuse);
			}
			else
			{
                if (j % 2)
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wDiffuse);
                else
                    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bDiffuse);
			}
            glNormal3f(0.f,1.f,0.f);
			glVertex3f(scale[0] * (float)i + scale[0], -100.0f, scale[2] * (float)j + scale[2]);
			glVertex3f(scale[0] * (float)i + scale[0], -100.0f, scale[2] * (float)j);
			glVertex3f(scale[0] * (float)i, -100.0f, scale[2] * (float)j);
			glVertex3f(scale[0] * (float)i, -100.0f, scale[2] * (float)j + scale[2]);
		}
	}
	glEnd();
    glEnable(GL_COLOR_MATERIAL);
	glPopAttrib();
	glPopMatrix();
}
#include "Skybox.h"


Skybox::Skybox(GLuint texTop, GLuint texBottom, GLuint texLeft, GLuint texRight, GLuint texNear, GLuint texFar) :
_texTop(texTop), _texBottom(texBottom), _texLeft(texLeft), _texRight(texRight), _texNear(texNear), _texFar(texFar)
{

}


Skybox::~Skybox()
{

}

void Skybox::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	// LEFT SIDE
	glBindTexture(GL_TEXTURE_2D, _texLeft); 
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(-1.f, -1.f, 1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(-1.f, -1.f, -1.f);
	}
	glEnd();

	// RIGHT SIDE
	glBindTexture(GL_TEXTURE_2D, _texRight);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(1.f, -1.f, 1.f);
	}
	glEnd();

	//  FAR SIDE
	glBindTexture(GL_TEXTURE_2D, _texFar); 
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(-1.f, -1.f, -1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(1.f, -1.f, -1.f);
	}
	glEnd();

	// NEAR SIDE
	glBindTexture(GL_TEXTURE_2D, _texNear);
	glBegin(GL_QUADS);
	glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
	glVertex3f(-1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
	glVertex3f(1.f, 1.f, 1.f);
	glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
	glVertex3f(1.f, -1.f, 1.f);
	glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
	glVertex3f(-1.f, -1.f, 1.f);
	glEnd();


	// TOP SIDE
	glBindTexture(GL_TEXTURE_2D, _texTop); 
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1.f, 1.f);  // (s,t) = (1,1)
		glVertex3f(1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 1.f);  // (s,t) = (0,1)
		glVertex3f(-1.f, 1.f, 1.f);
		glTexCoord2f(0.f, 0.f);  // (s,t) = (0,0)
		glVertex3f(-1.f, 1.f, -1.f);
		glTexCoord2f(1.f, 0.f);  // (s,t) = (1,0)
		glVertex3f(1.f, 1.f, -1.f);
	}
	glEnd();

	glBindTexture(GL_TEXTURE_2D,NULL);

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);


	// BOTTOM SIDE

	const float TESSELATION_RES = 25.0f;
	float quadsize = 1.0f / TESSELATION_RES;

	glNormal3f(0.0f, 1.0f, 0.0f);
	
	GLfloat mat_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat mat_shininess = 0.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

	for (float i = -1.0f; i < 1.0f; i += quadsize)
	{
		for (float j = -1.0f; j < 1.0f; j += quadsize)
		{
			glBegin(GL_QUADS);
			{
				glVertex3f(i, -1.0f, j + quadsize);
				glVertex3f(i + quadsize, -1.0f, j + quadsize);
				glVertex3f(i + quadsize, -1.0f, j);
				glVertex3f(i, -1.0f, j);
			}
			glEnd();
		}
	}

	glPopAttrib();
	glPopMatrix();
}
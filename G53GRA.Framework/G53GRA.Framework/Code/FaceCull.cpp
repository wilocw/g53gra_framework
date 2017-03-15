#include "FaceCull.h"


FaceCull::FaceCull() : _roty(0.0f), _flagCullFace(true)
{
}

void FaceCull::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	if (!_flagCullFace)
		glDisable(GL_CULL_FACE);

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);

	glScalef(scale[0], scale[1], scale[2]);

	glRotatef(_roty, 0.0f, 1.0f, 0.0f);
    glColor3f(0.5f, 0.5f, 0.5f);
	glutSolidCube(5.0f);

	glScalef(5.0f, 5.0f, 5.0f);
	glPushMatrix();
	glTranslatef(-4.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.8f);
	glBegin(GL_QUADS);
		glVertex3f(0.0f,-1.0f, 1.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);
	glEnd();
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
		glVertex3f(0.0f, -1.0f, 1.0f);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, -1.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(4.0f, 0.0f, 0.0f);
		glColor3f(0.8f, 0.0f, 0.0f);
		glBegin(GL_QUADS);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, -1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, -1.0f);
		glEnd();
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.0f, -1.0f, -1.0f);
		glVertex3f(0.0f, -1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, 1.0f);
		glVertex3f(0.0f, 1.0f, -1.0f);
		glEnd();
	glPopMatrix();

	glEnable(GL_CULL_FACE);
	glPopAttrib();
	glPopMatrix();
}

void FaceCull::Update(const double& deltaTime)
{
	_roty += 20.0f*static_cast<float>(deltaTime);

	if (_roty > 360.0f) _roty -= 360.0f;

}

void FaceCull::HandleKey(unsigned char key, int state, int mX, int mY)
{
	if (state && key == 'x')
		ToggleFaceCulling();
}

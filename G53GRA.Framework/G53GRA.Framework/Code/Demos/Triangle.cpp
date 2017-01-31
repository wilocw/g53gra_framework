#include "Triangle.h"


Triangle::Triangle() : xrot(0.0f), yrot(0.0f), zrot(0.0f), scale(0.5)
{
}


Triangle::~Triangle()
{
}

void Triangle::Display()
{
	glPushMatrix();

	glTranslatef(0.f, 0.f, 0.f);

	// rotate the triangle by the given degrees
	glRotatef(zrot, 0, 0, 1);
	glRotatef(yrot, 0, 1, 0);
	glRotatef(xrot, 1, 0, 0);
	// scale the traingle
	glScalef(0.5, scale, 0.5);

	// disable culling (removal) of backface triangles so that when we look at the back of the triangle
	// to does not disappear
	glDisable(GL_CULL_FACE);

	// draw the triangle us GL_TRIANGLES as the primative
	// so that every 3 verticies we pass get joined into one triangle
	glBegin(GL_TRIANGLES);
	// set the colour of the first vertex
	glColor3ub(255, 0, 0);
	// set the position of the first vertex
	glVertex3d(-Scene::GetWindowWidth() / 3, -Scene::GetWindowHeight() / 4, -2.0);
	// set the colour of the second vertex
	glColor3f(0, 1.0, 0);
	// set the position of the second vertex
	glVertex3d(Scene::GetWindowWidth() / 3, -Scene::GetWindowHeight() / 4, -2.0);
	// set the colour of the third vertex
	glColor3ub(0, 0, 255);
	// set the position of the third vertex
	glVertex3d(0.0, Scene::GetWindowHeight() / 3, -2.0);
	// stop drawing triangles
	glEnd();

	// re-enable face culling for other objects in the scene
	glEnable(GL_CULL_FACE);

	// revert back to the matrix we had before we added the triangles transforms so that other objects 
	// in the scene are not effected by the triangles transformations
	glPopMatrix();
}

void Triangle::Update(const double& deltaTime)
{
	zrot += 10.0f*(float)deltaTime;
}

void Triangle::HandleKey(unsigned char key, int state, int x, int y)
{	// set some rotation variables based on a key press
	switch (key) {
	case 'i':
		scale += 0.1f;
		break;
	case 'k':
		scale -= 0.1f;
		break;
	default:
		break;
	}
}
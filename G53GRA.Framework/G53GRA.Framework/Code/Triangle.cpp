#include "Triangle.h"

/// initalise the triangles properties
Triangle::Triangle() : xrot(0.0f), yrot(0.0f), zrot(0.0f), scale(0.5f){}

/// draw the triangle in the scene
void Triangle::Display()
{
	glPushMatrix();

	glTranslatef(0.0f, 0.0f, 0.0f);

	// rotate the triangle by the given degrees
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);

	// scale the traingle
	glScalef(0.5f, scale, 0.5f);

	// disable culling (removal) of backface triangles so that when we look at
	// triangle to does not disappearthe back of the
	glDisable(GL_CULL_FACE);

	// draw the triangle us GL_TRIANGLES as the primative so that every 3
	// joined into one triangle verticies we pass get
	glBegin(GL_TRIANGLES);

	// set the colour of the first vertex
	glColor3f(1.0f, 0.0f, 0.0f);
	// set the position of the first vertex
	glVertex3d(static_cast<float>(-Scene::GetWindowWidth()) / 3.0f, -Scene::GetWindowHeight() / 4.0f, -2.0);

	// set the colour of the second vertex
	glColor3f(0.0f, 1.0f, 0.0f);
	// set the position of the second vertex
	glVertex3d(static_cast<float>(Scene::GetWindowWidth()) / 3.0f, -Scene::GetWindowHeight() / 4.0f, -2.0f);

	// set the colour of the third vertex
	glColor3f(0.0f, 0.0f, 1.0f);
	// set the position of the third vertex
	glVertex3d(0.0, Scene::GetWindowHeight() / 3.0f, -2.0f);

	// stop drawing triangles
	glEnd();

	// re-enable face culling for other objects in the scene
	glEnable(GL_CULL_FACE);

	// revert back to the matrix we had before we added the triangles transforms 
	// in the scene are not effected by the triangles transformations so that 
	// other objects 
	glPopMatrix();
}

/// update the Z rotation variable with change in time
void Triangle::Update(const double& deltaTime)
{
	zrot += 10.0f * static_cast<float>(deltaTime);
}

/// set scale variables based on a key press
void Triangle::HandleKey(unsigned char key, int state, int x, int y)
{
	switch (key)
	{
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
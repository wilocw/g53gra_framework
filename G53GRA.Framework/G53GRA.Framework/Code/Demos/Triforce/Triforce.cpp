#include "Triforce.h"


Triforce::Triforce() : xrot(0.f), yrot(0.f), zrot(0.f)
{
}


Triforce::~Triforce()
{
}

void Triforce::Display()
{
	// Push the current transform matrix
	// for now just put it at the start and end of each draw call you make
	glPushMatrix();

	// Place the object in the scene by moving it backwards into the screen
	//glTranslatef(0, 0, -500.f);

	// Scale up the object
	glScalef(50.f, 50.f, 50.f);

	// Apply an object space rotation 
	// this will rotate the object around its object space center
	glRotatef(zrot, 0.f, 0.f, 1.f);
	glRotatef(yrot, 0.f, 1.f, 0.f);
	glRotatef(xrot, 1.f, 0.f, 0.f);

	// Set the draw colour to yellow
	glColor3ub(127, 127, 0);

	// Draw the simple Triforce
	//DrawBasicTriforce();

	// Draw each section of the Triforce
	glColor3f(0.f, 0.f, 1.f); // blue
	Draw3DTriangle(-1.f, -1.f, 0.f);
	glColor3f(0.f, 1.f, 0.f); // green
	Draw3DTriangle(1.f, -1.f, 0.f);
	glColor3f(1.f, 0.f, 0.f); // red
	Draw3DTriangle(0.f, 1.f, 0.f);

	// Pop off the changes to the transform matrix
	glPopMatrix();
}

void Triforce::Update(const double& deltaTime)
{
	// A simple update function just so we can see what we're doing
	xrot += 5.f*(float)deltaTime;
	yrot += 12.f*(float)deltaTime;
	zrot += 14.f*(float)deltaTime;
}

void Triforce::DrawBasicTriforce()
{
	// Draw the Triforce in Object Space Coordinates
	/*
	Triangle coodinate: O is the origin/center of object space
	Polygons must be wond anti-clockwise so they are not culled

	A
	/   \
	B -O- C
	/  \ /  \
	D--- E ---F
	*/

	// Disable backface culling to see the back when it rotates
	glDisable(GL_CULL_FACE);

	// Enter triangle primitives
	glBegin(GL_TRIANGLES);

	// Set the face normals to point outwards
	// This is for lighting, which will be covered in a later lecture
	glNormal3d(0.f, 0.f, 1.f);

	// Draw top center face
	glVertex3d(0.f, 2.f, 0.f);    // A
	glVertex3d(-1.f, 0.f, 0.f);    // B
	glVertex3d(1.f, 0.f, 0.f);    // C

	// Draw bottom left face
	glVertex3d(-1.f, 0.f, 0.f);    // B
	glVertex3d(-2.f, -2.f, -0.f);    // D
	glVertex3d(0.f, -2.f, 0.f);    // E

	// Draw bottom right face
	glVertex3d(1.f, 0.f, 0.f);    // C
	glVertex3d(0.f, -2.f, 0.f);    // E
	glVertex3d(2.f, -2.f, 0.f);    // F

	// Stop triangle primitives
	glEnd();

	// Reactivate backface culling so that it works for other objects in the scene
	glEnable(GL_CULL_FACE);
}

void Triforce::Draw3DTriangle(float cx, float cy, float cz)
{
	// Draw a section of the Triforce in Object Space Coordinates
	/*
	Triangle coodinate: c' is the center of triangle (cx, cy, cz)
	Polygons must be wond anti-clockwise so they are not culled

	A---------B
	/ \       / \
	/   \  c' /   \
	C-----D---E-----F
	*/

	// Enter triangle primitives
	glBegin(GL_TRIANGLES);

	// Draw the front triangle
	// Set the front face normal to point outwards
	glNormal3d(0, 0, 1.f);
	// Draw the front face wond anti-clockwise
	glVertex3d(cx, cy + 1.f, cz + 0.5f);    // A
	glVertex3d(cx - 1.f, cy - 1.f, cz + 0.5f); // C
	glVertex3d(cx + 1.f, cy - 1.f, cz + 0.5f); // D

	// Draw the back triangle
	// Set the backface normal to point inwards
	glNormal3d(0, 0, -1.f);
	// Draw the back face wond clockwise
	glVertex3d(cx, cy + 1.f, cz - 0.5f);    // B
	glVertex3d(cx + 1.f, cy - 1.f, cz - 0.5f); // F
	glVertex3d(cx - 1.f, cy - 1.f, cz - 0.5f); // E

	// Stop triangle primitive mode
	glEnd();

	// Enter quadrilateral primitives
	glBegin(GL_QUADS);

	// Draw the bottom plane
	// Set the bottom planes normal to point down
	glNormal3d(0.f, -1.f, 0.f);
	// Draw the bottom plane wond anti-clockwise
	glVertex3d(cx - 1.f, cy - 1.f, cz + 0.5f); // C
	glVertex3d(cx - 1.f, cy - 1.f, cz - 0.5f); // E
	glVertex3d(cx + 1.f, cy - 1.f, cz - 0.5f); // F
	glVertex3d(cx + 1.f, cy - 1.f, cz + 0.5f); // D

	// Draw the left plane
	// Set the left planes normal to point up and left
	glNormal3d(-1.f, 1.f, 0.f);
	// Draw the left plane wond anti-clockwise
	glVertex3d(cx, cy + 1.f, cz - 0.5f);     // B
	glVertex3d(cx - 1.f, cy - 1.f, cz - 0.5f); // E
	glVertex3d(cx - 1.f, cy - 1.f, cz + 0.5f); // C
	glVertex3d(cx, cy + 1.f, cz + 0.5f);     // A

	// Draw the right plane
	// Set the right planes normal to point up and right
	glNormal3d(1.f, 1.f, 0.f);
	// Draw the right plane wond anti-clockwise
	glVertex3d(cx, cy + 1.f, cz + 0.5f);     // A
	glVertex3d(cx + 1.f, cy - 1.f, cz + 0.5f); // D
	glVertex3d(cx + 1.f, cy - 1.f, cz - 0.5f); // F
	glVertex3d(cx, cy + 1.f, cz - 0.5f);     // B

	glEnd();
}
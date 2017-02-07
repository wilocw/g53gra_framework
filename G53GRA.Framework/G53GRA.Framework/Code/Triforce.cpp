#include "Triforce.h"

/// initalise triforce variables
Triforce::Triforce() : xrot(0.0f), yrot(0.0f), zrot(0.0f){}

/// draw the triforce
void Triforce::Display()
{
	// Push the current transform matrix
	// for now just put it at the start and end of each draw call you make
	glPushMatrix();

	// Place the object in the scene by moving it backwards into the screen
	//glTranslatef(0.0f, 0.0f, -500.0f);

	// Scale up the object
	glScalef(50.0f, 50.0f, 50.0f);

	// Apply an object space rotation 
	// this will rotate the object around its object space center
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);

	// Set the draw colour to yellow
	glColor3ub(static_cast<GLubyte>(127), static_cast<GLubyte>(127), static_cast<GLubyte>(0));

	// Draw the simple Triforce
	//DrawBasicTriforce();

	// Draw each section of the Triforce

	glColor3f(0.0f, 0.0f, 1.0f); // blue
	Draw3DTriangle(-1.f, -1.f, 0.f);

	glColor3f(0.0f, 1.0f, 0.0f); // green
	Draw3DTriangle(1.0f, -1.0f, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f); // red
	Draw3DTriangle(0.0f, 1.0f, 0.0f);

	// Pop off the changes to the transform matrix
	glPopMatrix();
}

/// update the rotation of the triforce with respect to the change in time
void Triforce::Update(const double& deltaTime)
{
	// A simple update function just so we can see what we're doing
	xrot += 5.0f  * static_cast<float>(deltaTime);
	yrot += 12.0f * static_cast<float> (deltaTime);
	zrot += 14.0f * static_cast<float> (deltaTime);
}

/// draw 2D triforce
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
	glNormal3f(0.0f, 0.0f, 1.0f);

	// Draw top center face
	glColor3f(0.0f, 0.0f, 1.0f); // blue
	glVertex3f(0.0f, 2.0f, 0.0f);    // A
	glVertex3f(-1.0f, 0.0f, 0.0f);   // B
	glVertex3f(1.0f, 0.0f, 0.0f);    // C

	// Draw bottom left face
	glColor3f(0.0f, 1.0f, 0.0f); // green
	glVertex3f(-1.0f, 0.0f, 0.0f);   // B
	glVertex3f(-2.0f, -2.0f, -0.0f); // D
	glVertex3f(0.0f, -2.0f, 0.0f);   // E

	// Draw bottom right face
	glColor3f(1.0f, 0.0f, 0.0f); // red
	glVertex3f(1.0f, 0.0f, 0.0f);    // C
	glVertex3f(0.0f, -2.0f, 0.0f);   // E
	glVertex3f(2.0f, -2.0f, 0.0f);   // F

	// Stop triangle primitives
	glEnd();

	// Reactivate backface culling so that it works for other objects in the scene
	glEnable(GL_CULL_FACE);
}

/// draw 3D triforce
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
	glNormal3f(0.0f, 0.0f, 1.0f);
	// Draw the front face wond anti-clockwise
	glVertex3f(cx, cy + 1.0f, cz + 0.5f);		 // A
	glVertex3f(cx - 1.0f, cy - 1.0f, cz + 0.5f); // C
	glVertex3f(cx + 1.0f, cy - 1.0f, cz + 0.5f); // D

	// Draw the back triangle
	// Set the backface normal to point inwards
	glNormal3f(0.0f, 0.0f, -1.0f);
	// Draw the back face wond clockwise
	glVertex3f(cx, cy + 1.0f, cz - 0.5f);		 // B
	glVertex3f(cx + 1.0f, cy - 1.0f, cz - 0.5f); // F
	glVertex3f(cx - 1.0f, cy - 1.0f, cz - 0.5f); // E

	// Stop triangle primitive mode
	glEnd();

	// Enter quadrilateral primitives
	glBegin(GL_QUADS);

	// Draw the bottom plane
	// Set the bottom planes normal to point down
	glNormal3f(0.0f, -1.0f, 0.0f);
	// Draw the bottom plane wond anti-clockwise
	glVertex3f(cx - 1.0f, cy - 1.0f, cz + 0.5f); // C
	glVertex3f(cx - 1.0f, cy - 1.0f, cz - 0.5f); // E
	glVertex3f(cx + 1.0f, cy - 1.0f, cz - 0.5f); // F
	glVertex3f(cx + 1.0f, cy - 1.0f, cz + 0.5f); // D

	// Draw the left plane
	// Set the left planes normal to point up and left
	glNormal3f(-1.0f, 1.0f, 0.0f);
	// Draw the left plane wond anti-clockwise
	glVertex3f(cx, cy + 1.0f, cz - 0.5f);		// B
	glVertex3f(cx - 1.0f, cy - 1.0f, cz - 0.5f);// E
	glVertex3f(cx - 1.0f, cy - 1.0f, cz + 0.5f);// C
	glVertex3f(cx, cy + 1.0f, cz + 0.5f);       // A

	// Draw the right plane
	// Set the right planes normal to point up and right
	glNormal3f(1.0f, 1.0f, 0.0f);
	// Draw the right plane wond anti-clockwise
	glVertex3f(cx, cy + 1.0f, cz + 0.5f);		// A
	glVertex3f(cx + 1.0f, cy - 1.0f, cz + 0.5f);// D
	glVertex3f(cx + 1.0f, cy - 1.0f, cz - 0.5f);// F
	glVertex3f(cx, cy + 1.0f, cz - 0.5f);		// B

	glEnd();
}
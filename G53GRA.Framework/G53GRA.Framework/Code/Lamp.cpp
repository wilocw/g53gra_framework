#include "Lamp.h"
#include "LampMesh.h"

#include <cmath>

// define a gravity constance for the bounce equation
#define GRAVITY -9.8f

/*
Linear interpolation between point A and B is used to decide where we are
between these two at time T.

NewPosition = startPosition + currentTime*[(distanceBetweenAandB)/totalTime];
or
NewPos = A + T*[(B-A)/totalTime]
(NewPos = interpA + animateRotation*[(interpB-interpA)/interpTime])

interpA is the position where the animation starts, in this case -15.
interpB is the position where it end, in this case -45.

interpTime is the total amount of time taken to move between the two
positions, in this case 1.75 seconds.

Then animateRotation keep track of the amount of time passed between starting
and ending the animation.
*/

// MAKE SURE WE INITIALISE OUR VARIABLES
Lamp::Lamp() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0),
interpA(0.0), interpB(0.0), interpTime(0.0){}

/// Update the lamps position in releation to delta time by use of mathematical
/// mechanics, eq SUVAT
void Lamp::Update(const double& deltaTime)
{
	// update the time and rotation steps
	animateTime += static_cast<float>(deltaTime);
	animateRotation += static_cast<float>(deltaTime);

	// check if we hit the end of the animation (3 seconds), if so reset
	if (animateTime >= 3.0f)
	{
		animateTime = 0.0f;
		keyframe = -1;
	}

	// check if we are in the 1st second of animation
	if (animateTime < 1.0f)
	{
		// check if we have only just entered the 1st keyframe in which case
		// set up the parameters
		if (keyframe != 0)
		{
			animateTime = 0.0f;
			animateRotation = 0.0f;
			animateTranslation = 0.0f;
			keyframe = 0;
			interpA = -45.0f;
			interpB = -60.0f;
			interpTime = 1.0f;
		}
	}
	// check if we are in the 1.0 to 1.25 seconds of animation
	else if (animateTime < 1.25f)
	{
		// check if we have only just entered the 2nd keyframe in which case 
		// set up the parameters
		if (keyframe != 1)
		{
			keyframe = 1;
			animateRotation = 0.0f;
			interpA = -60.0f;
			interpB = -15.0f;
			interpTime = 0.25f;
		}

		/*
		motion equations are usually referred to as the "SUVAT" equations.
		"SUVAT" is an acronym from the variables:
			S = displacement (s0 = initial displacement),
			U = initial velocity,
			V = final velocity,
			A = acceleration,
			T = time.
		*/

		// update the height value of the bounce using the suvat equation 
		// s = u*t + 1/2*a*t^2, let t = (animateTime-1.0)

		animateTranslation = 4.0f * -GRAVITY * (animateTime - 1.0f) + 0.5f * (animateTime - 1.0f) * (animateTime - 1.0f) * 4.0f * GRAVITY;
	}
	// check if we are in the 1.25 to 3 seconds of animation
	else
	{
		// check if we have only just entered the 3rd keyframe
		// in which case set up the parameters
		if (keyframe != 2)
		{
			keyframe = 2;
			animateRotation = 0.0f;
			interpA = -15.0f;
			interpB = -45.0f;
			interpTime = 1.75f;
		}

		// continue to update the height value of the bounce by solving the 
		// suvat equation s = u*t + 1/2*a*t^2

		animateTranslation = 4.0f * -GRAVITY * (animateTime - 1.0f) + 0.5f *(animateTime - 1.0f) * (animateTime - 1.0f) * 4.0f * GRAVITY;
	}
}

///Draw the lamp
void Lamp::Display()
{
	// Always push before making any changes
	glPushMatrix();

	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// Set colour to pale grey
	glColor3ub(250, 250, 250);

	//gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, -50.0, 0.0, 1.0, 0.0);

	//glTranslatef(0.0f, 0.0f, -500.0f);
	//glScalef(12.0f, 12.0f, 12.0f);


	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	glTranslatef(0.0f, -25.0f + animateTranslation, 0.0f);  // bouncing up and down

	// Draw base first
	DrawBase();

	glRotatef(interpA + animateRotation*((interpB - interpA) / interpTime), 0.0f, 0.0f, 1.0f);

	glTranslatef(0.0f, 8.0f, 0.0f);
	DrawArm();

	glTranslatef(0.0f, 7.0f, 0.0f);

	glRotatef(2.0f*(-interpA - animateRotation*((interpB - interpA) / interpTime)), 0.0f, 0.0f, 1.0f);

	glTranslatef(0.0f, 7.0f, 0.0f);
	DrawArm();

	glTranslatef(0.0f, 5.0f, 0.0f);
	glRotatef(-25.0f, 0.0f, 1.0f, 0.0f);
	DrawHead();

	// Revert style attributes
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing
	glPopMatrix();
}

/// Draw the base of the lamp
void Lamp::DrawBase()
{
	// This function scales a cube to draw the base elemet of the lamp
	glPushMatrix();
	glScalef(10.0f, 1.0f, 10.0f);
	DrawCube();
	glPopMatrix();
}

/// Draw the arm of the lamp
void Lamp::DrawArm()
{
	// This function scales a cube to draw an arm elemet of the lamp
	glPushMatrix();
	glScalef(2.0f, 15.0f, 2.0f);
	DrawCube();
	glPopMatrix();
}

/// Draw a cube with normals
void Lamp::DrawCube()
{
	// This function draws a unit cube centered around the origin

	glBegin(GL_QUADS);
	// Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	// Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	// Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	// Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	// Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	// Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();
}

/// Draw the head of the lamp
void Lamp::DrawHead()
{
	// This function scales a head mesh to draw the head of the lamp
	// Do not worry if you do not understand this, it is not strictly required 
	// for the course, however I've left the code here incase anyone is interested

	const float* HeadNorms = LampMesh::GetHeadNorms();
	const float* HeadVertex = LampMesh::GetHeadVertices();
	const int* FaceNorms = LampMesh::GetFaceNorms();
	const int* FaceVertex = LampMesh::GetFaceVertices();

	glPushMatrix();

	glScalef(8.0f, 8.0f, 8.0f);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < NUMBER_LAMP_HEAD_FACES; i++)
	{
		for (int v = 0; v < 3; v++)
		{
			glNormal3f(HeadNorms[(FaceNorms[i * 3 + v] - 1) * 3], HeadNorms[(FaceNorms[i * 3 + v] - 1) * 3 + 1], HeadNorms[(FaceNorms[i * 3 + v] - 1) * 3 + 2]);
			glVertex3f(HeadVertex[(FaceVertex[i * 3 + v] - 1) * 3], HeadVertex[(FaceVertex[i * 3 + v] - 1) * 3 + 1], HeadVertex[(FaceVertex[i * 3 + v] - 1) * 3 + 2]);
		}
	}
	glEnd();

	glPopMatrix();
}
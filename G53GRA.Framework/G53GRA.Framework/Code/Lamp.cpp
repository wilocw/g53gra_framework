#include "Lamp.h"
#include "LampMesh.h"

#include <cmath>

// define a gravity constance for the bounce equation
#define GRAVITY -9.8f

/*
Linear interpolation between point A and B is used to decide where we are between these two at time T.

NewPosition = startPosition + currentTime*[(distanceBetweenAandB)/totalTime];
or
NewPos = A + T*[(B-A)/totalTime]
(NewPos = interpA + animateRotation*[(interpB-interpA)/interpTime])

interpA is the position where the animation starts, in this case -15.
interpB is the position where it end, in this case -45.
interpTime is the total amount of time taken to move between the two positions, in this case 1.75 seconds.

Then animateRotation keep track of the amount of time passed between starting and ending the animation.
*/

// MAKE SURE WE INITIALISE OUR VARIABLES
Lamp::Lamp() : keyframe(-1), animateTime(0.0), animateRotation(0.0), animateTranslation(0.0), interpA(0.0), interpB(0.0), interpTime(0.0)
{
}


Lamp::~Lamp()
{
}


void Lamp::Update(const double& deltaTime)
{
	animateTime += static_cast<float>(deltaTime);                   // update the time and rotation steps
	animateRotation += static_cast<float>(deltaTime);

	if (animateTime >= 3.f)                    // check if we hit the end of the animation (3 seconds)
	{                                           // if so reset
		animateTime = 0.f;
		keyframe = -1;
	}

	if (animateTime < 1.f)                     // check if we are in the 1st second of animation
	{
		if (keyframe != 0)                     // check if we have only just entered the 1st keyframe
		{                                       // in which case set up the parameters
			animateTime = 0.f;
			animateRotation = 0.f;
			animateTranslation = 0.f;
			keyframe = 0;
			interpA = -45.f;
			interpB = -60.f;
			interpTime = 1.f;
		}
	}
	else if (animateTime < 1.25)               // check if we are in the 1.0 to 1.25 seconds of animation
	{
		if (keyframe != 1)                     // check if we have only just entered the 2nd keyframe
		{                                       // in which case set up the parameters
			keyframe = 1;
			animateRotation = 0.f;
			interpA = -60.f;
			interpB = -15.f;
			interpTime = 0.25f;
		}

		/*
		motion equations are usually referred to as the "SUVAT" equations. "SUVAT" is an acronym from the variables:
		S = displacement (s0 = initial displacement), U = initial velocity, V = final velocity, A = acceleration, T = time.
		*/

		// update the height value of the bounce using the suvat equation s = u*t + 1/2*a*t^2
		// let t = (animateTime-1.0)

		animateTranslation = 4.f*-GRAVITY*(animateTime - 1.f) + 0.5f*(animateTime - 1.f)*(animateTime - 1.f)*4.f*GRAVITY;
	}
	else                                        // check if we are in the 1.25 to 3 seconds of animation
	{
		if (keyframe != 2)                     // check if we have only just entered the 3rd keyframe
		{                                       // in which case set up the parameters
			keyframe = 2;
			animateRotation = 0.f;
			interpA = -15.f;
			interpB = -45.f;
			interpTime = 1.75f;
		}

		// continue to update the height value of the bounce by solving the suvat equation s = u*t + 1/2*a*t^2

		animateTranslation = 4.f*-GRAVITY*(animateTime - 1.f) + 0.5f*(animateTime - 1.f)*(animateTime - 1.f)*4.f*GRAVITY;
	}
}


void Lamp::Display()
{
	// Always push before making any changes
	glPushMatrix();

    // Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS); 
	// Set colour to pale grey
	glColor3ub(250, 250, 250);

	//gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, -50.0, 0.0, 1.0, 0.0);

	//glTranslated(0.0, 0.0, -500.0);
	//glScalef(12.0, 12.0, 12.0);


	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	glTranslated(0, -25.0 + animateTranslation, 0.0);  // bouncing up and down
	
	// Draw base first
	DrawBase();

	glRotated(interpA + animateRotation*((interpB - interpA) / interpTime), 0.0, 0.0, 1.0);

	glTranslated(0.0, 8.0, 0.0);
	DrawArm();

	glTranslated(0.0, 7.0, 0.0);

	glRotated(2.0*(-interpA - animateRotation*((interpB - interpA) / interpTime)), 0.0, 0.0, 1.0);

	glTranslated(0.0, 7.0, 0.0);
	DrawArm();

	glTranslated(0.0, 5.0, 0.0);
	glRotated(-25.0, 0.0, 1.0, 0.0);
	DrawHead();
	
	// Revert style attributes
	glPopAttrib();

	// pop matrix stack to revert to state prior to drawing
	glPopMatrix();
}


void Lamp::DrawBase()
{
	// This function scales a cube to draw the base elemet of the lamp
	glPushMatrix();
	glScaled(10.0, 1.0, 10.0);
	DrawCube();
	glPopMatrix();
}

void Lamp::DrawArm()
{
	// This function scales a cube to draw an arm elemet of the lamp
	glPushMatrix();
	glScaled(2.0, 15.0, 2.0);
	DrawCube();
	glPopMatrix();
}

void Lamp::DrawCube()
{
	// This function draws a unit cube centered around the origin

	glBegin(GL_QUADS);
	// Front
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3d(-0.5, -0.5, 0.5);
	glVertex3d(0.5, -0.5, 0.5);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(-0.5, 0.5, 0.5);
	// Back
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3d(-0.5, -0.5, -0.5);
	glVertex3d(-0.5, 0.5, -0.5);
	glVertex3d(0.5, 0.5, -0.5);
	glVertex3d(0.5, -0.5, -0.5);
	// Left
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3d(-0.5, -0.5, -0.5);
	glVertex3d(-0.5, -0.5, 0.5);
	glVertex3d(-0.5, 0.5, 0.5);
	glVertex3d(-0.5, 0.5, -0.5);
	// Right
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3d(0.5, -0.5, 0.5);
	glVertex3d(0.5, -0.5, -0.5);
	glVertex3d(0.5, 0.5, -0.5);
	glVertex3d(0.5, 0.5, 0.5);
	// Top
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3d(-0.5, 0.5, 0.5);
	glVertex3d(0.5, 0.5, 0.5);
	glVertex3d(0.5, 0.5, -0.5);
	glVertex3d(-0.5, 0.5, -0.5);
	// Bottom
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3d(-0.5, -0.5, 0.5);
	glVertex3d(-0.5, -0.5, -0.5);
	glVertex3d(0.5, -0.5, -0.5);
	glVertex3d(0.5, -0.5, 0.5);
	glEnd();
}

void Lamp::DrawHead()
{
	// This function scales a head mesh to draw the head of the lamp
	// Do not worry if you do not understand this, it is not strictly required for the course,
	// However I've left the code here incase anyone is interested

	const float* HeadNorms = LampMesh::GetHeadNorms();
	const float* HeadVertex = LampMesh::GetHeadVertices();
	const int* FaceNorms = LampMesh::GetFaceNorms();
	const int* FaceVertex = LampMesh::GetFaceVertices();

	glPushMatrix();

	glScaled(8.0, 8.0, 8.0);

	glBegin(GL_TRIANGLES);
	for (int i = 0; i<NUMBER_LAMP_HEAD_FACES; i++)
	{
		for (int v = 0; v<3; v++)
		{
			glNormal3f(HeadNorms[(FaceNorms[i * 3 + v] - 1) * 3], HeadNorms[(FaceNorms[i * 3 + v] - 1) * 3 + 1], HeadNorms[(FaceNorms[i * 3 + v] - 1) * 3 + 2]);
			glVertex3d(HeadVertex[(FaceVertex[i * 3 + v] - 1) * 3], HeadVertex[(FaceVertex[i * 3 + v] - 1) * 3 + 1], HeadVertex[(FaceVertex[i * 3 + v] - 1) * 3 + 2]);
		}
	}
	glEnd();

	glPopMatrix();
}
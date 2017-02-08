
#include "Planet2.h"

Planet2::Planet2(double size, float distanceFromSun, float axisRotationSpeed, float orbitRotationSpeed,
				 float moonSize, float distMoonFromPlanet, float moonAxisSpeed, float moonOrbitSpeed) :
	r(255), g(0), b(0), radius(size), distanceFromSun(distanceFromSun), axisRotationSpeed(axisRotationSpeed),
	orbitRotationSpeed(orbitRotationSpeed), axisRotation(0.0f), orbitRotation(0.0f), moonRadius(moonSize),
	distanceMoonFromPlanet(distMoonFromPlanet), moonAxisRotSpeed(moonAxisSpeed), moonOrbitRotSpeed(moonOrbitSpeed),
	moonAxisRot(0.0f), moonOrbitRot(0.0f){}

void Planet2::SetColour(unsigned char r, unsigned char g, unsigned b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}

void Planet2::Display()
{
	// remember the state of the model view matrix before we entered the 
	// function
	glPushMatrix();

	/*-------------------------------------------------------------------------
	----------------------ORDER OF ROTATIONS IS IMPORTANT----------------------
	-------------------------------------------------------------------------*/

	// rotate the planet around its orbit
	glRotatef(orbitRotation, 0.0f, 1.0f, 0.0f);
	// translate the planet from its center out onto it's obriting path
	glTranslatef(0.0f, 0.0f, -distanceFromSun);
	// rotate the planet around its origin
	glRotatef(axisRotation, 0.0f, 1.0f, 0.0f);

	// Use an inner push and pop to apply transforms only to the moon but NOT 
	// to the planet
	glPushMatrix();

	/*-------------------------------------------------------------------------
	----------------------ORDER OF ROTATIONS IS IMPORTANT----------------------
	-------------------------------------------------------------------------*/

	// rotate the moon around the planet
	glRotatef(moonOrbitRot, 0.0f, 1.0f, 0.0f);
	// translate the moon from its center out onto it's obriting path of the 
	// planet
	glTranslatef(0.0f, 0.0f, -distanceMoonFromPlanet);
	// rotate the moon around its origin/axis
	glRotatef(moonAxisRot, 0.0f, 1.0f, 0.0f);

	// set the colour we wish to draw the moon in
	glColor3ub(137, 137, 137);
	// use a function from glut to draw a sphere representing the moon.
	glutSolidSphere(moonRadius, static_cast<GLint>(10), static_cast<GLint>(10));
	glPopMatrix();

	// set the colour we wish to draw the planet in
	glColor3ub(r, g, b);

	// use glut function to draw a sphere with given radius
	// here the last 2 parameters refer to how accurately we draw the sphere
	// they supply the number of stack and number of slices we wish to use
	// this higher this number the more triangle we use to more accuratly 
	// represent the sphere
	// N.B. The more triangle we use the slower are program is at drawing the 
	// scene as there is more data to process, always try to keep your poly 
	// count low.
	glutSolidSphere(radius, static_cast<GLint>(12), static_cast<GLint>(12));

	// pop off the changed we made to the model view matrix to leave the 
	// function in the same state that we entered
	glPopMatrix();
}

void Planet2::Update(const double& deltaTime)
{
	// update the axis and orbit rotation variables based on the amount of time that has passed
	// between drawring consective frames and the speed at which the rotation should occur

	axisRotation += axisRotationSpeed*static_cast<float>(deltaTime);
	if (axisRotation >= 360.0f)
	{
		axisRotation = axisRotation - 360.0f;
	}
	orbitRotation += orbitRotationSpeed*static_cast<float>(deltaTime);
	if (orbitRotation >= 360.0f)
	{
		orbitRotation = orbitRotation - 360.0f;
	}

	moonAxisRot += moonAxisRotSpeed*static_cast<float>(deltaTime);
	if (moonAxisRot >= 360.0f)
	{
		moonAxisRot = moonAxisRot - 360.0f;
	}
	moonOrbitRot += moonOrbitRotSpeed*static_cast<float>(deltaTime);
	if (moonOrbitRot >= 360.0f)
	{
		moonOrbitRot = moonOrbitRot - 360.0f;
	}
}
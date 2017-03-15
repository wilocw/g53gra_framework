#include "MultiLight.h"

#include <cmath>

MultiLight::MultiLight() :
	_runtime(0.0), _radius(200.0), _flagVisualise(false),
	_showLight0(true), _showLight1(true), _showLight2(true), _showLight3(true)
{
	/*====================================================================================
	 * POSITION PARAMETER (x,y,z,p)
	 *====================================================================================*/
	// Direction Light (the 4th component is 0): like the sun, rays are parallel and every
	// thing is light as though the light hit it at a given direction.
	// Positional Light (the 4th component is 1): like a lamp in a room, objects are light
	// based on the position and distance from the light source.
	static GLfloat position[] =
	{
		// LIGHT 0 (directional light)
		1.0f, 1.0f, 1.0f, 0.0f,
		// LIGHT 1 (positional light)
		static_cast<GLfloat>(_radius), 0.0f, 0.0f, 1.0f,
		// LIGHT 2 (positional light)
		-static_cast<GLfloat>(_radius), 0.0f, 0.0f, 1.0f,
		// LIGHT 3 (positional light)
		static_cast<GLfloat>(_radius), 0.0f, 0.0f, 1.0f,
	};
	_position = position;
	/*====================================================================================
	* AMBIENT PARAMETER (r,g,b,a)
	*====================================================================================*/
	// Ambient light is the basic uniform lighting that a source gives up, regardless of
	// direction. Normally, this is set to a low intensity version of the diffuse colour.
	static GLfloat ambient[] =
	{
		// LIGHT 0 (dull yellow)
		0.15f, 0.15f, 0.0f, 1.0f,
		// LIGHT 1 (dark red)
		0.15f, 0.0f, 0.0f, 1.0f,
		// LIGHT 2 (dark green)
		0.0f, 0.15f, 0.0f, 1.0f,
		// LIGHT 3 (dark blue)
		0.0f, 0.0f, 0.25f, 1.0f
	};
	_ambient = ambient;
	/*====================================================================================
	* DIFFUSE PARAMETER (r,g,b,a)
	*====================================================================================*/
	// Diffuse is the main lighting colour, that is dependent of directional parameters.
	static GLfloat diffuse[] =
	{
		// LIGHT 0 (yellow)
		0.5f, 0.5f, 0.0f, 1.0f,
		// LIGHT 1 (bright red)
		1.0f, 0.0f, 0.0f, 1.0f,
		// LIGHT 2 (deep green)
		0.0f, 0.8f, 0.0f, 1.0f,
		// LIGHT 3 (bright blue)
		0.0f, 0.0f, 0.9f, 1.0f
	};
	_diffuse = diffuse;
	/*===================================================================================
	* SPECULAR PARAMETER (r,g,b,a)
	*====================================================================================*/
	// The specular parameter describes the colour of specular highlights (controlled by
	// the shininess material value of the surface).
	static GLfloat specular[] =
	{
		// LIGHT 0 (bright white)
		1.0f, 1.0f, 1.0f, 1.0f,
		// LIGHT 1 (bright red)
		1.0f, 0.0f, 0.0f, 1.0f,
		// LIGHT 2 (bright green)
		0.0f, 1.0f, 0.0f, 1.0f,
		// LIGHT 3 (bright blue)
		0.0f, 0.0f, 1.0f, 1.0f
	};
	_specular = specular;
}


MultiLight::~MultiLight()
{

}

void MultiLight::Display()
{
	// If light source visualisation off, do not display.
	if (!_flagVisualise) return;

	// Basic code to draw the position and direction of the light.
	// This is not suitable for a directional light source, as a 
	// directional light has no position (LIGHT 0)
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);

	if (_showLight1)
	{
	// Draw LIGHT 1 (red light)
		glPushMatrix();
			glColor4fv(&_diffuse[_LIGHT_1]);
			glTranslatef(_position[_LIGHT_1 + 0], _position[_LIGHT_1 + 1], _position[_LIGHT_1 + 2]);
			glutSolidSphere(10.0, 10, 10);
		glPopMatrix();
	}

	if (_showLight2)
	{
	// Draw LIGHT 2 (green light)
		glPushMatrix();
			glColor4fv(&_diffuse[_LIGHT_2]);
			glTranslatef(_position[_LIGHT_2 + 0], _position[_LIGHT_2 + 1], _position[_LIGHT_2 + 2]);
			glutSolidSphere(10.0, 10, 10);
		glPopMatrix();
	}

	if (_showLight3)
	{
	// Draw LIGHT 3 (blue light)
		glPushMatrix();
			glColor4fv(&_diffuse[_LIGHT_3]);
			glTranslatef(_position[_LIGHT_3 + 0], _position[_LIGHT_3 + 1], _position[_LIGHT_3 + 2]);
			glutSolidSphere(10.0, 10, 10);
		glPopMatrix();
	}
	
	glEnable(GL_LIGHTING);
	glPopAttrib();
}

void MultiLight::Update(const double& deltaTime)
{
	_runtime += deltaTime;
	// Update positions of positonal lights (1,2, and 3)
	_position[_LIGHT_1 + 0] = static_cast<GLfloat>(_radius*cos(_runtime - 1.5));
	_position[_LIGHT_1 + 1] = static_cast<GLfloat>(_radius*sin(_runtime - 1.5));

	_position[_LIGHT_2 + 0] = -static_cast<GLfloat>(_radius*cos(_runtime));
	_position[_LIGHT_2 + 1] = -static_cast<GLfloat>(_radius*sin(_runtime));

	_position[_LIGHT_3 + 0] = static_cast<GLfloat>(_radius*cos(_runtime));
	_position[_LIGHT_3 + 1] = static_cast<GLfloat>(_radius*sin(_runtime));

	// Enable lighting to display effects of these lights by default
	glEnable(GL_LIGHTING);

	/*===================================================================================
	* LIGHT 0 : Yellow Directional Light
	*====================================================================================*/
	glLightfv(GL_LIGHT0, GL_POSITION, &_position[_LIGHT_0]);
	glLightfv(GL_LIGHT0, GL_AMBIENT, &_ambient[_LIGHT_0]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &_diffuse[_LIGHT_0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &_specular[_LIGHT_0]);
	// If _showLight, enable GL_LIGHT, else disable it
	_showLight0 ? glEnable(GL_LIGHT0) : glDisable(GL_LIGHT0);

	/*===================================================================================
	* LIGHT 1 : Red Positional Light
	*====================================================================================*/
	glLightfv(GL_LIGHT1, GL_POSITION, &_position[_LIGHT_1]);
	glLightfv(GL_LIGHT1, GL_AMBIENT, &_ambient[_LIGHT_1]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, &_diffuse[_LIGHT_1]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, &_specular[_LIGHT_1]);
	// Set the lights attentuation i.e. how quickly the light fades as it moves away
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0025f);
	// If _showLight, enable GL_LIGHT, else disable it
	_showLight1 ? glEnable(GL_LIGHT1) : glDisable(GL_LIGHT1);

	/*===================================================================================
	* LIGHT 2 : Green Positional Light
	*====================================================================================*/
	glLightfv(GL_LIGHT2, GL_POSITION, &_position[_LIGHT_2]);
	glLightfv(GL_LIGHT2, GL_AMBIENT, &_ambient[_LIGHT_2]);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, &_diffuse[_LIGHT_2]);
	glLightfv(GL_LIGHT2, GL_SPECULAR, &_specular[_LIGHT_2]);
	// Set the lights attentuation i.e. how quickly the light fades as it moves away
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0025f);
	// If _showLight, enable GL_LIGHT, else disable it
	_showLight2 ? glEnable(GL_LIGHT2) : glDisable(GL_LIGHT2);

	/*===================================================================================
	* LIGHT 3 : Blue Positional Light
	*====================================================================================*/
	glLightfv(GL_LIGHT3, GL_POSITION, &_position[_LIGHT_3]);
	glLightfv(GL_LIGHT3, GL_AMBIENT, &_ambient[_LIGHT_3]);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, &_diffuse[_LIGHT_3]);
	glLightfv(GL_LIGHT3, GL_SPECULAR, &_specular[_LIGHT_3]);
	// Set the lights attentuation i.e. how quickly the light fades as it moves away
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0005f);
	// If _showLight, enable GL_LIGHT, else disable it
	_showLight3 ? glEnable(GL_LIGHT3) : glDisable(GL_LIGHT3);
}

void MultiLight::HandleKey(unsigned char key, int state, int x, int y)
{
	// Ignore callback from key release (state == 0)
	if (!state) return;

	switch (key)
	{
	case '0':
		_showLight0 = _showLight1 = _showLight2 = _showLight3 = false;
		break;
	case '1':
		_showLight0 = !_showLight0;
		break;
	case '2':
		_showLight1 = !_showLight1;
		break;
	case '3':
		_showLight2 = !_showLight2;
		break;
	case '4':
		_showLight3 = !_showLight3;
		break;
	case 'p':
		ToggleVisualiseLights();
		break;
	}
}

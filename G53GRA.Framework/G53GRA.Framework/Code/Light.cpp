#include "Light.h"


Light::Light()
	: _lightSrc(GL_LIGHT0), _c_falloff(0.0f), _l_falloff(0.025f), _q_falloff(0.00005f), _flagVisualise(false)
{
	static GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_position = position;
}

Light::Light(GLenum lightSrc, GLfloat *ambient, GLfloat *diffuse, GLfloat *specular, GLfloat *position) : Light()
{
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_position = position;

	_lightSrc = lightSrc;
}

Light::~Light()
{

}


void Light::Display()
{
	if (!_flagVisualise) return;
	
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glDisable(GL_LIGHTING);
		glColor4fv(_diffuse);
		glTranslatef(_position[0], _position[1], _position[2]);
		
		glutSolidSphere(10.0, 10, 10);

	glEnable(GL_LIGHTING);

	glPopAttrib();
	glPopMatrix();

}

void Light::Update(const double& deltaTime)
{
	glEnable(GL_LIGHTING);
	// Colour
	glLightfv(_lightSrc, GL_AMBIENT, _ambient);
	glLightfv(_lightSrc, GL_DIFFUSE, _diffuse);
	glLightfv(_lightSrc, GL_SPECULAR, _specular);

	// Position
	glLightfv(_lightSrc, GL_POSITION, _position);

	// Fall off
	
	glLightf(_lightSrc, GL_CONSTANT_ATTENUATION, _c_falloff);
	glLightf(_lightSrc, GL_LINEAR_ATTENUATION, _l_falloff);
	glLightf(_lightSrc, GL_QUADRATIC_ATTENUATION, _q_falloff);
	

	/*
	GLfloat spotdir[] = { 0.0f, 0.0f, -1.0f, 0.0f };

	glLightfv(_lightSrc, GL_SPOT_DIRECTION, spotdir);
	glLightf(_lightSrc, GL_SPOT_EXPONENT, 4.0f);
	glLightf(_lightSrc, GL_SPOT_CUTOFF, 60.0f);
	*/
	glEnable(_lightSrc);
}

void Light::HandleKey(unsigned char key, int state, int mx, int my)
{
	if (key == 'x' && state) ToggleVisualisation();
}
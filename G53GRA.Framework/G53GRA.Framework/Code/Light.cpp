#include "Light.h"


Light::Light()
	: _runtime(0.0), _radius(200.0), _positionalLight(1.0f)
{
	// Set ambient colour of the light (off-grey)
	static GLfloat ambient[] = { 0.15f, 0.15f, 0.1f, 1.0f };

	// Set diffuse colour of the light (red)
	static GLfloat diffuse[] = { 0.8f, 0.0f, 0.0f, 1.0f };

	// Set specular colour (white)
	static GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
}


Light::~Light()
{
}

void Light::Display()
{
	// Basic code to draw the position and direction of the light.
	// This is not suitable for a directional light source, as a 
	// directional light has no position.

	if (_positionalLight)
	{
		// Disable lighting on this geometry (since it is the source
		// of the light) so it will only be coloured by glColor call
		glDisable(GL_LIGHTING);

		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			// Match colour of sphere to diffuse colour of light
			glColor4fv(_diffuse);
			glTranslatef(pos[0], pos[1], pos[2]);
			glutSolidSphere(10.0, 10, 10);
			glBegin(GL_LINES);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(-pos[0], -pos[1], -pos[2]);
			glEnd();
		glPopAttrib();
		glPopMatrix();
		// Re-enable lighting after light source has been drawn
		glEnable(GL_LIGHTING);
	}
}

void Light::Update(const double& deltaTime)
{
	_runtime += deltaTime;
	
	pos[0] = static_cast<float>(_radius*cos(_runtime));
	pos[1] = static_cast<float>(_radius*sin(_runtime));

	glEnable(GL_LIGHTING);

	/*	Lighting property settings:
	*		 glLightfv( GLenum light , GLenum pname , const GLfloat* params )
	*           |      ____________   ____________   _____________________
	* accepts float vector  |              |                   |
	*                specifies light       |           parameter values
	*             GL_LIGHTi for i=0..8     |      (as defined in constructor)
	*								 light parameter
	*					either GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR,
	*					     GL_POSITION or GL_SPOT_DIRECTION
	*
	* Some properties take only single value parameters, so you must use glLightf() instead
	* The following properties take single values only:
	*    GL_SPOT_EXPONENT (0..128), GL_SPOT_CUTOFF (0..90, 180), GL_CONSTANT_ATTENUATION,
	*        GL_LINEAR_ATTENUATION, and GL_QUADRATIC ATTENUATION
	*        GL_LINEAR_ATTENUATION, and GL_QUADRATIC ATTENUATION
	*/

	// Set properties GL_LIGHT0 (overwrites default global framework lighting)
	glLightfv(GL_LIGHT0, GL_AMBIENT, _ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, _diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, _specular);

	GLfloat lPosition[4] = { pos[0], pos[1], pos[2], _positionalLight };
	glLightfv(GL_LIGHT0, GL_POSITION, lPosition);

	// enable GL_LIGHT0 with these defined properties
	glEnable(GL_LIGHT0); 
}


void Light::HandleKey(unsigned char key, int state, int mx, int my)
{
	if (state && key == 'p') ToggleLightType();
}
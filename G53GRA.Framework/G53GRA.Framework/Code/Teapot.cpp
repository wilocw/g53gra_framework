#include "Teapot.h"


Teapot::Teapot()
	: _flagAnimation(true), _yrot(10.0f)
{ 
	// Define the ambient material colour property K_a
	static GLfloat mat_ambient[] = { 0.f, 0.f, 0.9f, 1.f };
	// Define the diffuse material colour property K_d
	static GLfloat mat_diffuse[] = { 0.9f, 0.0f, 0.0f, 1.f };
	// Define the specular material colour property K_s
	static GLfloat mat_specular[] = { 1.f, 1.f, 1.f, 1.f };
	// Define the shininess/specular exponent factor n ( capped between 0.0 and 128.0 )
	static GLfloat mat_shininess[] = { 100.0 };

	_mat_ambient = mat_ambient;
	_mat_diffuse = mat_diffuse;
	_mat_specular = mat_specular;
	_mat_shininess = mat_shininess;
}


Teapot::~Teapot()
{

}

void Teapot::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);

	glDisable(GL_COLOR_MATERIAL); // stops glColor affecting properties of surface

	/* Material property settings:
	*     glMaterialfv( GLenum face , GLenum pname , const GLfloat* params )
	*		     |       ___________   ____________   _____________________
	*  accepts float vector  |              |                  |
	*				   specifies face        |           parameter values
	*           either GL_FRONT or GL_BACK  |          (as defined above)
	*             or GL_FRONT_AND_BACK      |
	*                               material parameter
	*                   either GL_AMBIENT, GL_DIFFUSE, GL_SPECULAR
	*                GL_EMISSION, GL_SHININESS or GL_AMBIENT_AND_DIFFUSE
	*/

	// Material properties for OpenGL implementation of Phong reflectance model
	glMaterialfv(GL_FRONT, GL_AMBIENT, _mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, _mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, _mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, _mat_shininess);
	
	// Swap winding order for back face culling (so clockwise ordering is now considered front face)
	//    because glutSolidTeapot has the wrong polygon winding
	glFrontFace(GL_CW);
	// Draw solid teapot (with default normals)
	glutSolidTeapot(1.0); 
	// Revert to previous winding order (front face is now counterclockwise delared vertices)
	glFrontFace(GL_CCW);

	glPopAttrib();
	glPopMatrix();
}

void Teapot::Update(const double& deltaTime)
{
	if (!_flagAnimation) return;

	rotation[1] += _yrot*static_cast<float>(deltaTime);

	if (rotation[1] > 360.0f) rotation[1] -= 360.0f;

}
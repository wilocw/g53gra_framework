#include "TexturedSphere.h"
#include "VectorMath.h"

// Default Constructor
TexturedSphere::TexturedSphere()
	: _resolution(4), _flagWireFrame(false), _flagAnimation(true), _texID(NULL)
{
	// Octahedron vertices (used for initial triangle faces)
	static float vertices[] = 
	{
		1.0f, 0.0f, 0.0f,   // VERTEX 0
		0.0f, 0.0f, -1.0f,	// VERTEX 1
		-1.0f, 0.0f, 0.0f,	// VERTEX 2
		0.0f, 0.0f, 1.0f,	// VERTEX 3
		0.0f, 1.0f, 0.0f,	// VERTEX 4
		0.0f, -1.0f, 0.0f	// VERTEX 5
	 };
	// Globalise vertices
	_initV = vertices;
}

// Constructor with Texture filename
TexturedSphere::TexturedSphere(const std::string& filename) : TexturedSphere()
{
	SetTexture(filename);
}

void TexturedSphere::SetTexture(const std::string& filename)
{
	// Load texture using the provided Texture loader (.bmp only)
	_texID = Scene::GetTexture(filename);
}

void TexturedSphere::Display()
{
	// Push MODELVIEW matrix and attributes to respective stacks (save state)
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// Apply object transformations in world space
	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
	glScalef(scale[0], scale[1], scale[2]);

	// Enable texturing (2D image as texture)
	glEnable(GL_TEXTURE_2D);
	// Bind input texture to GL_TEXTURE_2D buffer
	glBindTexture(GL_TEXTURE_2D, _texID);
	// Handle lighting effects
	glEnable(GL_COLOR_MATERIAL);

	// Render sphere
	DrawSphere();

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Disable texturing
	glDisable(GL_TEXTURE_2D);

	// Pop matrix and attribute stack to revert transformation changes
	glPopAttrib();
	glPopMatrix();
}

void TexturedSphere::DrawSphere()
{
	// Subdivide each face of an octohedron (_resolution = number of divisions)
	// and then render the final subdivisions of each face
	// Top half
	SubDivide(_resolution, &_initV[_VERTEX3], &_initV[_VERTEX0], &_initV[_VERTEX4]);
	SubDivide(_resolution, &_initV[_VERTEX0], &_initV[_VERTEX1], &_initV[_VERTEX4]);
	SubDivide(_resolution, &_initV[_VERTEX1], &_initV[_VERTEX2], &_initV[_VERTEX4]);
	SubDivide(_resolution, &_initV[_VERTEX2], &_initV[_VERTEX3], &_initV[_VERTEX4]);
	// Bottom half
	SubDivide(_resolution, &_initV[_VERTEX0], &_initV[_VERTEX3], &_initV[_VERTEX5]);
	SubDivide(_resolution, &_initV[_VERTEX1], &_initV[_VERTEX0], &_initV[_VERTEX5]);
	SubDivide(_resolution, &_initV[_VERTEX2], &_initV[_VERTEX1], &_initV[_VERTEX5]);
	SubDivide(_resolution, &_initV[_VERTEX3], &_initV[_VERTEX2], &_initV[_VERTEX5]);
}

void TexturedSphere::SubDivide(int recurse_idx, float *a, float *b, float *c)
{
	// Calcuate mid point between each pair of triangle vertices (a,b,c)
	float ab[3] = { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
	float bc[3] = { b[0] + c[0], b[1] + c[1], b[2] + c[2] };
	float ca[3] = { c[0] + a[0], c[1] + a[1], c[2] + a[2] };

	// Normalise to vertices to have ||x|| = 1
	norm(ab);
	norm(bc);
	norm(ca);
	
	// Recursively subdivide faces
	if (recurse_idx > 1)
	{
		/*
		      a						 a
			 /\  					 /\
		    /  \ 				 ca	/__\ ab
		   /    \       --->       /\  /\
	    c /______\ b			c /__\/__\ b
								     bc	
		*/
		SubDivide(recurse_idx - 1, a, ab, ca);
		SubDivide(recurse_idx - 1, ab, b, bc);
		SubDivide(recurse_idx - 1, ca, bc, c);
		SubDivide(recurse_idx - 1, ca, ab, bc);
	}
	// Draw final subdivision faces
	else
	{
		/*
		     a
			 /\
		ca	/__\ ab
		   /\  /\
	    c /__\/__\ b
			 bc	
		*/
		DrawFace(a, ab, ca);
		DrawFace(ab, b, bc);
		DrawFace(ca, bc, c);
		DrawFace(ca, ab, bc);
	}
}

void TexturedSphere::DrawFace(float *a, float *b, float *c)
{
	//  a[0], a[1], and a[2] are the X, Y and Z values of the normal (so too for b and c)
	// atan2 is used to convert that to an angle, which is between -PI and PI. divide it 
	// by 2PI to restrict it to between -0.5 and 0.5. add 0.5 to make it range from 0 to 1
	// to get the (s) values in the texture map.	

	// Index texture coordinate (s,t) for vertex a (convert to angle and index between 0 and 1)
	float sa = 0.5f - atan2f(a[2], a[0]) / (2.0f*M_PI);
	float ta = 0.5f + asinf(a[1]) / M_PI;
	
	// Index texture coordinate (s,t) for vertex b (convert to angle and index between 0 and 1)
	float sb = 0.5f - atan2f(b[2], b[0]) / (2.0f*M_PI);
	float tb = 0.5f + asinf(b[1]) / M_PI;

	// Index texture coordinate (s,t,) for vertex c( convert to angle and index between 0 and 1)
	float sc = 0.5f - atan2f(c[2], c[0]) / (2.0f*M_PI);
	float tc = 0.5f + asinf(c[1]) / M_PI;

	// Fix seam issue when texture face goes from 1 to 0 (wrap around)
	FixSeam(sa, sb, sc);

	// Create face with texture bound texture
	_flagWireFrame ? glBegin(GL_LINE_LOOP) : glBegin(GL_TRIANGLES);
	// vertex a
		glTexCoord2f(sa, ta);
		glNormal3fv(a); glVertex3fv(a);
	// vertex b
		glTexCoord2f(sb, tb);
		glNormal3fv(b);	glVertex3fv(b);
	// vertex c
		glTexCoord2f(sc, tc);
		glNormal3fv(c);	glVertex3fv(c);
	glEnd();
}

void TexturedSphere::FixSeam(float &a, float &b, float &c)
{
	// The problem is that some triangles will map to both ends of the map.
	// After all, the right edge of the map meets the left edge. The trig 
	// functions simply wrap the value around so you end up with a triangle
	// with two vertices on one edge of the map and one on the other edge. 
	// This causes all of the map between these points to be smashed into 
	// the image mapped onto the polygon. The easiest solution is to check
	// for the problem and use negative indexing. Since the texture is set
	// to repeat, it will smooth the seam.
	if (b < 0.75f && a > 0.75f)
		b += 1.0f;
	else if (b > 0.75f && a < 0.75f)
		b -= 1.0f;

	if (c < 0.75f && a > 0.75f)
		c += 1.0f;
	else if (c > 0.75f && a < 0.75f)
		c -= 1.0f;
}

void TexturedSphere::Update(const double& deltaTime)
{
	// Increment rotation around y-axis at _ROTV(=18) degrees per second
	if (_flagAnimation)
		rotation[1] += _ROTV*static_cast<float>(deltaTime);
}


void TexturedSphere::HandleKey(unsigned char key, int state, int mx, int my)
{
	// Ignore key-release
	if (!state) return;
	// Handle key
	switch (key)
	{
	// Press 'x' key to turn Animation on/off
	case 'x':
		ToggleAnimation();
		break;
	// Press 'z' key to toggle wire frame model
	case 'z':
		ToggleWireFrame();
		break;
	// Press '-' to decrement the number of subdivisions (min 1)
	case '-':
		if (_resolution > 1) --_resolution;
		break;
	// Press '+'(or '=') to increment the number of subdivisions (max 7)
	case '+':
    case '=':
		if (_resolution < _MAX_RES) ++_resolution;
		break;
	}
}

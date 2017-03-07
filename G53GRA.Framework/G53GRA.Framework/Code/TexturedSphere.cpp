#include "TexturedSphere.h"


TexturedSphere::TexturedSphere(const std::string& filename)
	: _resolution(4), _flagWireFrame(false), _flagAnimation(true)
{
	_texID = Scene::GetTexture(filename);

	static float vertices[] = 
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,		
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f
	 };

	_INIT_V = vertices;
}

TexturedSphere::~TexturedSphere()
{

}

void TexturedSphere::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
	glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
	glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
	glScalef(scale[0], scale[1], scale[2]);

	_flagWireFrame ? glColor3f(1.0f, 1.0f, 1.0f) : glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	DrawSphere();

	glPopAttrib();
	glPopMatrix();
}

void TexturedSphere::DrawSphere()
{
	SubDivide(_resolution, &_INIT_V[_VERTEX3], &_INIT_V[_VERTEX0], &_INIT_V[_VERTEX4]);
	SubDivide(_resolution, &_INIT_V[_VERTEX0], &_INIT_V[_VERTEX1], &_INIT_V[_VERTEX4]);
	SubDivide(_resolution, &_INIT_V[_VERTEX1], &_INIT_V[_VERTEX2], &_INIT_V[_VERTEX4]);
	SubDivide(_resolution, &_INIT_V[_VERTEX2], &_INIT_V[_VERTEX3], &_INIT_V[_VERTEX4]);

	SubDivide(_resolution, &_INIT_V[_VERTEX0], &_INIT_V[_VERTEX3], &_INIT_V[_VERTEX5]);
	SubDivide(_resolution, &_INIT_V[_VERTEX1], &_INIT_V[_VERTEX0], &_INIT_V[_VERTEX5]);
	SubDivide(_resolution, &_INIT_V[_VERTEX2], &_INIT_V[_VERTEX1], &_INIT_V[_VERTEX5]);
	SubDivide(_resolution, &_INIT_V[_VERTEX3], &_INIT_V[_VERTEX2], &_INIT_V[_VERTEX5]);
}

void TexturedSphere::SubDivide(int recurse_idx, float *a, float *b, float *c)
{
	float ab[3] = { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
	float bc[3] = { b[0] + c[0], b[1] + c[1], b[2] + c[2] };
	float ca[3] = { c[0] + a[0], c[1] + a[1], c[2] + a[2] };

	norm(ab);
	norm(bc);
	norm(ca);
	
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
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _texID);

	glEnable(GL_COLOR_MATERIAL);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	float sa = 0.5f + atan2f(a[2], a[0]) / (2.0f*M_PI);
	float ta = 0.5f + asinf(a[1]) / M_PI;
	
	float sb = 0.5f + atan2f(b[2], b[0]) / (2.0f*M_PI);
	float tb = 0.5f + asinf(b[1]) / M_PI;

	float sc = 0.5f + atan2f(c[2], c[0]) / (2.0f*M_PI);
	float tc = 0.5f + asinf(c[1]) / M_PI;

	FixSeam(sa, sb, sc);

	_flagWireFrame ? glBegin(GL_LINE_LOOP) : glBegin(GL_TRIANGLES);

		glTexCoord2f(sa, ta);
		glNormal3fv(a); glVertex3fv(a);
		glTexCoord2f(sb, tb);
		glNormal3fv(b);	glVertex3fv(b);
		glTexCoord2f(sc, tc);
		glNormal3fv(c);	glVertex3fv(c);

	glEnd();
}

void TexturedSphere::FixSeam(float &a, float &b, float &c)
{
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
	if (_flagAnimation)
		rotation[1] += _ROTV*static_cast<float>(deltaTime);
}


void TexturedSphere::HandleKey(unsigned char key, int state, int mx, int my)
{
	if (!state) return;

	switch (key)
	{
	case 'x':
		ToggleAnimation();
		break;
	case 'z':
		ToggleWireFrame();
		break;
	case '-':
		_resolution = _resolution > 1 ? _resolution - 1 : 1;
		break;
	case '+':
		_resolution++;
	}
}
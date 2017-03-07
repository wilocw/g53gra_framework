#include "TexturedSphere.h"


TexturedSphere::TexturedSphere(const std::string& filename)
	: _resolution(8), _flagWireFrame(false), _flagAnimation(true)
{
	_texID = Scene::GetTexture(filename);

	float vertices[] = 
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f,		
		-1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f
	 };

	_INIT_V = vertices;
	printf("%3.2f %3.2f %3.2f\n", _INIT_V[0], _INIT_V[1], _INIT_V[2]);
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

	_flagWireFrame ? glColor3f(1.0f, 1.0f, 1.0f) : glColor4f(0.0f, 0.0f, 0.0f, 0.0f);

	DrawSphere();

	glPopAttrib();
	glPopMatrix();
}

void TexturedSphere::DrawSphere()
{
	/*
	ERROR IS HERE
	*/
	float* v = &_INIT_V[0];
	printf("%3.2f %3.2f %3.2f\n", v[0], v[1], v[2]);
	printf("%3.2f %3.2f %3.2f\n", *_INIT_V, *(_INIT_V+1), *(_INIT_V+2));


	DrawFace(_resolution, &_INIT_V[_VERTEX3], &_INIT_V[_VERTEX0], &_INIT_V[_VERTEX4]);
	DrawFace(_resolution, &_INIT_V[_VERTEX0], &_INIT_V[_VERTEX1], &_INIT_V[_VERTEX4]);
	DrawFace(_resolution, &_INIT_V[_VERTEX1], &_INIT_V[_VERTEX2], &_INIT_V[_VERTEX4]);
	DrawFace(_resolution, &_INIT_V[_VERTEX2], &_INIT_V[_VERTEX3], &_INIT_V[_VERTEX4]);

	DrawFace(_resolution, &_INIT_V[_VERTEX0], &_INIT_V[_VERTEX3], &_INIT_V[_VERTEX5]);
	DrawFace(_resolution, &_INIT_V[_VERTEX1], &_INIT_V[_VERTEX0], &_INIT_V[_VERTEX5]);
	DrawFace(_resolution, &_INIT_V[_VERTEX2], &_INIT_V[_VERTEX1], &_INIT_V[_VERTEX5]);
	DrawFace(_resolution, &_INIT_V[_VERTEX3], &_INIT_V[_VERTEX2], &_INIT_V[_VERTEX5]);
}

void TexturedSphere::DrawFace(int recurse_idx, float *a, float *b, float *c)
{
	if (recurse_idx > 1)
	{
		float ab[3] = { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
		float bc[3] = { b[0] + c[0], b[1] + c[1], b[2] + c[2] };
		float ca[3] = { c[0] + a[0], c[1] + a[1], c[2] + a[2] };

		norm(ab);
		norm(bc);
		norm(ca);

		DrawFace(recurse_idx - 1, a, ab, ca);
		DrawFace(recurse_idx - 1, ab, b, bc);
		DrawFace(recurse_idx - 1, ca, bc, c);
		DrawFace(recurse_idx - 1, ca, a, bc);
	}

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, _texID);

	glEnable(GL_COLOR_MATERIAL);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	_flagWireFrame ? glBegin(GL_LINE_LOOP) : glBegin(GL_TRIANGLES);
		glNormal3fv(a); glVertex3fv(a);
		glNormal3fv(b);	glVertex3fv(b);
		glNormal3fv(c);	glVertex3fv(c);
	glEnd();
}

void TexturedSphere::Update(const double& deltaTime)
{
	if (_flagAnimation)
		rotation[1] += _ROTV*static_cast<float>(deltaTime);
}



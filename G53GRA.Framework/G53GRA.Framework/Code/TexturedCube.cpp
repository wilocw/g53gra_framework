#include "TexturedCube.h"

using namespace std;

TexturedCube::TexturedCube(const string& filename)
{
	texID = Scene::GetTexture(filename);
}

void TexturedCube::Display()
{
	glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		
		glTranslatef(pos[0], pos[1], pos[2]);
		glScalef(scale[0], scale[1], scale[2]);
		glRotatef(rotation[1], 0.f, 1.f, 0.f);
		glRotatef(rotation[0], 1.f, 0.f, 0.f);
		glRotatef(rotation[2], 0.f, 0.f, 1.f);

		DrawCube();
		
		glPopAttrib();
	glPopMatrix();
}

void TexturedCube::DrawCube()
{
	// Enable Texturing
	glEnable(GL_TEXTURE_2D);

	// Enable setting the colour of the material the cube is made from
	// as well as the material for blending.
	glEnable(GL_COLOR_MATERIAL);

	// Tell openGL which texture buffer to use
	glBindTexture(GL_TEXTURE_2D, texID);

	glBegin(GL_QUADS);

		// draw the front face

		// set the colour of the front face
		glColor3f(1.0f, 0.0f, 0.0f);

		// set the normal of the front face
		glNormal3f(0.0f, 0.0f, 1.0f);

		// define texture coordinates for the 4 vertices
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		// draw the back face

		// set the colour of the front face
		glColor3f(0.0f, 1.0f, 0.0f);

		// set the normal of the front face
		glNormal3f(0.0f, 0.0f, -1.0f);

		// define texture coordinates for the 4 vertices
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		// draw the left face

		// set the colour of the front face
		glColor3f(0.0f, 0.0f, 1.0f);

		// set the normal of the front face
		glNormal3f(-1.0f, 0.0f, 0.0f);

		// define texture coordinates for the 4 vertices
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		// draw the right face

		// set the colour of the front face
		glColor3f(0.0f, 1.0f, 1.0f);

		// set the normal of the front face
		glNormal3f(1.0f, 0.0f, 0.0f);

		// define texture coordinates for the 4 vertices
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		// draw the top face

		// set the colour of the front face
		glColor3f(1.0f, 1.0f, 0.0f);

		// set the normal of the front face
		glNormal3f(0.0f, 1.0f, 0.0f);

		// define texture coordinates for the 4 vertices
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		// draw the bottom face

		// set the colour of the front face
		glColor3f(1.0f, 0.0f, 1.0f);

		// set the normal of the front face
		glNormal3f(0.0f, -1.0f, 0.0f);

		// define texture coordinates for the 4 vertices
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

	glEnd();

	// Stop blending textures and colours
	glDisable(GL_COLOR_MATERIAL);

	// Bind to the blank buffer to stop ourselves accidentaly
	// using the wrong texture in the next draw call
	glBindTexture(GL_TEXTURE_2D, 0);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);
}

void TexturedCube::Update(const double& deltaTime)
{
	rotation[0] += (float)deltaTime*20.f; // Rotate around x axis at 20degrees per second
	rotation[1] += (float)deltaTime*10.f; // Rotate around y axis at 10degrees per second
}
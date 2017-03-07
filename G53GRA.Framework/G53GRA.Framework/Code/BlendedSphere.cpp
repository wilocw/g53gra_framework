#include "BlendedSphere.h"


BlendedSphere::BlendedSphere(const std::string& mapfile, const std::string& cloudfile)
	: TexturedSphere()
{
	// Load texture using the provided Texture loader (.bmp only)
	_mapID = Scene::GetTexture(mapfile);
	_cloudID = Scene::GetTexture(cloudfile);
}

void BlendedSphere::Display()
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

	// Handle lighting effects
	glEnable(GL_COLOR_MATERIAL);
	glColor3ub(30, 59, 117);
	DrawSphere();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor3ub(255, 255, 255);

	// Enable texturing (2D image as texture)
	glEnable(GL_TEXTURE_2D);
	// Bind input texture to GL_TEXTURE_2D buffer
	glBindTexture(GL_TEXTURE_2D, _mapID);
	// Render sphere
	DrawSphere();

	glBindTexture(GL_TEXTURE_2D, _cloudID);
	DrawSphere();

	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Disable texturing
	glDisable(GL_TEXTURE_2D);

	// Pop matrix and attribute stack to revert transformation changes
	glPopAttrib();
	glPopMatrix();
}

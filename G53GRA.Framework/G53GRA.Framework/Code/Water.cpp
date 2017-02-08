#include "Water.h"
#include <cmath>

Water::Water(const int& gridX, const int& gridZ, const std::string& filename)
	: xGridDims(gridX), zGridDims(gridZ), frozen(false), time(0.0)
{
	texID = Scene::GetTexture(filename);

	// initialise the grids texture coordinate memory we will need enough memory for both the s and t coordinate at each mesh vertex
	texCoords = new float[(xGridDims + 1) * (zGridDims + 1) * 2];

	matAmbient[0] = 0.9f;   // set the material properties of the grid
	matAmbient[1] = 0.95f;
	matAmbient[2] = 0.9f;
	matAmbient[3] = 1.0f;

	matDiffuse[0] = 1.0f;
	matDiffuse[1] = 1.0f;
	matDiffuse[2] = 1.0f;
	matDiffuse[3] = 1.0f;

	matSpecular[0] = 1.0f;
	matSpecular[1] = 1.0f;
	matSpecular[2] = 1.0f;
	matSpecular[3] = 1.0f;

	matShininess = 128;
}


Water::~Water()
{
	if (texCoords != NULL)
	{
		delete [] texCoords;
		texCoords = NULL;
	}
}

void Water::Display()
{
	float x, y, z;
	glPushAttrib(GL_ALL_ATTRIB_BITS);              // Set the material properties of the waters surface
		glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
		glMateriali(GL_FRONT, GL_SHININESS, matShininess);

		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, texID);    // Tell OpenGL which texture buffer to apply as texture
		glColor4f(1.0f, 1.0f, 1.0f, 0.8f);          // Set the base colour of the quad

		glPushMatrix();
			glTranslatef(pos[0], pos[1], pos[2]);   // position the water
			glScalef(scale[0], scale[1], scale[2]); // scale the unit water

			y = 0.0f; z = -0.5f; // initialise the start position as the top left coorner of the unit water mesh
			glBegin(GL_QUADS);                                      // draw the unit water surface as quads
			for (int j = 0; j < zGridDims; j++)
			{
				x = -0.5f;
				for (int i = 0; i < xGridDims; i++)
				{
					glNormal3f(0.0f, 1.0f, 0.0f);  // specify the quads normal

					// specify the first texture coordinate and position relative to the start postion x,y,z
					glTexCoord2fv(&texCoords[(i + j*(xGridDims + 1)) * 2]);
					glVertex3f(x, y, z);

					// specify the second texture coordinate and position relative to the start postion x,y,z
					glTexCoord2fv(&texCoords[(i + (j + 1)*(xGridDims + 1)) * 2]);
					glVertex3f(x, y, z + 1.0f / (float)zGridDims);

					// specify the third texture coordinate and position relative to the start postion x,y,z
					glTexCoord2fv(&texCoords[(i + 1 + (j + 1)*(xGridDims + 1)) * 2]);
					glVertex3f(x + 1.0f / (float)xGridDims, y, z + 1.0f / (float)zGridDims);

					// specify the fourth texture coordinate and position relative to the start postion x,y,z 
					glTexCoord2fv(&texCoords[((i + 1) + j*(xGridDims + 1)) * 2]);
					glVertex3f(x + 1.0f / (float)xGridDims, y, z);

					x += 1.0f / (float)xGridDims; // move the position of the quad on by one xgriddim step in the x axis
				}
				z += 1.0f / (float)zGridDims; // move the position of the quad on by one zgriddim step in the z axis
			}
			glEnd();
			
		glPopMatrix();

	glPopAttrib();

	glBindTexture(GL_TEXTURE_2D, NULL); // Bind to the blank (null) buffer to stop accidentaly using the wrong texture in the next draw call

	glDisable(GL_TEXTURE_2D); // stop using texture coordinates
}

void Water::Update(const double& deltaTime)
{
	float radius;
	time += deltaTime; // overall run time


	// use dimensions of the grid to find a sensible radius to rotate about
	radius = sqrtf((1.0f / xGridDims)*(1.0f / xGridDims) + (1.0f / zGridDims)*(1.0f / zGridDims));
	radius /= 4.0f; // make sure this radius does not intersect any of the other texture locations

	// for each of the grid points calculate the texture coordinate
	if (frozen)
	{
		for (int j = 0; j <= zGridDims; j++)
		{
			for (int i = 0; i <= xGridDims; i++)
			{
				// if the water is frozen then calculate texCoord based on the sample position
				// i+(xGridDims+1) * j gives the texture position of the ith sample on the jth row
				texCoords[(i + (xGridDims + 1) * j) * 2 + 0] = (float)i / (float)xGridDims;
				texCoords[(i + (xGridDims + 1) * j) * 2 + 1] = (float)j / (float)zGridDims;
			}
		}
	}
	else
	{
		for (int j = 0; j <= zGridDims; j++)
		{
			for (int i = 0; i <= xGridDims; i++)
			{
				// if the water is not frozen then calculate texCoord based on the sample position + some amount offset by a spherical function
				texCoords[(i + (xGridDims + 1) * j) * 2 + 0] = (float)sin(time + (double)j) * radius + (float)i / (float)xGridDims;
				texCoords[(i + (xGridDims + 1) * j) * 2 + 1] = (float)cos(time + (double)i) * radius + (float)j / (float)zGridDims;
			}
		}
	}
}

void Water::HandleKey(unsigned char key, int state, int x, int y)
{
	if (key == 'm' && state)
		frozen = !frozen;		 // if the m key is pressed freeze / unfreeze the water
}
#include "Link.h"


Link::Link(const float& width, const float& height, const std::string& filename)
	: width(width), height(height), time(0.0), runAnimate(true), dx(4.0f)
{
	texID = Scene::GetTexture(filename);

	spriteFrame = 0;
	spriteWidth = 16;
}


Link::~Link()
{
}

void Link::Display()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);

	glPushMatrix();
		glTranslatef(pos[0], pos[1], pos[2]);
		glScalef(scale[0], scale[1], scale[2]);
		glBegin(GL_QUADS);
			glColor3f(1.0f, 1.0f, 1.0f);
			glNormal3f(0.0f, 0.0f, 0.0f);

			glTexCoord2d(texCoords[0], texCoords[1]); // Texture coordinate index into the top left sprite coord
			glVertex3f(-width / 2.0f, height, 0.0f);    // Vertex coordinate of the top left of the quad

			glTexCoord2d(texCoords[2], texCoords[3]); // Texture coordinate index into the bottom left sprite coord
			glVertex3f(-width / 2.0f, 0.0f, 0.0f);       // Vertex coordinate of the bottom left of the quad
		
			glTexCoord2d(texCoords[4], texCoords[5]); // Texture coordinate index into the bottom right sprite coord
			glVertex3f(width / 2.0f, 0.0f, 0.0f);        // Vertex coordinate of the bottom right of the quad
						
			glTexCoord2d(texCoords[6], texCoords[7]); // Texture coordinate index into the top right sprite coord
			glVertex3f(width / 2.0f, height, 0.0f);     // Vertex coordinate of the top right of the quad
		glEnd();
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, NULL); // Bind to the blank (null) buffer to stop ourselves accidentaly using the wrong texture in the next draw call

	glDisable(GL_TEXTURE_2D);
}

void Link::Update(const double& deltaTime)
{
	float sCoord;
	time += deltaTime;

	if (runAnimate)
	{
		pos[0] += (1.0f + scale[0])*dx*static_cast<float>(deltaTime);
		if (pos[0] > scale[0]*20.0f || pos[0] < -scale[0]*20.0f)
			dx = -dx;

		if (time > 0.1)
		{
			spriteFrame = spriteFrame > 6 ? 0 : spriteFrame + 1; // shift frame up by 1 (wrap at 7)
			time = 0.0; // reset frame counter
		}
	}

	if (dx > 0.0f) // if he is running right, from spriteFrame to spriteFrame+1
		sCoord = (float)spriteFrame / (float)spriteWidth;
	else // if he is running left FLIP the coords to avoid needing more sprite sheets
		sCoord = (float)(spriteFrame + 1) / (float)spriteWidth;
	
	texCoords[0] = sCoord; // (s,t) texture coord at [0, 1]
	texCoords[1] = 1.0f;

	texCoords[2] = sCoord; // (s,t) texture coord at [0, 0]
	texCoords[3] = 0.0f;

	if (dx > 0.0) // if he is running right, from spriteFrame to spriteFrame+1
		sCoord = (float)(spriteFrame + 1) / (float)spriteWidth;
	else // if he is running left FLIP the coords to avoid needing more sprite sheets
		sCoord = (float)spriteFrame / (float)spriteWidth;

	texCoords[4] = sCoord; // (s,t) texture coord at [1, 0]
	texCoords[5] = 0.0f;

	texCoords[6] = sCoord; // (s,t) texture coord at [1, 1]
	texCoords[7] = 1.0f;

}

void Link::HandleKey(unsigned char key, int state, int x, int y)
{
	if (key == 'x' && state) // 'r' key pressed: pause/unpause animation
	{
		runAnimate = !runAnimate;
		if (!runAnimate) spriteFrame = 0;
	}
}

void Link::HandleMouse(int button, int state, int x, int y)
{
	if (button == GLUT_RIGHT_BUTTON || button == GLUT_MIDDLE_BUTTON) // right or middle button press
	{
		if (state) // release: unpause animation
		{
			runAnimate  = true;
			spriteFrame = 0;
		}
		else // click: special sprite (pause animation while holding mouse button)
		{
			spriteFrame = 8;
			runAnimate  = false;
		}
	}

}
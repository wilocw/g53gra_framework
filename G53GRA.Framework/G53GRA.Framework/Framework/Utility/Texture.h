#pragma once

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <map>
#include <string>
#include <gl/GLUT.h>

/**
 * Class for loading bitmap files into texture buffer and handling texture IDs
 */
class Texture
{
public:
	Texture(void){};
	~Texture(void);

	/** Loads a texture into memory and returns the id of the texture object created */
	int GetTexture(std::string fileName);

private:
	std::map<int, std::string> textures;
	
	int CheckGLError()
	{
		int e = 0;
		GLenum error = glGetError();
		while (GL_NO_ERROR != error)
		{
			++e;
			printf("GL Error %i: %s\n", e, gluErrorString(error));
			error = glGetError();
		}

		return e;
	}

};
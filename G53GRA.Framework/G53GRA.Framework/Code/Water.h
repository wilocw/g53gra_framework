#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"

#include <string>

class Water :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Water(const int& gridX, const int& gridZ, const std::string& filename);
	~Water();

	void Display();
	void Update(const double& delteTime);
	void HandleKey(unsigned char key, int state, int x, int y);

private:
	int texID;

	int xGridDims, zGridDims;
	float* texCoords;
	double time;
	bool frozen;

	float matAmbient[4];      // matrial properties of the grid
	float matDiffuse[4];
	int   matShininess;
	float matSpecular[4];
};


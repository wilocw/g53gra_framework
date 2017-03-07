#pragma once
#include "TexturedSphere.h"
class BlendedSphere :
	public TexturedSphere
{
public:
	BlendedSphere(const std::string& mapfile, const std::string& cloudfile);
	~BlendedSphere() {}

	void Display();

private:
	// ID to bound texture
	int _mapID, _cloudID;
};


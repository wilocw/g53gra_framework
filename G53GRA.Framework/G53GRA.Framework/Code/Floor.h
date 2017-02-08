#pragma once
#include "DisplayableObject.h"

class Floor :
	public DisplayableObject
{
public:
	Floor();
	~Floor();

	void Display();

private:
	int texId;
};


#pragma once

#include "../Framework/Engine/Scene.h"

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};
	void HandleKey(unsigned char key, int state, int x, int y);

private:
	void Initialise();
	void Projection();

};
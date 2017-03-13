#include "MyScene.h"

#include "TexturedCube.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
#ifdef __APPLE__
	TexturedCube* tc = new TexturedCube("./batmanlogo.bmp");
#else
	TexturedCube* tc = new TexturedCube("./Textures/batmanlogo.bmp");
#endif
	tc->size(100.0f);
	AddObjectToScene(tc);

}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}

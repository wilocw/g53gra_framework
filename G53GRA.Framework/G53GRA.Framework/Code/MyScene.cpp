#include "MyScene.h"

#include "Demos\Triforce\Triforce.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	
	Triforce *t = new Triforce();
	AddObjectToScene(t);

}

void MyScene::Projection()
{
	gluPerspective(60.0, (GLdouble)windowWidth / (GLdouble)windowHeight, 1.0, 1000.0);
}
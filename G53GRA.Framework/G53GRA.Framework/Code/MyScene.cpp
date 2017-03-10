#include "MyScene.h"
#include "FaceCull.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	FaceCull *f = new FaceCull();
	f->size(20.0f);
	f->position(0.0f, 0.0f, -500.0f);
	AddObjectToScene(f);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 10000.0);
}

#include "MyScene.h"

#include "Floor.h"
#include "Teapot.h"
#include "MultiLight.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Floor *f = new Floor();
	f->size(100.0f);

	Teapot *t = new Teapot();
	t->size(100.0f);

	MultiLight *l = new MultiLight();

	AddObjectToScene(f);
	AddObjectToScene(t);
	// Press 'p' to toggle positional (default) / directional light
	AddObjectToScene(l);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}

#include "MyScene.h"

#include "Triangle.h"
#include "Floor.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight){}

void MyScene::Initialise()
{
	// set the background colour of the scene to black
	glClearColor(static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(1.0f));

	// DEMO 5
	// Show floor and triangle
	Floor *f = new Floor();
	Triangle *t = new Triangle();
	f->size(100.0f);
	t->size(0.5f);
	AddObjectToScene(f);
	AddObjectToScene(t);
}

/// set the perspective of camera
void MyScene::Projection()
{
	gluPerspective(static_cast<GLdouble>(60.0), static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight),
				   static_cast<GLdouble>(1.0), static_cast<GLdouble>(1000.0));
}

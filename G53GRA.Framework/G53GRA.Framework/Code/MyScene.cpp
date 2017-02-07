#include "MyScene.h"

#include "Triforce.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight){}

void MyScene::Initialise()
{
	// set the background colour of the scene to black
	glClearColor(static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(1.0f));

	// Create a new triforce object and add it to the list of objects
	Triforce *t = new Triforce();
	AddObjectToScene(t);
}

/// set the perspective of camera
void MyScene::Projection()
{
	gluPerspective(static_cast<GLdouble>(60.0), static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight),
				   static_cast<GLdouble>(1.0), static_cast<GLdouble>(1000.0));
}

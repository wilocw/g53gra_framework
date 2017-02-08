#include "MyScene.h"

#include "Lamp.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
	// Create and add a new lamp to the scene
	Lamp *l = new Lamp();
	l->size(6.0f);
	AddObjectToScene(l);
}

void MyScene::Initialise()
{
	glClearColor(static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(1.0f));

}

void MyScene::Projection()
{
	gluPerspective(static_cast<GLdouble>(60.0), static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight), 
				   static_cast<GLdouble>(1.0), static_cast<GLdouble>(1000.0));
}

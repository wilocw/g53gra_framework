#include "MyScene.h"

#include "Wall.h"
#include "Light.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Wall

	Wall *w = new Wall();
	w->position(0.0f, 0.0f, -100.0f);
	w->size(800.0f, 600.0f, 1.0f);

	AddObjectToScene(w);

	// Light A (red)

	static GLfloat ambient_A[] = {0.5f, 0.0f, 0.0f, 1.0f};
	static GLfloat diffuse_A[] = { 0.9f, 0.0f, 0.0f, 1.0f };
	static GLfloat specular_A[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static GLfloat position_A[] = { -100.0f, 0.0f, 0.0f, 1.0f };

	Light *l_A = new Light(GL_LIGHT0, ambient_A, diffuse_A, specular_A, position_A);
	
	// Light B (blue)

	static GLfloat ambient_B[] = { 0.0f, 0.0f, 0.5f, 1.0f };
	static GLfloat diffuse_B[] = { 0.0f, 0.0f, 0.9f, 1.0f };
	static GLfloat specular_B[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static GLfloat position_B[] = { 100.0f, 0.0f, 0.0f, 1.0f };

	Light *l_B = new Light(GL_LIGHT1, ambient_B, diffuse_B, specular_B, position_B);

	AddObjectToScene(l_A);
	AddObjectToScene(l_B);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}

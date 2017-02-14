#include "MyScene.h"

#include "Hands.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Hands *rh = new Hands();
	Hands *lh = new Hands();
	
	rh->size(25.f);
	rh->position(100.0f, -50.0f, -10.f);
	rh->orientation(0.0f, -30.0f, 0.0f);
	rh->SetAnimationControl('u');

	lh->size(25.f);
	lh->position(-100.f, -50.0f, -10.f);
	lh->orientation(0.0f, 30.0f, 0.0f);
	lh->ToggleAnimation();
	lh->ToggleWireFrame();
	lh->ToggleHandedness();
	lh->SetAnimationControl('y');
	
	AddObjectToScene(rh);
	AddObjectToScene(lh);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}

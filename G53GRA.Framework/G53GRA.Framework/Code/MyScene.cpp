#include "MyScene.h"

#include "Hands.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{
	
}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Initialise new Hands objects
	Hands *rh = new Hands(); // right hand
	Hands *lh = new Hands(); // left hand
	
	// Set properties for right hand
	rh->size(25.f);
	rh->position(100.0f, -50.0f, -10.f);
	rh->orientation(0.0f, -30.0f, 0.0f);
	// Press 'u' key to start/stop animation
	rh->SetAnimationControl('u');

	// Set properties for left hand
	lh->size(25.f);
	lh->position(-100.f, -50.0f, -10.f);
	lh->orientation(0.0f, 30.0f, 0.0f);

	// Flip handedness for right (default) to left
	lh->ToggleHandedness();
	// Turn on animation by default
	lh->ToggleAnimation();
	// Show wireframe and skeleton (instead of solid shapes)
	lh->ToggleWireFrame();
	// Press 'y' key to stop/start animation
	lh->SetAnimationControl('y');
	
	// Add both hands to the Scene
	AddObjectToScene(rh);
	AddObjectToScene(lh);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}

#include "MyScene.h"
#include "Link.h"
#include "SunLight.h"
#include "Water.h"
#include "TexturedCube.h"
#include "Floor.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(0.0f), static_cast<GLclampf>(1.0f));
	// DEMO 10 (Animated Texturing)
#ifdef __APPLE__
	Link *link = new Link(10.0f, 25.0f, "./linkSpriteSheet.bmp");
#else
	Link *link = new Link(10.0f, 25.0f, "./Textures/linkSpriteSheet.bmp");
#endif
	link->position(0.0f, -99.9f, -100.0f);
	link->size(10.0f);

#ifdef __APPLE__
	Water *water = new Water(20, 20, "./water.bmp");
#else
	Water *water = new Water(20, 20, "./Textures/water.bmp");
#endif

	water->position(0.0f, -99.9f, 100.0f);
	water->size(400.0f);

	Floor *floor = new Floor();
	floor->size(100);

	SunLight *sl = new SunLight();
	sl->direction(-1.0f, 1.0f, 1.0f);

	AddObjectToScene(floor);
	AddObjectToScene(water);
	AddObjectToScene(link);
	AddObjectToScene(sl);
}

void MyScene::Projection()
{
	gluPerspective(static_cast<GLdouble>(60.0), static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight), static_cast<GLdouble>(1.0), static_cast<GLdouble>(1000.0));
}

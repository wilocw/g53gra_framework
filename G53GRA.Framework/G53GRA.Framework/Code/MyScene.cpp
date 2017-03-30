#include "MyScene.h"

#include "Car.h"

#include "Skybox.h"

#include "Sun.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	Car *car = new Car();
	car->size(100.0f);
	car->position(0.0f, -900.0f, 0.0f);
	AddObjectToScene(car);

	GLuint tf = Scene::GetTexture("./Textures/skybox_up.bmp");
	GLuint bf = Scene::GetTexture("./Textures/skybox_down.bmp");
	GLuint lf = Scene::GetTexture("./Textures/skybox_left.bmp");
	GLuint rf = Scene::GetTexture("./Textures/skybox_right.bmp");
	GLuint nf = Scene::GetTexture("./Textures/skybox_back.bmp");
	GLuint ff = Scene::GetTexture("./Textures/skybox_front.bmp");

	Skybox *skybox = new Skybox(tf, bf, lf, rf, nf, ff);
	skybox->size(10000.0f, 1000.0f, 10000.0f);
	AddObjectToScene(skybox);

	Sun *sun = new Sun();
	sun->position(1000.0f, 1000.0f, -1000.0f);

	AddObjectToScene(sun);
}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 30000.0);
}

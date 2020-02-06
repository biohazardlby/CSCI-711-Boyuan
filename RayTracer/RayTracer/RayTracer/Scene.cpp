#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

bool Scene::Add_Object(Object &obj)
{
	objects.push_back(&obj);
	return true;
}

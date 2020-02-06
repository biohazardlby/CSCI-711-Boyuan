#pragma once
#include "Utility.h"
#include <vector>
#include "Object.h"
class Scene
{
public:
	std::vector<Object*> objects;
	Camera *current_cam;
	Scene();
	~Scene();
	bool Add_Object(Object &obj);
};


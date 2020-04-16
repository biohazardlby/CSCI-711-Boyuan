#pragma once
#include "Utility.h"
#include <vector>
#include "Object.h"

class Camera {
public:
	vertex position;
	vertex lookAt;
	vertex up;

	float screen_height;
	float screen_width;
	float rayTrace_plane_dist;
	float viewAngle;

	float filmPlane_height;
	float filmPlane_width;

	void Camera_Trans_Matrix(glm::mat4& translate_matrix, glm::mat4& rotation_matrix);
	Camera(vertex position, vertex lookAt, vertex up, float width, float height, float rayTrace_plane_dist, float angleView);

};

class Light
{
public:
	vertex position;
	Color color;
	Color ambientColor;
	Light(vertex position, Color color, Color ambientColor);
};

class Scene
{
public:
	std::vector<Object*> objects ;
	std::vector<Light*> lights ;
	Camera *current_cam = nullptr;
	Scene();
	~Scene();	
	bool Add_Object(Object &obj);
	bool Add_Light(Light& light);
};
	
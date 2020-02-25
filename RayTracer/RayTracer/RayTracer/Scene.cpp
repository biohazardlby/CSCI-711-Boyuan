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

bool Scene::Add_Light(Light& light)
{
	lights.push_back(&light);
	return true;
}

void Camera::Camera_Trans_Matrix(glm::mat4& translate_matrix, glm::mat4& rotation_matrix)
{
	vector D = normalize(position - lookAt);
	vector upVec = up - position;
	vector R = normalize(cross(upVec, D));
	vector U = cross(D, R);
	vector P = { position.x,position.y,position.z };
	rotation_matrix = {
		R.x,U.x,D.x,0,
		R.y,U.y,D.y,0,
		R.z,U.z,D.z,0,
		0,0,0,1
	};
	translate_matrix = {
		1,0,0,-0,
		0,1,0,0,
		0,0,1,0,
		-P.x,-P.y,-P.z,1
	};
}

Camera::Camera(vertex position, vertex lookAt, vertex up, float width, float height, float rayTrace_plane_dist, float viewAngle)
{
	this->position = position;
	this->lookAt = lookAt;
	this->up = up;
	this->screen_height = height;
	this->screen_width = width;
	this->rayTrace_plane_dist = rayTrace_plane_dist;
	this->viewAngle = viewAngle;
	if (width >= height) {
		filmPlane_height = 2 * tan(deg_2_rad(viewAngle / 2)) * rayTrace_plane_dist;
		filmPlane_width = filmPlane_height * (screen_width / screen_height);
	}
	else {
		filmPlane_width = 2 * tan(deg_2_rad(viewAngle / 2)) * rayTrace_plane_dist;
		filmPlane_height = filmPlane_width * (screen_height / screen_width);
	}
}

Light::Light(vertex position, Color color, Color ambientColor) 
{
	this->position = position;
	this->color = color;
	this->ambientColor = ambientColor;
}
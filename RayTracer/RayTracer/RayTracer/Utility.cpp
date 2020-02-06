#include "Utility.h"

void Print_Vertex(vertex v) {
	using namespace std;
	string output = "";
	output += "x:" + to_string(v.x) + "\t" + "y:" + to_string(v.y) + "\t" + "z:" + to_string(v.z);
	cout << output << endl;
}
void Print_Matrix(glm::mat4 mat) {
	using namespace std;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
}

float rad_2_deg(float rad)
{
	return rad * 180 / PI;
}
float deg_2_rad(float degree)
{
	return degree * PI / 180;
}

vector normalize(vector v)
{
	glm::vec3 vec = { v.x,v.y,v.z };
	vec = glm::normalize(vec);
	return { vec.x,vec.y,vec.z };
}

float vector_angle(vector v1, vector v2)
{
	return glm::angle(glm::vec3{ v1.x,v1.y,v1.z }, glm::vec3{ v2.x,v2.y,v2.z });
}

float dot(vector v1, vector v2)
{
	return glm::dot(glm::vec3{ v1.x,v1.y,v1.z }, glm::vec3{ v2.x,v2.y,v2.z });
}

vector cross(vector v1, vector v2)
{
	glm::vec3 result = glm::cross(glm::vec3{ v1.x,v1.y,v1.z }, glm::vec3{ v2.x,v2.y,v2.z });
	return { result.x,result.y,result.z };
}

float length(vector v)
{
	return glm::length(glm::vec3{ v.x,v.y,v.z });
}

vector operator*(glm::mat4 mat, vector v) {
	glm::vec4 vec = { v.x,v.y,v.z,1 };
	vec = mat * vec;
	return { vec.x, vec.y, vec.z };
}
vector operator*(vector v, glm::mat4 mat) {
	glm::vec4 vec = { v.x,v.y,v.z,1 };
	vec = vec * mat;
	return { vec.x, vec.y, vec.z };
}
vector operator*(float f, vector v)
{
	return v * f;
}
vector operator-(vertex v1, vertex v2)
{
	return { v1.x - v2.x,v1.y - v2.y,v1.z - v2.z };
}
vertex operator*(glm::mat4 mat, vertex v) {
	glm::vec4 vec = { v.x,v.y,v.z,1 };
	vec = mat * vec;
	return { vec.x, vec.y, vec.z };
}
vertex operator*(vertex v, glm::mat4 mat) {
	glm::vec4 vec = { v.x,v.y,v.z,1 };
	vec = vec * mat;
	return { vec.x, vec.y, vec.z };
}

void Camera::Camera_Trans_Matrix(glm::mat4 & translate_matrix, glm::mat4 & rotation_matrix)
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
		filmPlane_height = 2 * tan(deg_2_rad(viewAngle / 2))*rayTrace_plane_dist;
		filmPlane_width = filmPlane_height * (screen_width / screen_height);
	}
	else {
		filmPlane_width = 2 * tan(deg_2_rad(viewAngle / 2))*rayTrace_plane_dist;
		filmPlane_height = filmPlane_width * (screen_height / screen_width);
	}
}

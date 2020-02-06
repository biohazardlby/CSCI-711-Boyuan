#pragma once

#include <glm\glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <iostream>
#include <string>
#include <math.h>

#define PI 3.14159265359
#define kEpsilon 0.000001

struct vector {
	float x;
	float y;
	float z;

	vector operator*(glm::mat4x4 mat) {
		glm::vec4 init = { x,y,z,1 };
		glm::vec4 res = mat * init;
		return { res.x,res.y,res.z };
	}
	vector operator*(float f) {
		return { x*f,y*f,z*f };
	}
	vector operator/(float f) {
		return { x / f,y / f,z / f };
	}
};

struct vertex {
	float x;
	float y;
	float z;

	void set(float set_x, float set_y, float set_z) {
		x = set_x;
		y = set_y;
		z = set_z;
	}
	vertex operator+(vector vec) {
		return { x + vec.x, y + vec.y, z + vec.z };
	}
	vertex operator-(vector vec) {

		return { x - vec.x ,y - vec.y ,z - vec.z };
	}
	vertex operator*(glm::mat4x4 mat) {
		glm::vec4 init = { x,y,z,1 };
		glm::vec4 res = mat * init;
		return { res.x,res.y,res.z };
	}
};

vector operator*(glm::mat4 mat, vector v);
vector operator*(vector v, glm::mat4 mat);
vector operator*(float f, vector v);
vector operator-(vertex v1, vertex v2);

vertex operator*(glm::mat4 mat, vertex v);
vertex operator*(vertex v, glm::mat4 mat);

struct Color {
	float r;
	float g;
	float b;
};

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

	void Camera_Trans_Matrix(glm::mat4& translate_matrix, glm::mat4 &rotation_matrix);
	Camera(vertex position, vertex lookAt, vertex up, float width, float height, float rayTrace_plane_dist, float angleView);

};

void Print_Vertex(vertex v);
void Print_Matrix(glm::mat4 mat);
float rad_2_deg(float rad);
float deg_2_rad(float degree);
vector normalize(vector v);
float vector_angle(vector v1, vector v2);
float dot(vector v1, vector v2);
vector cross(vector v1, vector v2);
float length(vector v);
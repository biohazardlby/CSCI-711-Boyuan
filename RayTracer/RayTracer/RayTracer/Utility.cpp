#include "Utility.h"

Color operator*(Color c, float f)
{
	return Color{c.r*f, c.g*f, c.b*f};
}

Color operator*(float f, Color c)
{
	return c * f;
}

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

Ray::Ray(vertex origin, vector direction, float length)
{
	this->origin = origin;
	this->direction = direction;
	this->length = length;
}
Ray::Ray(vertex origin, vector direction)
{
	this->origin = origin;
	this->direction = direction;
}
Ray::~Ray()
{
}


Color phongShading(vertex lightPos, vector normal, vertex fragPos, vertex viewPos, Color lightColor, Color ambientColor, Color diffuseColor, float shininess)
{
	vector lightDir = normalize(lightPos - fragPos);
	vector viewDir = normalize(viewPos - fragPos);
	vector halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(fmax(dot(normal, halfwayDir), 0.0), shininess);
	Color specular = lightColor * spec;

	float lambertian = fmax(dot(lightDir, normal), 0.0);
	Color diffuse = lambertian * diffuseColor;

	return (specular + diffuse + ambientColor);
}

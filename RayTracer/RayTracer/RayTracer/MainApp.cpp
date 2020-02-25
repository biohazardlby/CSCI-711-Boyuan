#include "MainApp.h"

void testRender() {
	float curTime = glfwGetTime();
	double time_sec;
	float time_frac = modf(curTime, &time_sec);
	for (int x = 100; x < 540; x++) {
		for (int y = 0; y < 100; y++) {
			Draw_Point(x, y, { time_frac,0,0 });
		}
		for (int y = 100; y < 200; y++) {
			Draw_Point(x, y, { 0,time_frac,0 });
		}
	}
}

void RayTrace() {
	int obj_size = scene->objects.size();
	Camera *cam = scene->current_cam;

	float scene_screen_ratio = cam->filmPlane_width / SCREEN_WIDTH;

	//std::cout << "SCREEN_WIDTH = \t" << SCREEN_WIDTH << std::endl;
	//std::cout << "SCREEN_HEIGHT = \t" << SCREEN_HEIGHT << std::endl;
	//std::cout << "scene_screen_ratio = \t" << scene_screen_ratio << std::endl;
	//std::cout << "filmplane_width = \t" << cam->filmPlane_width << std::endl;
	//std::cout << "filmplane_height = \t" << cam->filmPlane_height << std::endl;
	//std::cout << "focal length = \t" << cam->focalLength << std::endl;

	for (int sx = 0; sx < SCREEN_WIDTH; sx++) {
		for (int sy = 0; sy < SCREEN_HEIGHT; sy++) {
			vertex rayOrigin = { 0,0,0 };
			vertex rayEnd = {
				-cam->filmPlane_width / 2 + sx * scene_screen_ratio,
				-cam->filmPlane_height / 2 + sy * scene_screen_ratio,
				-scene->current_cam->rayTrace_plane_dist
			};

			glm::mat4 cam_translate_matrix(1);
			glm::mat4 cam_rotation_matrix(1);

			scene->current_cam->Camera_Trans_Matrix(cam_translate_matrix, cam_rotation_matrix);

			rayOrigin = glm::inverse(cam_translate_matrix) * rayOrigin;
			rayEnd = glm::inverse(cam_rotation_matrix) * rayEnd;
 			vector rayDir = rayEnd - rayOrigin;
			rayDir = normalize(rayDir);

			vertex* hit_pt = new vertex{ 0,0,0 };
			Ray *ray = new Ray(rayOrigin, rayDir);

			Object* rend_obj;
			float rend_obj_dist = FLT_MAX;
			for (int i = 0; i < obj_size; i++) {
				Object* cur_obj = scene->objects.at(i);
				float hit_distance;
				vector normal;
				if (cur_obj->RayTrace(*ray, *hit_pt, hit_distance,normal)) {
					if (hit_distance <= rend_obj_dist) {
						Light light = *scene->lights.at(0);

						Color drawColor = phongShading(
							light.position, normal, *hit_pt, scene->current_cam->position,
							light.color, light.ambientColor, cur_obj->color, 16);
						rend_obj = cur_obj;
						rend_obj_dist = hit_distance;
						Draw_Point(sx, sy, drawColor);
					}
				}
			}
		}
	}
}

void render_loop()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(1);
	
	//testRender();
	RayTrace();
}


/* program entry */

void Create_Window() {
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(SCREEN_WIDTH,SCREEN_HEIGHT , "Ray Tracer Yes", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
}
void Setup_Viewport() {
	// set up view
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT, 0.0, 1.0); // this creates a canvas you can do 2D drawing on

}
void Scene_Construct() {
	scene = new Scene();
	Sphere *sphere1 = new Sphere({ -1.23,	1.443,	-0.115 }, 0.85);
	sphere1->color = { 0.5,0,0 };
	scene->Add_Object(*sphere1);

	Sphere *sphere2 = new Sphere({ -0.129,	0.957,	-0.997 }, 0.65);
	sphere2->color = { 0,0.5,0 };
	scene->Add_Object(*sphere2);

	Triangle *triangle1 = new Triangle(
		{ -2.5,0,5 },
		{ 2.5,0,5 },
		{ -2.5,0,-5 }
		);
	triangle1->color = { 0,0,1 };
	scene->Add_Object(*triangle1);

	Triangle *triangle2 = new Triangle(
		{ 2.5,0,5 },
		{ 2.5,0,-5 },
		{ -2.5,0,-5 }
	);
	triangle2->color = { 0,0,1 };
	scene->Add_Object(*triangle2);

	Light* lightSource_1 = new Light({ -2,5,1 }, { .2,.2,.2 }, { .2,0,0 });
	scene->Add_Light(*lightSource_1);

	scene->current_cam = new Camera(
		{ -1.103, 1.312, 4 },		//position
		{ -1.256, 1.026, -3.945 },	//LookAt
		{ -1.103, 2.325, 4 },		//up
		SCREEN_WIDTH,				//width
		SCREEN_HEIGHT,				//height
		1000,							//rayTrace plane distance to camera
		60							//angle of view
	);
}


int main(int argc, char *argv[])
{

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}

	Create_Window();
	Setup_Viewport();

	Scene_Construct();

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Draw gears
		render_loop();

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Terminate GLFW
	glfwTerminate();

	// Exit program
	exit(EXIT_SUCCESS);
}


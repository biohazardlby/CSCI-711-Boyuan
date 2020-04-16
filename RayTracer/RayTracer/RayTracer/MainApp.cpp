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


			Ray *ray = new Ray(rayOrigin, rayDir);
			vertex* fragPoint = NULL;
			Object* rend_obj = NULL;
			float rend_obj_dist = FLT_MAX;
			vector fragPoint_normal;
			for (int cur_obj_idx = 0; cur_obj_idx < obj_size; cur_obj_idx++) {
				Object* cur_obj = scene->objects.at(cur_obj_idx);
				float hit_distance;
				vector hit_normal;
				vertex* hit_pt = new vertex{ 0,0,0 };
				//Check if view ray hit current obj
				if (cur_obj->RayTrace(*ray, *hit_pt, hit_distance, hit_normal)) {
					//Check if it is the first object hit
					if (hit_distance <= rend_obj_dist) {
						rend_obj = cur_obj;
						rend_obj_dist = hit_distance;
						fragPoint_normal = hit_normal;
						fragPoint = hit_pt;
					}
				}
			}
			//start shading
			if (rend_obj != NULL) {
				Light light = *scene->lights.at(0);
				//Check if light is blocked
				Ray* fragPoint_2_light = new Ray(*fragPoint, normalize(light.position - *fragPoint));
				bool blocked = false;
				for (int block_obj_idx = 0; block_obj_idx < obj_size; block_obj_idx++) {
					Object* block_obj = scene->objects.at(block_obj_idx);
					if (block_obj != rend_obj) {
						vertex block_hit_pt;
						float block_distance;
						vector block_normal;
						if (block_obj->RayTrace(*fragPoint_2_light, block_hit_pt, block_distance, block_normal)) {
							blocked = true;
						}
					}
				}
				Color drawColor;
				if (blocked) {
					drawColor = light.ambientColor;
				}
				else
				{
					drawColor = phongShading(
						light.position, fragPoint_normal, *fragPoint, scene->current_cam->position,
						light.color, light.ambientColor, rend_obj->color, 16);
				}
				Draw_Point(sx, sy, drawColor);
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
	Sphere *sphere1 = new Sphere({ -1.23,	1.546,	-0.115 }, 0.85);
	sphere1->color = { 0.5,0,0 };
	sphere1->ambientColor = { 0.2,0,0 };
	scene->Add_Object(*sphere1);

	Sphere *sphere2 = new Sphere({ 0.078,	0.957,	-0.881 }, 0.65);

	//Sphere *sphere2 = new Sphere({ -2,  2,   .5 }, 0.4);
	sphere2->color = { 0,0.5,0 };
	sphere2->ambientColor = { 0,.2,0 };
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

	Light* lightSource_1 = new Light({ -1.554,6.698,2.607 }, { .2,.2,.2 }, { .2,0,0 });
	scene->Add_Light(*lightSource_1);

	scene->current_cam = new Camera(
		{ -1.103, 1.312, 4 },		//position
		{ -1.256, 1.026, -3.945 },	//LookAt
		{ -1.103, 2.325, 4 },		//up
		SCREEN_WIDTH,				//width
		SCREEN_HEIGHT,				//height
		1000,						//rayTrace plane distance to camera
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


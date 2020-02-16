#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <iostream>

#include "Utility.h"
#include "PointDrawer.h"
#include "Scene.h"

GLFWwindow *window;
GLint SCREEN_WIDTH = 640;
GLint SCREEN_HEIGHT = 480;

Scene *scene;

#ifndef GLOBAL_H
#define GLOBAL_H


#include <string>
#include <vector>
#include <math.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "stb_image.h"

#include "graphics.hpp"
#include "input.hpp"
#include "cShader.hpp"

#include "cubeDemo.hpp"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int REFRESH_RATE;
extern float FRAME_TIME;

extern GLFWwindow* window;

#endif
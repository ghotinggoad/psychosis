#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "graphics.hpp"
#include "input.hpp"

#include "test.hpp"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int REFRESH_RATE;
extern float FRAME_TIME;

extern GLFWwindow* window;

#endif
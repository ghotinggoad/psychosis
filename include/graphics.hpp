#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

void initGraphics(int SCREEN_WIDTH,int SCREEN_HEIGHT);
static void error_callback(int error, const char* description);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void refreshWindow();

#endif
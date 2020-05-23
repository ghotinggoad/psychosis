#ifndef GRAPHICS_H
#define GRAPHICS_H

void initGraphics();
static void error_callback(int error, const char* description);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void refreshWindow();

#endif
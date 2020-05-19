#ifndef _INPUT_H_
#define _INPUT_H_

void initInput();
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);


#endif
#include "../include/global.hpp"

void initInput(){
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        printf("Closed!");
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    double xPosition, yPosition;
    glfwGetCursorPos(window, &xPosition, &yPosition);

    std::cout << xPosition << " " << yPosition << std::endl;
}
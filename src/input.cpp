#include "../include/global.hpp"


double xlast;
double ylast;

void initInput(){
    glfwSetKeyCallback(window, key_callback);
    glfwGetCursorPos(window, &xlast, &ylast);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
}

// Movement FORWARD = 0, BACKWARD = 1, LEFT = 2, RIGHT = 3, UP = 4, DOWN = 5
// Rotation YAW LEFT = 0, YAW RIGHT = 1, PITCH UP = 2, PITCH DOWN = 3

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        printf("EXIT\n");
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if(key == GLFW_KEY_W && action == GLFW_PRESS){
        printf("FORWARD\n");
        camera.setMovement(0, 1.0);
    }
    if(key == GLFW_KEY_W && action == GLFW_RELEASE){
        printf("FORWARD STOP\n");
        camera.setMovement(0, 0.0);
    }
    if(key == GLFW_KEY_S && action == GLFW_PRESS){
        printf("BACKWARD\n");
        camera.setMovement(1, 1.0);
    }
    if(key == GLFW_KEY_S && action == GLFW_RELEASE){
        printf("BACKWARD STOP\n");
        camera.setMovement(1, 0.0);
    }
    if(key == GLFW_KEY_A && action == GLFW_PRESS){
        printf("LEFT\n");
        camera.setMovement(2, 1.0);
    }
    if(key == GLFW_KEY_A && action == GLFW_RELEASE){
        printf("LEFT STOP\n");
        camera.setMovement(2, 0.0);
    }
    if(key == GLFW_KEY_D && action == GLFW_PRESS){
        printf("RIGHT\n");
        camera.setMovement(3, 1.0);
    }
    if(key == GLFW_KEY_D && action == GLFW_RELEASE){
        printf("RIGHT STOP\n");
        camera.setMovement(3, 0.0);
    }
    if(key == GLFW_KEY_Q && action == GLFW_PRESS){
        printf("YAW LEFT\n");
        camera.setRotation(0, 1.0f);
    }
    if(key == GLFW_KEY_Q && action == GLFW_RELEASE){
        printf("YAW LEFT STOP\n");
        camera.setRotation(0, 0.0f);
    }
    if(key == GLFW_KEY_E && action == GLFW_PRESS){
        printf("YAW RIGHT\n");
        camera.setRotation(1, 1.0f);
    }
    if(key == GLFW_KEY_E && action == GLFW_RELEASE){
        printf("YAW RIGHT STOP\n");
        camera.setRotation(1, 0.0f);
    }
    if(key == GLFW_KEY_R && action == GLFW_PRESS){
        printf("PITCH UP\n");
        camera.setRotation(2, 1.0f);
    }
    if(key == GLFW_KEY_R && action == GLFW_RELEASE){
        printf("PITCH UP STOP\n");
        camera.setRotation(2, 0.0f);
    }
    if(key == GLFW_KEY_F && action == GLFW_PRESS){
        printf("PITCH DOWN\n");
        camera.setRotation(3, 1.0f);
    }
    if(key == GLFW_KEY_F && action == GLFW_RELEASE){
        printf("PITCH DOWN STOP\n");
        camera.setRotation(3, 0.0f);
    }
    if(key == GLFW_KEY_SPACE && action == GLFW_PRESS){
        printf("UP\n");
        camera.setMovement(4, 1.0);
    }
    if(key == GLFW_KEY_SPACE && action == GLFW_RELEASE){
        printf("UP STOP\n");
        camera.setMovement(4, 0.0);
    }
    if(key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS){
        printf("DOWN\n");
        camera.setMovement(5, 1.0);
    }
    if(key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE){
        printf("DOWN STOP\n");
        camera.setMovement(5, 0.0);
    }
    else{
        std::cout << key << std::endl;
    }
}

static void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    camera.processMouseRotation((float)(xpos-xlast), (float)(ypos-ylast));
    xlast = xpos;
    ylast = ypos;
}
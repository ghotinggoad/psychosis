#include "../include/global.h"


void initGraphics(int SCREEN_WIDTH, int SCREEN_HEIGHT){
    glfwSetErrorCallback(error_callback);

    if(!glfwInit()){
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "psychosis", NULL, NULL);
    if(!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    //gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);
}

static void error_callback(int error, const char* description)
{
    printf("Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        printf("Closed!");
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void makeBuffers(){
    GLuint vertexBuffer, vertexShader, fragmentShader, program;
}
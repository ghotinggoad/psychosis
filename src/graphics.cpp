#include "../include/global.hpp"


void initGraphics(int SCREEN_WIDTH, int SCREEN_HEIGHT){
    glfwSetErrorCallback(error_callback);

    // initialize glfw
    if(!glfwInit()) exit(EXIT_FAILURE);

    // sets glfw window minimum version and other settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "psychosis", NULL, NULL);
    if(!window){
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // initialize glad/opengl (?)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) printf("Failed to initialize GLAD.");
    
    // set viewport in pixels
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

static void error_callback(int error, const char* description){
    printf("Error: %s\n", description);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  

void refreshWindow(){
    // clear window contents
    glClearColor(.2, .2, .2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // put drawing code in here

    // swap buffers
    glfwSwapBuffers(window);
}
#include "../include/global.hpp"


// designed resolution = resolution game sprites are designed for e.g. resolution of background file that is supposed to fill the screen
// sprite has designed resolution e.g. 960p , ratio scaling applied with "texture/(designed resolution/target resolution)" e.g. 960/480 = 2
// designed resolution has been set to 1280*960p for development
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;
int REFRESH_RATE = 60;
float FRAME_TIME = 1000/60.f;

float frameTime = 0.0f;
float lastTick = 0.0f;

GLFWwindow* window;
cCamera camera;

void initGraphics(){
    glfwSetErrorCallback(error_callback);

    // initialize glfw
    if(!glfwInit()) exit(EXIT_FAILURE);

    // sets glfw window minimum version and other settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    //window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "psychosis", NULL, NULL);  //windowed
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "psychosis", glfwGetPrimaryMonitor(), NULL);   //fullscreen
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
    float currentTick= glfwGetTime();
    frameTime = currentTick - lastTick;
    // clear window contents
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    lastTick = currentTick;
    // put drawing code in here
}
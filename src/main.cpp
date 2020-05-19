#include "../include/global.h"


// designed resolution = resolution game sprites are designed for e.g. resolution of background file that is supposed to fill the screen
// sprite has designed resolution e.g. 960p , ratio scaling applied with "texture/(designed resolution/target resolution)" e.g. 960/480 = 2
// designed resolution has been set to 1280*960p for development
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 960;
int REFRESH_RATE = 60;
float FRAME_TIME = 1000/60.f;

GLFWwindow* window;

int main(int argc, char *argv[]){
    (void)(argc);
    (void)(argv);

    initGraphics(SCREEN_WIDTH, SCREEN_HEIGHT);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
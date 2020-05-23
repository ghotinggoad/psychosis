#include "../include/global.hpp"


int main(int argc, char *argv[]){
    (void)(argc);
    (void)(argv);

    initGraphics();
    initInput();

    const GLubyte* glVersion = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "OpenGL Version: " << glVersion << std::endl << "GLSL Version: " << glslVersion << std::endl;
    if(glGenVertexArrays) printf("genVertexArrays supported.\n");

    initCube();

    while(!glfwWindowShouldClose(window)){

        refreshWindow();
        loopCube();
        glfwPollEvents();
        camera.processKeyMovement();
        camera.processKeyRotation();
    }

    quitCube();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
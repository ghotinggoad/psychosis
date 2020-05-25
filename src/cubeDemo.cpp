#include "../include/global.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


// all these unsigned int are IDs
// id of array object that stored calls to vertex attributes functions as well as the VBO "attached"
// id of buffer object that stored array data into the GPU memory
// id of element object that stores indices that OpenGL uses to decide which vertices to draw
// stores id of shaderProgram

unsigned int backgroundTexture, cubeTexture;
unsigned int backgroundVAO, demoVAO, cubeVAO, backgroundVBO, demoVBO, cubeVBO, backgroundEBO;
cShader background, rgbCubeDemo, colorCube, lightCube;
glm::vec3 lightPos = {1.2f, 1.0f, 2.0f};

void initCube(){
    // making a float array consisting of vertex information and colors in groups of 3
    float demoVertices[] = {
        // positions            // colors, only each corner's color is determined, the mixture of colors is automatically done by fragment interpolation
        -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 0.0f,   1.0f, 0.0f,

        -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
         1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 0.0f,   1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 1.0f,   0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

         1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 1.0f,   1.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 1.0f,   0.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,

        -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 1.0f,   1.0f, 1.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 1.0f,

        -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 1.0f,   1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,

         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 1.0f,   0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f
    };

    float vertices2D[] = {
        // position      texture coordinates
        -1.0f, -1.0f,    0.0f,  0.0f,
        -1.0f,  1.0f,    0.0f,  1.0f,
         1.0f, -1.0f,    1.0f,  0.0f,
         1.0f,  1.0f,    1.0f,  1.0f
    };
    unsigned int indices2D[] = {
        0, 1, 2,
        1, 2, 3
    };

                            // face's normal vector (a vector that is perpendicular to the face)
    float cubeVertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    glGenTextures(1, &backgroundTexture);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    // texture filtering stuff
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // texture loading
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("./media/background.png", &width, &height, &nrChannels, 0); 
    if (data){
        // generate texture from 2D image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // generate mipmap, basically a texture with "perpetual half sizes"
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &cubeTexture);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    width = 0;
    height = 0;
    nrChannels = 0;
    stbi_set_flip_vertically_on_load(true);
    data = stbi_load("./media/cube.png", &width, &height, &nrChannels, 0); 
    if (data){
        // generate texture from 2D image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // generate mipmap, basically a texture with "perpetual half sizes"
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    rgbCubeDemo.build("./shaders/demo.vert", "./shaders/demo.frag"); // crashes the program without any error
    background.build("./shaders/background.vert", "./shaders/background.frag");
    lightCube.build("./shaders/cube.vert", "./shaders/light.frag");
    colorCube.build("./shaders/cube.vert", "./shaders/lighting.frag");

    // GPU POINTERS AND MEMORY MANAGEMENT
    glGenVertexArrays(1, &backgroundVAO);
    glGenVertexArrays(1, &demoVAO);
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &backgroundVBO);
    glGenBuffers(1, &demoVBO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &backgroundEBO);

    // selecting the vertex array object, vertex buffer object and array attributes calls we're currently manipulating
    glBindVertexArray(backgroundVAO);
    glBindBuffer(GL_ARRAY_BUFFER, backgroundVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2D), vertices2D, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, backgroundEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2D), indices2D, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);

    printf("2D done.\n");


    glBindVertexArray(demoVAO);
    // selecting the buffer we're currently manipulating, then loading a program array data into the buffer.
    glBindBuffer(GL_ARRAY_BUFFER, demoVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(demoVertices), demoVertices, GL_STATIC_DRAW);  //GL_STATIC_DRAW, drawn once like background texture, probably sending it to hard to call memaddr
    // LINKING VERTEX ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // idk how to explain this, refer to https://learnopengl.com/Getting-started/Shaders and hover over glVertexAttribPointer()
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    printf("3D done.\n");


    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    printf("light source done.\n");


    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void loopCube(){
    glm::mat4 projection = glm::perspective(glm::radians(71.0f), SCREEN_WIDTH*1.0f / SCREEN_HEIGHT*1.0f, 0.1f, 1000.0f);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 model;

    glDisable(GL_DEPTH_TEST);

    glBindVertexArray(backgroundVAO);
    background.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    background.setInt("backgroundTexture", 1);
    // affect both front and back faces (3D mode), telling GPU to only draw lines
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // telling the GPU to draw specific element from the array, how many elements, element pointer data type, starting index "(void*)(INDEX*sizeof(GLfloat))"



    glEnable(GL_DEPTH_TEST);

    glBindVertexArray(demoVAO); // telling the GPU to use vertices data in the Vertex Buffer Object (which is stored together with all attributes info stored in the selected Vertex Array Object)
    rgbCubeDemo.use();
    // create transformations
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f));
    model = glm::rotate(model, glm::radians((float) glfwGetTime()*50.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    // note that we're translating the scene in the reverse direction of where we want to move
    rgbCubeDemo.setMat4("projection", projection);
    rgbCubeDemo.setMat4("view", view);
    rgbCubeDemo.setMat4("model", model);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    rgbCubeDemo.setInt("cubeTexture", 1);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 36); // telling the GPU to draw the array with primitive triangle, starting index in the array, how many vertices to draw.


    // rotating light
    glm::vec3 lightPosition = glm::vec3(glm::sin(glfwGetTime())*1.5f, 1.0f, glm::cos(glfwGetTime())*1.5f - 3);
    // abs so it doesn't go negative and turn my object invisible
    glm::vec3 lightColor = glm::vec3(abs(glm::sin(glfwGetTime()/2)), 0.0f, abs(glm::cos(glfwGetTime()/2)));
    
    glBindVertexArray(cubeVAO);
    lightCube.use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPosition);
    model = glm::scale(model, glm::vec3(0.2f));
    lightCube.setMat4("projection", projection);
    lightCube.setMat4("view", view);
    lightCube.setMat4("model", model);
    lightCube.setVec3("lightColor", lightColor);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    colorCube.use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
    colorCube.setMat4("projection", projection);
    colorCube.setMat4("view", view);
    colorCube.setMat4("model", model);
    // object is red but 0.1f for green and blue channels because no objects irl is perfectly red, object doesn't turn black (turns that of ambient) when no red light too.
    colorCube.setVec3("color", glm::vec3(1.0f, 0.1f, 0.1f));
    colorCube.setVec3("lightColor", lightColor);
    colorCube.setVec3("lightPosition", lightPosition);
    colorCube.setVec3("cameraPosition", camera.cameraPosition);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    

    glBindVertexArray(0);
    // swap buffers
    glfwSwapBuffers(window);
}

void quitCube(){
    glDeleteVertexArrays(1, &backgroundVAO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &demoVAO);
    glDeleteBuffers(1, &backgroundVBO);
    glDeleteBuffers(1, &demoVBO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &backgroundEBO);
}
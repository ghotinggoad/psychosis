#include "../include/global.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


// all these unsigned int are IDs
// id of array object that stored calls to vertex attributes functions as well as the VBO "attached"
// id of buffer object that stored array data into the GPU memory
// id of element object that stores indices that OpenGL uses to decide which vertices to draw
// stores id of shaderProgram

unsigned int backgroundTexture, crateTexture, crateSpecularTexture;
unsigned int backgroundVAO, cubeVAO, backgroundVBO, cubeVBO, backgroundEBO;
cShader background, rgbCubeDemo, colorCube, lightCube;
glm::vec3 lightPos = {1.2f, 1.0f, 2.0f};

unsigned int loadTexture(char const * path);

void initCube(){
    // making a float array consisting of vertex information and colors in groups of 3
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

    float cubeVertices[] = {
        // vertices for face,   // normal              // texture coordinates (some of the textures are upside down)
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f,  0.0f, -1.0f,     0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,     0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,

         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,     1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    1.0f,  0.0f,  0.0f,     1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    1.0f,  0.0f,  0.0f,     0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f,  0.0f,  0.0f,     0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    1.0f,  0.0f,  0.0f,     1.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f,     0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f,     0.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f,  1.0f,  0.0f,     0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f,  1.0f,  0.0f,     0.0f, 0.0f
    };

    
    backgroundTexture = loadTexture("./media/background.png");
    crateTexture = loadTexture("./media/crate.png");
    crateSpecularTexture = loadTexture("./media/crate_specular.png");

    rgbCubeDemo.build("./shaders/texturedCube.vert", "./shaders/texturedLighting.frag");
    background.build("./shaders/background.vert", "./shaders/background.frag");
    lightCube.build("./shaders/untexturedCube.vert", "./shaders/light.frag");
    colorCube.build("./shaders/untexturedCube.vert", "./shaders/material.frag");

    // GPU POINTERS AND MEMORY MANAGEMENT
    glGenVertexArrays(1, &backgroundVAO);
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &backgroundVBO);
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


    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    printf("3D done.\n");
    printf("light source done.\n");


    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void loopCube(){
    glm::mat4 projection = glm::perspective(glm::radians(71.0f), SCREEN_WIDTH*1.0f / SCREEN_HEIGHT*1.0f, 0.1f, 1000.0f);
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 model;
    glm::mat3 normalMatrixTransform;

    glDisable(GL_DEPTH_TEST);

    glBindVertexArray(backgroundVAO);
    background.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    background.setInt("backgroundTexture", 0);
    // affect both front and back faces (3D mode), telling GPU to only draw lines
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // telling the GPU to draw specific element from the array, how many elements, element pointer data type, starting index "(void*)(INDEX*sizeof(GLfloat))"


    glEnable(GL_DEPTH_TEST);

    // rotating light
    //glm::vec3 lightPosition = glm::vec3(glm::sin(glfwGetTime())*1.5f, 1.0f, glm::cos(glfwGetTime())*1.5f + 3);
    glm::vec3 lightPosition = glm::vec3(glm::sin(glfwGetTime())*5.0f, 1.0f, 3);
    // abs so it doesn't go negative and turn my object invisible
    //glm::vec3 lightColor = glm::vec3(abs(glm::sin(glfwGetTime()/2)), 0.0f, abs(glm::cos(glfwGetTime()/2)));
    glm::vec3 lightColor = glm::vec3(1.0f);

    glBindVertexArray(cubeVAO); // telling the GPU to use vertices data in the Vertex Buffer Object (which is stored together with all attributes info stored in the selected Vertex Array Object)
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

    // use cubeVertices now, so don't need to rebind cubeVAO
    rgbCubeDemo.use();
    // create transformations
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.0f));
    //model = glm::rotate(model, glm::radians((float) glfwGetTime()*50.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    normalMatrixTransform = glm::mat3(1.0f);
    normalMatrixTransform = glm::transpose(glm::inverse(model));
    // note that we're translating the scene in the reverse direction of where we want to move
    rgbCubeDemo.setMat4("projection", projection);
    rgbCubeDemo.setMat4("view", view);
    rgbCubeDemo.setMat4("model", model);
    rgbCubeDemo.setMat3("normalMatrixTransform", normalMatrixTransform);
    // light properties
    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
    glm::vec3 ambientColor = lightColor * glm::vec3(0.1f); // low influence
    rgbCubeDemo.setVec3("light.ambient", ambientColor);
    rgbCubeDemo.setVec3("light.diffuse", diffuseColor);
    rgbCubeDemo.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    rgbCubeDemo.setVec3("light.position", lightPosition);
    rgbCubeDemo.setFloat("light.constant", 1.0f);
    rgbCubeDemo.setFloat("light.linear", 0.045f);
    rgbCubeDemo.setFloat("light.quadratic", 0.0075f);	
    // material properties
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, crateTexture);
    rgbCubeDemo.setInt("material.diffuse", 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, crateSpecularTexture);
    rgbCubeDemo.setInt("material.specular", 2);
    rgbCubeDemo.setFloat("material.shininess", 32.0f);
    rgbCubeDemo.setVec3("cameraPosition", camera.cameraPosition);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 36); // telling the GPU to draw the array with primitive triangle, starting index in the array, how many vertices to draw.

    lightPosition = glm::vec3(glm::sin(glfwGetTime())*5.0f, 1.0f, 6);
    lightCube.use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPosition);
    model = glm::scale(model, glm::vec3(0.2f));
    lightCube.setMat4("model", model);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    rgbCubeDemo.use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 6.0f));
    //model = glm::rotate(model, glm::radians((float) glfwGetTime()*50.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    normalMatrixTransform = glm::mat3(1.0f);
    normalMatrixTransform = glm::transpose(glm::inverse(model));
    rgbCubeDemo.setMat4("model", model);
    rgbCubeDemo.setVec3("light.position", lightPosition);
    rgbCubeDemo.setFloat("light.constant", 1.0f);
    rgbCubeDemo.setFloat("light.linear", 0.0f);
    rgbCubeDemo.setFloat("light.quadratic", 0.0f);
    //rgbCubeDemo.setFloat("light.linear", 0.014f);
    //rgbCubeDemo.setFloat("light.quadratic", 0.0007f);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // rotating light
    lightPosition = glm::vec3(glm::sin(glfwGetTime())*1.5f, 1.0f, glm::cos(glfwGetTime())*1.5f - 3);
    lightCube.use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPosition);
    model = glm::scale(model, glm::vec3(0.2f));
    lightCube.setMat4("model", model);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    colorCube.use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
    normalMatrixTransform = glm::mat3(1.0f);
    normalMatrixTransform = glm::transpose(glm::inverse(model));
    colorCube.setMat4("projection", projection);
    colorCube.setMat4("view", view);
    colorCube.setMat4("model", model);
    colorCube.setMat3("normalMatrixTransform", normalMatrixTransform);

    // object is red but 0.1f for green and blue channels because no objects irl is perfectly red, object doesn't turn black (turns that of ambient) when no red light too.
    // colorCube.setVec3("light.ambient", glm::vec3(1.0f, 0.1f, 0.1f));
    
    // light properties
    diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
    ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
    colorCube.setVec3("light.ambient", ambientColor);
    colorCube.setVec3("light.diffuse", diffuseColor);
    colorCube.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
    colorCube.setVec3("light.position", lightPosition);
    // material properties
    colorCube.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    colorCube.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    colorCube.setVec3("material.specular", 0.5f, 0.5f, 0.5f); // specular lighting doesn't have full effect on this object's material
    colorCube.setFloat("material.shininess", 32.0f);
    colorCube.setVec3("cameraPosition", camera.cameraPosition);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    

    glBindVertexArray(0);
    // swap buffers
    glfwSwapBuffers(window);
}

unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void quitCube(){
    glDeleteVertexArrays(1, &backgroundVAO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &backgroundVBO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &backgroundEBO);
}
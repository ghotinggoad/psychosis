#include "../include/global.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"


// all these unsigned int are IDs
// id of array object that stored calls to vertex attributes functions as well as the VBO "attached"
// id of buffer object that stored array data into the GPU memory
// id of element object that stores indices that OpenGL uses to decide which vertices to draw
// stores id of shaderProgram

unsigned int backgroundTexture, cubeTexture;
unsigned int VAO2D, VAO3D, VBO2D, VBO3D, EBO2D, EBO3D;
cShader background, rgbCubeDemo;

// saving 10 locations of the cubes to render

void initCube(){
    /*
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(3);
    */

    // making a float array consisting of vertex information and colors in groups of 3
    float cubeVertices[] = {
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

        /*  reference element type
        -1.0f, -1.0f,  1.0f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
         1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
         1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 0.0f,   1.0f, 0.0f,

         1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 1.0f,   0.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 1.0f,   1.0f, 0.0f
        */
        
    };
    unsigned int cubeIndices[] = {
        /* reference
        0, 1, 2,
        0, 2, 3,

        0, 3, 4,
        4, 7, 0,

        4, 7, 6,
        6, 5, 4,

        6, 5, 2,
        2, 1, 6,

        0, 1, 6,
        6, 7, 0,

        2, 3, 4,
        4, 5, 2,
        */
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35
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
    // texture filtering stuff
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // texture loading
    width = 0;
    height = 0;
    nrChannels = 0;
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

    rgbCubeDemo.build("./shaders/cube.vs", "./shaders/cube.fs"); // crashes the program without any error
    background.build("./shaders/background.vs", "./shaders/background.fs");

    // GPU POINTERS AND MEMORY MANAGEMENT
    glGenVertexArrays(1, &VAO2D);
    glGenVertexArrays(1, &VAO3D);
    glGenBuffers(1, &VBO2D);
    glGenBuffers(1, &VBO3D);
    glGenBuffers(1, &EBO2D);
    glGenBuffers(1, &EBO3D);


    // selecting the vertex array object, vertex buffer object and array attributes calls we're currently manipulating
    glBindVertexArray(VAO2D);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2D);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2D), vertices2D, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2D);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2D), indices2D, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    printf("2D done.\n");




    glBindVertexArray(VAO3D);
    // selecting the buffer we're currently manipulating, then loading a program array data into the buffer.
    glBindBuffer(GL_ARRAY_BUFFER, VBO3D);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);  //GL_STATIC_DRAW, drawn once like background texture, probably sending it to hard to call memaddr

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3D);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

    // LINKING VERTEX ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // idk how to explain this, refer to https://learnopengl.com/Getting-started/Shaders and hover over glVertexAttribPointer()
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    printf("3D done.\n");

    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // affect both front and back faces (3D mode), telling GPU to only draw lines
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


}

void loopCube(){

    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT, GL_FILL);

    background.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glUniform1i(glGetUniformLocation(background.ID, "backgroundTexture"), 0);

    glBindVertexArray(VAO2D);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // telling the GPU to draw specific element from the array, how many elements, element pointer data type, starting index "(void*)(INDEX*sizeof(GLfloat))"



    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    // create transformations
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians((float) glfwGetTime()*50.0f), glm::vec3(1.0f, 0.0f, 1.0f)); 

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(71.0f), SCREEN_WIDTH*1.0f / SCREEN_HEIGHT*1.0f, 0.1f, 1000.0f);

    // get matrix's uniform location and set matrix
    rgbCubeDemo.use();
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    glUniform1i(glGetUniformLocation(rgbCubeDemo.ID, "cubeTexture"), 1);
    
    unsigned int modelLoc = glGetUniformLocation(rgbCubeDemo.ID, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    unsigned int projectionLoc = glGetUniformLocation(rgbCubeDemo.ID, "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO3D); // telling the GPU to use vertices data in the Vertex Buffer Object (which is stored together with all attributes info stored in the selected Vertex Array Object)
    
    glm::mat4 view = camera.getViewMatrix();
    // note that we're translating the scene in the reverse direction of where we want to move 
    unsigned int viewLoc = glGetUniformLocation(rgbCubeDemo.ID, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    // glDrawArrays(GL_TRIANGLES, 0, 3); // telling the GPU to draw the array with primitive triangle, starting index in the array, how many vertices to draw.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    glBindVertexArray(0);
    
    // swap buffers
    glfwSwapBuffers(window);
}

void quitCube(){
    glDeleteVertexArrays(1, &VAO2D);
    glDeleteVertexArrays(1, &VAO3D);
    glDeleteBuffers(1, &VBO2D);
    glDeleteBuffers(1, &VBO3D);
    glDeleteBuffers(1, &EBO2D);
    glDeleteBuffers(1, &EBO3D);
}
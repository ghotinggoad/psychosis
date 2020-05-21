#include "../include/global.hpp"


// all these unsigned int are IDs
// id of array object that stored calls to vertex attributes functions as well as the VBO "attached"
// id of buffer object that stored array data into the GPU memory
// id of element object that stores indices that OpenGL uses to decide which vertices to draw
// stores id of shaderProgram
unsigned int VAO, VBO, EBO;
cShader rgbTriangle;

void testCode(){
    /*
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(3);
    */

    // making a float array consisting of vertex information and colors in groups of 3
    float vertices[] = {
        // positions            // colors, only each corner's color is determined, the mixture of colors is automatically done by fragment interpolation
        -1.0f, -1.0f,  0.0f,     1.0f, 0.0f, 0.0f,
        -1.0f,  1.0f,  0.0f,     0.0f, 1.0f, 0.0f,
         1.0f,  1.0f,  0.0f,     0.0f, 0.0f, 1.0f,
         1.0f, -1.0f,  0.0f,     1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,     0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,     1.0f, 0.0f, 1.0f,
         1.0f,  1.0f, -1.0f,     1.0f, 1.0f, 1.0f,
         1.0f, -1.0f, -1.0f,     0.0f, 0.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,
        1, 4, 0,
        5, 1, 4,
        3, 2, 6,
        6, 7, 3,
        1, 5, 6,
        1, 6, 2,
        4, 5, 7,
        5, 6, 7,
        4, 0, 7,
        3, 7, 0
    };

    rgbTriangle.build("./shaders/triangle.vs", "./shaders/triangle.fs"); // crashes the program without any error


    // GPU POINTERS AND MEMORY MANAGEMENT
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // selecting the vertex array object, vertex buffer object and array attributes calls we're currently manipulating
    glBindVertexArray(VAO);

    // selecting the buffer we're currently manipulating, then loading a program array data into the buffer.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  //GL_STATIC_DRAW, drawn once like background texture, probably sending it to hard to call memaddr

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // LINKING VERTEX ATTRIBUTES
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // idk how to explain this, refer to https://learnopengl.com/Getting-started/Shaders and hover over glVertexAttribPointer()
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // affect both front and back faces (3D mode), telling GPU to only draw lines
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //rgbTriangle.use();    // basically do everything of the first few steps of GPU pipeline, vertex & fragment shading.
}

void testLoop(){
    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f)); // offset/shifting
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 1.0f)); // rotating

    // get matrix's uniform location and set matrix
    rgbTriangle.use();
    unsigned int transformLoc = glGetUniformLocation(rgbTriangle.ID, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));


    // Called right before drawing
    //rgbTriangle.use();
    glBindVertexArray(VAO); // telling the GPU to use vertices data in the Vertex Buffer Object (which is stored together with all attributes info stored in the selected Vertex Array Object)
    // glDrawArrays(GL_TRIANGLES, 0, 3); // telling the GPU to draw the array with primitive triangle, starting index in the array, how many vertices to draw.
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // telling the GPU to draw specific element from the array, how many elements, element pointer data type, starting index
    glBindVertexArray(0);
    
    // swap buffers
    glfwSwapBuffers(window);
}

void testQuit(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
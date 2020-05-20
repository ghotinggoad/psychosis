#include "../include/global.hpp"


// all these unsigned int are IDs
// id of array object that stored calls to vertex attributes functions as well as the VBO "attached"
// id of buffer object that stored array data into the GPU memory
// id of element object that stores indices that OpenGL uses to decide which vertices to draw
// stores id of shaderProgram
unsigned int VAO, VBO, EBO, shaderProgram;

// writing vertex source and compiling of shader program. Vertex = coordinates. Also telling shader to transform vertices of 3 to vertices of 4
const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main(){\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" // gl_Position, contains the position of the current vertex, think &pointer that points to a vec4 data in memory.
    "}\0";

// writing fragment source and compiling of shader program. Fragment = color
const char * fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main(){\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

void testCode(){
    /*
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(3);
    */

    // making a float array consisting of vertex information in groups of 3
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };


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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // unbind buffers
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // GPU PIPELINE
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // check success of shader compiling
    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "Error, Vertex Shader compilation failed.\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "Error, Fragment Shader compilation failed.\n" << infoLog << std::endl;
    }

    // create shader program object, a "final linked version of multiple shaders combined"
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);   //remember to link after attaching

    glGetProgramiv(shaderProgram, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error, Shader Program compilation failed.\n" << infoLog << std::endl;
    }

    // delete shader after linking because they are no longer needed, freeing up VRAM
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // affect both front and back faces (3D mode), telling GPU to only draw lines
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void testLoop(){
    // Called right before drawing
    glUseProgram(shaderProgram);    // basically do everything of the first few steps of GPU pipeline, vertex & fragment shading.
    glBindVertexArray(VAO); // telling the GPU to use vertices data in the Vertex Buffer Object (which is stored together with all attributes info stored in the selected Vertex Array Object)
    // glDrawArrays(GL_TRIANGLES, 0, 3); // telling the GPU to draw the array with primitive triangle, starting index in the array, how many vertices to draw.
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); // telling the GPU to draw specific element from the array, how many elements, element pointer data type, starting index
    glBindVertexArray(0);
    
    // swap buffers
    glfwSwapBuffers(window);
}

void testQuit(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
}
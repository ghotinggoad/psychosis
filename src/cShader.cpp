#include "../include/global.hpp"


cShader::cShader(){
    ID = 0;
}

void cShader::build(const char* vertexPath, const char* fragmentPath){
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "Error, shaders file not found in 'shaders' folder.\n" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    
    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "Error, Vertext Shader " << vertexPath << " cannot be compiled.\n" << infoLog << std::endl;
    };
    
    // similiar for Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "Error, Fragment Shader " << fragmentPath << " cannot be compiled.\n" << infoLog << std::endl;
    };
    
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Error, Shader Program cannot be linked.\n" << infoLog << std::endl;
    }
    
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void cShader::use(){
    glUseProgram(ID);
}

void cShader::setBool(const std::string &name, bool value) const{         
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void cShader::setInt(const std::string &name, int value) const{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void cShader::setFloat(const std::string &name, float value) const{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void cShader::setVec2(const std::string &name, const glm::vec2 &value) const{ 
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void cShader::setVec2(const std::string &name, float x, float y) const{ 
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
}
    
void cShader::setVec3(const std::string &name, const glm::vec3 &value) const{ 
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}
void cShader::setVec3(const std::string &name, float x, float y, float z) const{ 
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
}

void cShader::setVec4(const std::string &name, const glm::vec4 &value) const{ 
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
}

void cShader::setVec4(const std::string &name, float x, float y, float z, float w) const{ 
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
}

void cShader::setMat2(const std::string &name, const glm::mat2 &mat) const{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void cShader::setMat3(const std::string &name, const glm::mat3 &mat) const{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void cShader::setMat4(const std::string &name, const glm::mat4 &mat) const{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
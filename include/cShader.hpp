#ifndef CSHADER_H
#define CSHADER_H


class cShader{
    public:
        // the program ID
        unsigned int ID;

        // constructor reads and builds the shader
        cShader();
        // reads and builds the shader
        void build(const char* vertexPath, const char* fragmentPath);
        // use/activate the shader
        void use();
        // utility uniform functions
        void setBool(const std::string &name, bool value) const;  
        void setInt(const std::string &name, int value) const;   
        void setFloat(const std::string &name, float value) const;
};

#endif
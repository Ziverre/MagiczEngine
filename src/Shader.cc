#include "Shader.h"

Shader::Shader(){};

void Shader::Init(const char* vPath, const char* fPath)
{
    _initialized = false;
    _vertex = 0; _fragment = 0;
    //f = fragment, v = vertex
    bool vSuccess = false, fSuccess = false;
    std::string vData, fData;

    //TO DO: Fix the loader somehow failing, for now I pretend that those files are "loaded"

    vData = LoadFromFile(vPath, &vSuccess);
    fData = LoadFromFile(fPath, &fSuccess);

    if (!vSuccess || !fSuccess)
        return;

    const char* vCode = vData.c_str();
    const char* fCode = fData.c_str();

    _vertex = Compile(vCode, GL_VERTEX_SHADER);
    _fragment = Compile(fCode, GL_FRAGMENT_SHADER);

    if (!_vertex || !_fragment)
    //The error message is already handled by the Compile() function, therefore only return is needed for the constructor.
        return;

    //Variables for checking errors

    int success;
    char infoLog[512];

    //Link program

    _id = glCreateProgram();
    glAttachShader(_id, _vertex);
    glAttachShader(_id, _fragment);
    glLinkProgram(_id);

    glGetProgramiv(_id, GL_LINK_STATUS, &success);
    if (!success){
        glGetProgramInfoLog(_id, 512, NULL, infoLog);
        std::cout << "[ERROR] Linking failed: \n" << infoLog << std::endl;

        glDeleteShader(_vertex);
        glDeleteShader(_fragment);

        return;
    }

    glDeleteShader(_vertex);
    glDeleteShader(_fragment);

    _initialized = true;
}

std::string Shader::LoadFromFile(const char* path, bool* success){

    std::string shaderData;
    std::ifstream shaderFile;
    std::stringstream shaderStringStream;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        shaderFile.open(path);

        shaderStringStream << shaderFile.rdbuf();

        shaderFile.close();

        shaderData = shaderStringStream.str();

        *success = true;
    }
    catch(std::ifstream::failure& e){
        std::cout << "[ERROR] Failed to load file: " << e.what() << std::endl;
        *success = false;
    }
    return shaderData;
}

unsigned int Shader::Compile(const char* shaderCode, int type){

    unsigned int shader;
    int success;
    char infoLog[512];

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success){
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "[ERROR] Compilation failed: \n" << infoLog << std::endl;
    }

    return shader;
}

bool Shader::isInitialized(){
    return _initialized;
}

/*
    Usage: Activates shader program using the ID (stored in _id)
*/

void Shader::Use(){
    if (isInitialized())
        glUseProgram(_id);
}

/*
    Usage: Set uniform variables
*/

unsigned int Shader::GetID(){
    return _id;
}

void Shader::SetBool(const std::string& name, bool value){
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
}

void Shader::SetFloat(const std::string& name, float value){
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::SetInt(const std::string& name, int value){
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

Shader::~Shader(){
}

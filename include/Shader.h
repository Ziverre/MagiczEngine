#ifndef OPZ_SHADER_H
#define OPZ_SHADER_H

#include <gl/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
    public:
        unsigned int _id;

        Shader();
        void Init(const char* vPath, const char* fPath);

        //TO DO: Move this method to a class responsible for handling file read/write
        std::string LoadFromFile(const char* path, bool* success);

        bool IsInitialized();

        void Use();

        unsigned int GetID();

        int GetUniform(const std::string& name);

        void SetBool(const std::string& name, bool value);
        void SetFloat(const std::string& name, float value);
        void SetInt(const std::string& name, int value);

        virtual ~Shader();

    protected:

    private:
        bool _initialized;
        unsigned int _vertex, _fragment;
        unsigned int Compile(const char* shaderCode, int type);
};

#endif // OPZ_SHADER_H

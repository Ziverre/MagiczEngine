#ifndef OPZ_TEXTURE_H
#define OPZ_TEXTURE_H

#include <iostream>
#include <string>

#include <gl/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

#include "Global.h"
#include "Shader.h"

class Texture
{
    public:
        static Shader s_rgba_shader;

        Texture();

        void Init(std::string filename);
        void InitBlankState(); //Generates a "blank state texture"


        bool isInitialized();

        //State setters

        void Use();

        virtual ~Texture();

    protected:

    private:

        void _Generate_2D_GL_Texture(int *id){}; //TO DO: Give it a task
        void _GenerateFBO();
        void _InitShaders();

        unsigned int _id, _fbo, _vao;
        int _width, _height;

        bool _initialized;
};

#endif // OPZ_TEXTURE_H

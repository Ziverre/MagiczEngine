#ifndef OPZ_TEXTURE_H
#define OPZ_TEXTURE_H

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GL/glu.h>

#include "Global.h"
#include "Shader.h"
#include "Bitmap.h"
#include "Palette.h"

//TEXTURE PAGE
struct sTexturePage {

    unsigned int _text_id;
    unsigned int _fbo_id;

    //Use IF Texture is in 256 color palette format
    float _palette_index;
};


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

        //void _Generate_2D_GL_Texture(unsigned int id, int width, int height, void* data){}; //TO DO: Give it a task
        void _GenerateFBO();
        void _InitShaders();

        unsigned int _id, _fbo, _vao;
        int _width, _height;

        bool _initialized;
};

#endif // OPZ_TEXTURE_H

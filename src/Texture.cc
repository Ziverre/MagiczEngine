//TO DO: Make texture lookup table

#include "Texture.h"

#include "Bitmap.h"

Shader Texture::s_rgba_shader;

Texture::Texture()
{
    _initialized = false; // :)
    _width = 0; _height = 0; _fbo = 0;

    glGenTextures(1, &_id);

    _InitShaders();
    //_GenerateFBO();

}

void Texture::Init(std::string fileName){
    //TO DO: Implement the actual IO (currently mimicking)

    Bitmap bmp;

    _width = 4, _height = 4;
    unsigned char transparentData[] = {
        255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255,
        255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255,
        255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255,
        255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255
    };

    bmp.ReadBMP(fileName);

    unsigned char* data = (unsigned char*) bmp.GetData();

    if (!!data)
    {
        bmp.GetSize(&_width, &_height);
    }
    else
    {
        data = transparentData;
    }

    //glGenTextures(1, &_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //I have been using OpenGL for months now, yet never realized that GL_BGR exists until now. What a shame.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    //

    _GenerateFBO();

}

void Texture::InitBlankState(){
    _width = 2, _height = 2;
    unsigned char data[] = {
        255, 255, 255, 255,  255, 255, 255, 255,
        255, 255, 255, 255,  255, 255, 255, 255,
    };

    //glGenTextures(1, &_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    //TO DO: Add support for RGBA bitmap too
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

    //
    _GenerateFBO();
}

void Texture::_InitShaders(){
    s_rgba_shader.Init("shaders/texture/texture.vs", "shaders/texture/rgba.fs");
}

bool Texture::isInitialized(){
    return _initialized;
}


void Texture::Use(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::_GenerateFBO(){
    glGenFramebuffers(1, &_fbo);

}

Texture::~Texture()
{
    //dtor
}

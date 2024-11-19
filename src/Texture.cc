//TO DO: Make texture lookup table

#include "Texture.h"

Shader Texture::s_rgba_shader;
Shader Texture::s_indexed_shader;

Texture::Texture()
{
    _initialized = false; // :)
    _width = 0; _height = 0; _fbo = 0;

    _vao = Global.GetDefaultVAO();

    glGenTextures(1, &_id);

    _InitShaders();

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
    s_indexed_shader.Init("shaders/texture/texture.vs", "shaders/texture/indexed.fs");

    _uniform_indexed.index = s_indexed_shader.GetUniform("index");
}

bool Texture::isInitialized(){
    return _initialized;
}

//-------------------------------------------------------------------

void Texture::SetPalette(Palette* palette){
    _palette = palette;

}

void Texture::SetPaletteIndex(int index){
    _palette_index = index;

}

void Texture::Generate(){

    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

    glViewport(0, 0, _width, _height);

    if (s_indexed_shader.IsInitialized()){

        s_indexed_shader.Use();

        _palette->Use();
        glUniform1f(_uniform_indexed.index, static_cast<float>(_palette_index));
        std::cout << static_cast<float>(_palette_index) << std::endl;

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

    }

    /*if (s_rgba_shader.IsInitialized()){

        s_rgba_shader.Use();

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

    }*/
    Global.RestoreViewport();

    glBindFramebuffer(GL_FRAMEBUFFER, 0); //and pray that it works
}

//-------------------------------------------------------------------

void Texture::Use(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::_GenerateFBO(){
    glGenFramebuffers(1, &_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _id, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){

        std::cout << "Framebuffer is ready." << std::endl;
    }else{
        std::cout << "You fucked up." << std::endl;
    }

    glViewport(0, 0, _width, _height);
    if (s_rgba_shader.IsInitialized()){

        s_rgba_shader.Use();

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);

    }
    Global.RestoreViewport();

    glBindFramebuffer(GL_FRAMEBUFFER, 0); //and pray that it works

}

Texture::~Texture()
{
    //dtor
}

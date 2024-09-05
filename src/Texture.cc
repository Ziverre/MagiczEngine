//TO DO: Make texture lookup table

#include "Texture.h"

#include "Bitmap.h"

Texture::Texture()
{
    _initialized = false; // :)
}

void Texture::Init(std::string fileName){

    Bitmap bmp;

    int width = 4, height = 4;
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
        bmp.GetSize(&width, &height);
    }
    else
    {
        data = transparentData;
    }



    glGenTextures(1, &_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

}

bool Texture::isInitialized(){
    return _initialized;
}


void Texture::Use(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _id);
}

Texture::~Texture()
{
    //dtor
}

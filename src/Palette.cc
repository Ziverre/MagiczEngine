#include "Palette.h"

Palette::Palette()
{
    //ctor
    _loaded = false;
    _tex_id = 0;
}

bool Palette::Load(std::string fileName){

    Bitmap pal;
    pal.ReadBMP(fileName);

    if (!pal.GetPalette()){
        std::cout << "Bitmap fucked up" << std::endl;
        return false;
    }

    _Generate_GL_Texture(pal.GetPalette());
    //std::cout << _tex_id << std::endl;

    return false;
}

//BINDS TO THE SLOT 0
void Palette::Use(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _tex_id);
    std::cout << "bound texture " << _tex_id << std::endl;
}

//------------------------------------------------------

void Palette::_Generate_GL_Texture(void* bitmap){

    glGenTextures(1, &_tex_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0, GL_BGRA, GL_UNSIGNED_BYTE, bitmap);
}

Palette::~Palette()
{
    //dtor
}

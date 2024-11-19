#ifndef OPZ_PALETTE_H
#define OPZ_PALETTE_H

#include <GL/glew.h>
#include <GL/glu.h>

#include <string>
#include <fstream>
#include <iostream>

#include "Bitmap.h"

class Palette
{
    public:
        Palette();

        bool Load(std::string fileName);

        void Use();

        virtual ~Palette();

    protected:

    private:

        void _Generate_GL_Texture(void* bitmap);

        bool _loaded;

        unsigned int _tex_id;
};

#endif // OPZ_PALETTE_H

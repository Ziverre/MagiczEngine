#ifndef OPZ_PALETTE_H
#define OPZ_PALETTE_H

#include <GL/glew.h>
#include <GL/glu.h>

#include <string>
#include <fstream>
#include <iostream>

class Palette
{
    public:
        Palette();

        bool Load(std::string fileName);

        void Use();

        virtual ~Palette();

    protected:

    private:

        void _Generate_GL_Texture();
        bool _ReadFile(std::string fileName);

        bool _loaded;

        unsigned int _tex_id;
        char _data[256 * 4]; //TO DO: *Probably* make it so it gets garbage collected
};

#endif // OPZ_PALETTE_H

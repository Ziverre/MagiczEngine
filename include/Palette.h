#ifndef OPZ_PALETTE_H
#define OPZ_PALETTE_H

#include <string>
#include <fstream>
#include <iostream>

#include <gl/glew.h>
#include <gl/glu.h>

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

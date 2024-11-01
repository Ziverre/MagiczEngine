#ifndef OPZ_GLOBAL_H
#define OPZ_GLOBAL_H

#include <gl/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

#include <iostream>

class _Global
{
    public:
        _Global() {}

        void Configure(int width, int height);
        unsigned int GetDefaultVAO();
        void RestoreViewport();

    private:
        void _SetDefaultVAO();
        //
        unsigned int _default_vao = 0;
        //TO DO: RE DO :D
        int _width, _height;
};

extern _Global Global;

#endif // OPZ_DEFAULT_H

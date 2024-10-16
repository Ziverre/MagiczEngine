#ifndef OPZ_GLOBAL_H
#define OPZ_GLOBAL_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <iostream>

class _Global
{
    public:
        _Global() {}

        void Configure();
        unsigned int GetDefaultVAO();

    private:
        void SetDefaultVAO();
        //
        unsigned int _default_vao = 0;
};

extern _Global Global;

#endif // OPZ_DEFAULT_H

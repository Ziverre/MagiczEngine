#ifndef OPZ_TEXTURE_H
#define OPZ_TEXTURE_H

#include <iostream>
#include <string>

#include <gl/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

class Texture
{
    public:
        Texture();

        void Init(std::string filename);
        bool isInitialized();

        void Use();

        virtual ~Texture();

    protected:

    private:
        bool _initialized;
        unsigned int _id;
};

#endif // OPZ_TEXTURE_H

#ifndef OPZ_DRAWABLE_H
#define OPZ_DRAWABLE_H

#include "Shader.h"

class Drawable
{
    public:
        static Shader s_shader;

        Drawable();

        //virtual void SetUniformAddr() = 0;

        virtual float GetZ() = 0;

        virtual void Update() = 0;
        virtual void Draw() = 0;

        virtual   ~Drawable();

    protected:

    private:

};

#endif // DRAWABLE_H

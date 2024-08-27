#ifndef OPZ_BALL_H
#define OPZ_BALL_H

#include "Drawable.h"
#include <cmath>

class Ball : public Drawable
{
    public:
        static Shader s_shader;

        Ball();

        //
        void SetCoords(int x, int y, int z);
        void SetCoords(float x, float y, float z);

        void SetSize(int s);

        void GetCoords(float* x, float* y);

        float GetSize();

        //
        virtual void SetUniformAddr() override;

        virtual void Update() override;
        virtual void Draw() override;

        virtual float GetZ() override;

        //
        virtual ~Ball();

    protected:

    private:
        //variables to bind
        unsigned int vao, vbo, ebo;
        float _x, _y, _z, _rad;
        //gotta see if i could optimize unicorns even further
        int _rad_addr, _x_addr, _y_addr, _fuzz_addr;


};

#endif // BALL_H

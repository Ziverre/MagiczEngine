#ifndef OPZ_BALL_H
#define OPZ_BALL_H

#include <cmath>

#include "Drawable.h"

struct sBallUniformAddress {
    int diameter = -1;
    int x = -1;
    int y = -1;
    int fuzz = -1;
};

class Ball : public Drawable
{
    public:
        static Shader s_shader;

        Ball();

        //
        void SetCoords(int x, int y, int z);
        void SetCoords(float x, float y, float z);

        void SetDiameter(int s);

        void GetCoords(float* x, float* y);

        float GetDiameter();

        //
        void SetUniformAddr();

        virtual void Update() override;
        virtual void Draw() override;

        virtual float GetZ() override;

        //
        virtual ~Ball();

    protected:

    private:
        //variables to bind
        unsigned int vao, vbo, ebo;
        float _x, _y, _z, _diameter;

        sBallUniformAddress _uniform;


};

#endif // BALL_H

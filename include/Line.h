#ifndef OPZ_LINE_H
#define OPZ_LINE_H

#include "Drawable.h"
#include "Ball.h"

#include <cmath>
#include <iostream>

class Line : public Drawable
{
    public:
        static Shader s_shader;

        //
        Line();

        //
        void SetStartAndEndBalls(Ball* startBall, Ball* endBall);

        //
        virtual void SetUniformAddr() override;

        virtual void Update() override;
        virtual void Draw() override;

        virtual float GetZ() override;

        //
        virtual ~Line();

    protected:

    private:
        //variables to bind
        unsigned int vao, vbo, ebo;
        float _x, _y, _z; //?

        int _start_x_addr, _start_y_addr, _end_x_addr, _end_y_addr, _rad_addr;
        Ball* _startBall; Ball* _endBall;


};

#endif // OPZ_LINE_H

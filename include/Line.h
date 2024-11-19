#ifndef OPZ_LINE_H
#define OPZ_LINE_H

#include <cmath>
#include <iostream>

#include "Drawable.h"
#include "Ball.h"

struct sLineUniformAddress {
    int start_x = -1;
    int start_y = -1;
    int end_x = -1;
    int end_y = -1;
    int start_diameter = -1;
    int end_diameter = -1;
};

class Line : public Drawable
{
    public:
        static Shader s_shader;

        //
        Line();

        //
        void SetStartAndEndBalls(Ball* startBall, Ball* endBall);

        //
        void SetUniformAddr();

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

        int _start_x_addr, _start_y_addr,
            _end_x_addr, _end_y_addr,
            _start_diameter_addr, _end_diameter_addr;

        sLineUniformAddress _uniform;

        Ball* _startBall; Ball* _endBall;


};

#endif // OPZ_LINE_H

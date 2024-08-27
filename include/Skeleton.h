//THIS WHOLE THING IS TEMPORARY, MUST BE RE-IMPLEMENTED

#ifndef OPZ_SKELETON_H
#define OPZ_SKELETON_H

#include "Ball.h"

#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

struct sBallCoord {
    int x;
    int y;
    int z;
    int rx;
    int ry;
    int rz;
};

struct sBallFrame {
    std::vector<sBallCoord> coords;
};

struct sBallAnimation {
    int number;
    std::vector<sBallFrame> frames;
};

class Skeleton
{
    public:
        Skeleton();

        virtual void Init();

        virtual void Update();
        virtual void Render();

        virtual ~Skeleton();

    protected:

    private:
        bool _ready;
        int _numBallz;
        float _x, _y, _z;
        float _rx, _ry, _rz;
        //to do: decided whether this gonna include everything, or just balls
        std::vector<Ball*> _ballz;
        std::vector<Drawable*> _ballz_view; //for sorting (to do: do better)
        //TO DO: ... (I think this should belong in a static variable, why repeat the same thing everytime)
        struct sBallAnimation _animation;
};

#endif // OPZ_SKELETON_H

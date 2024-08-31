#include "Skeleton.h"

Skeleton::Skeleton()
{
    _x = 320.0; _y = 360.0; _z = 0.0;
    _rx = 0.0; _ry = 0.0; _rz = 0.0;
}

void Skeleton::Init(){
    _ready = false;

    std::vector<int> sizes;
    std::ifstream a1;
    a1.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
    	a1.open("ptzfiles/CAT.bsa", std::ios::in| std::ios::binary);
		int ballSize = 0;
		int numBallz = 0;
		a1.read((char*)&numBallz, 4);

		_numBallz = numBallz;

		for (int i = 0; i < _numBallz; i++){
            a1.read((char*)&ballSize, 4);

            Ball* ball = new Ball();
            ball->SetUniformAddr();
            ball->SetDiameter(ballSize);

            _ballz.push_back(ball);
            _ballz_view.push_back(ball);
		}

	}catch(std::ifstream::failure& e){
        perror("[ERROR] Failed to process file: ");
        return;
    }

    std::ifstream b1;
    b1.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
    	b1.open("ptzfiles/CAT0.bfa", std::ios::in| std::ios::binary);
		int x = 0, y = 0, z = 0;
		int numFramez = 0;

		//struct sBallAnimation animation;

		b1.read((char*)&numFramez, 4);

		_animation.number = numFramez;

        for (int frameN =0; frameN < numFramez; frameN++){
            struct sBallFrame frame;
            for (int i = 0; i < _numBallz; i++){

                b1.read((char*)&x, 4);
                b1.read((char*)&y, 4);
                b1.read((char*)&z, 4);

                struct sBallCoord coord;

                coord.x = x; coord.y = y; coord.z = z;
                coord.rx = 0; coord.ry = 0; coord.rz = 0;

                frame.coords.push_back(coord);

                _ballz[i]->SetCoords(coord.x/2 + 320, coord.y/2 + 360, coord.z);

                b1.ignore(12);
            }
            _animation.frames.push_back(frame);
        }

	}catch(std::ifstream::failure& e){
        perror("[ERROR] Failed to process file: ");
        return;
    }
    _ready = true;
}

void Skeleton::Update(){

    if (!_ready)
        return;

    struct sBallFrame frame = _animation.frames[0];


    //------------------------------------

    _ry += 0.05;

    //Calculate the sine/cosine once

    float rYSin = std::sin(_ry);
    float rYCos = std::cos(_ry);

    for (int i = 0; i < _numBallz; i++){

        //TO DO: Idk, this kinda irritates me tbh

        float xf = static_cast<float>(frame.coords[i].x);
        float zf = static_cast<float>(frame.coords[i].z);

        float zz = zf;

        zf = (zz * rYCos) - (xf * rYSin);
        xf = (xf * rYCos) + (zz * rYSin);

        float z = std::round(zf);
        float x = std::round(xf);

        _ballz[i]->SetCoords(x/2.0 + _x, static_cast<float>(frame.coords[i].y/2) + _y, z/2.0);
    }


    std::sort(_ballz_view.begin(), _ballz_view.end(), [](Drawable* b1, Drawable* b2){
        return b2->GetZ() < b1->GetZ();
    });
}

void Skeleton::Render(){
    // TO DO: Implement animation

    for (int i = 0; i < _numBallz; i++){
        //_ballz_view[i]->Update();
        _ballz_view[i]->Draw();
    }
}

Skeleton::~Skeleton()
{
    //dtor
    for (Ball* ball : _ballz)
        delete ball;
}

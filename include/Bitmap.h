#ifndef OPZ_BITMAP_H
#define OPZ_BITMAP_H


#include <string>
#include <vector>
#include <fstream>
#include <iostream>


class Bitmap
{
    public:
        Bitmap();

        void ReadBMP(std::string fileName);

        //TO DO: Probably give this a better name
        void GetSize(int* width, int* height);

        void* GetData();

        virtual ~Bitmap();

        //

    protected:

    private:
        std::vector<char> _data;
        int _width, _height;
        bool _readable;
};

#endif // OPZ_BITMAP_H

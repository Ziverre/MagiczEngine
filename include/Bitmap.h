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
        void* GetPalette();

        virtual ~Bitmap();

        //

    protected:

    private:
        std::vector<char> _data;
        int _width, _height;
        bool _readable, _has_palette;

        char _palette[256 * 4];
};

#endif // OPZ_BITMAP_H

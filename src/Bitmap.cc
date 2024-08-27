#include "Bitmap.h"

Bitmap::Bitmap() :  _width(0), _height(0), _readable(false)
{
    //ctor
}

void Bitmap::ReadBMP(std::string fileName)
{
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    //fuck the performance, of course (TO DO: optimize this shit)
    try{
    	file.open(fileName, std::ios::in| std::ios::binary);

		char signature[2] = {0, 0};

		file.read(signature, 2);

		if (signature[0] != 0x42 || signature[1] != 0x4D){
            std::cout << "[BMP ERROR] Invalid BMP signature" << std::endl;
            return;
		}

		file.ignore(12);

		int headerSize = 0;
		file.read((char*)&headerSize, 4);

		if (headerSize != 40){
            std::cout << "[BMP ERROR] Only BITMAPINFOHEADER = 40 is supported" << std::endl;
            return;
		}

		//The size definitelly matters to the OpenGL texture

		file.read((char*)&_width, 4);
		file.read((char*)&_height, 4);

		if (_width == 0 || _height == 0){
            std::cout << "[BMP ERROR] The width and (or) height have to be non-zero" << std::endl;
            return;
		}

		file.ignore(2); //always 1 apparently

        int bitCount = 0;
        file.read((char*)&bitCount, 2);

        if (bitCount != 24){
            std::cout << "[BMP ERROR] Only BitCount = 24 is supported" << std::endl;
            return;
		}

        int compression = 0;
        file.read((char*)&compression, 4);

        if (compression != 0){
            std::cout << "[BMP ERROR] Only Compression = 0 is supported" << std::endl;
            return;
        }

        file.ignore(20);

        //testing if i reached raster
        char tempData = 0;

        for (int i = 0; i < (_width * _height) * 3; i++){
            file.read(&tempData, 1);
            _data.push_back(tempData);
        }


	}catch(std::ifstream::failure& e){
        perror("[BMP ERROR] Failed to process file: ");
        return;
    }

    _readable = true;
}

/*USAGE: Return pointer to the data of internal vector.
 * Or nullptr if the bitmap is unreadable (either uninitialized or error had happened while parsing)*/

void Bitmap::GetSize(int* width, int* height){
    *width  = _width;
    *height = _height;
}

void* Bitmap::GetData(){
    if (!_readable)
        return nullptr;
    //If this causes segfault, either it is my fault or you have skill issues
    return _data.data();
}


Bitmap::~Bitmap()
{
    //dtor
}

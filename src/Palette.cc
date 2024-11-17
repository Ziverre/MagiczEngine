#include "Palette.h"

Palette::Palette()
{
    //ctor
    _loaded = false;
    _tex_id = 0;
}

bool Palette::Load(std::string fileName){

    bool read = _ReadFile(fileName);

    if (!read){
        std::cout << "Something went wrong" << std::endl;
        return false;
    }

    _Generate_GL_Texture();
    //std::cout << _tex_id << std::endl;

    return false;
}

void Palette::Use(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _tex_id);
}

//------------------------------------------------------

void Palette::_Generate_GL_Texture(){

    glGenTextures(1, &_tex_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 1, 0, GL_BGRA, GL_UNSIGNED_BYTE, _data);
}

bool Palette::_ReadFile(std::string fileName){
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    //fuck the performance, of course (TO DO: ALSO optimize this shit)
    try{
    	file.open(fileName, std::ios::in| std::ios::binary);

		char signature[2] = {0, 0};

		file.read(signature, 2);

		if (signature[0] != 0x42 || signature[1] != 0x4D){
            std::cout << "[BMP ERROR] Invalid BMP signature" << std::endl;
            return false;
		}

		file.ignore(12);

		int headerSize = 0;
		file.read((char*)&headerSize, 4);

		if (headerSize != 40){
            std::cout << "[BMP ERROR] Only BITMAPINFOHEADER = 40 is supported" << std::endl;
            return false;
		}

		//width/height ain't no matter here
		file.ignore(10);

        int bitCount = 0;
        file.read((char*)&bitCount, 2);

        if (bitCount != 8){
            std::cout << "[BMP ERROR] Only BitCount = 8 is supported" << std::endl;
            return false;
		}

        int compression = 0;
        file.read((char*)&compression, 4);

        if (compression != 0){
            std::cout << "[BMP ERROR] Only Compression = 0 is supported" << std::endl;
            return false;
        }

        file.ignore(20);

        //testing if i reached raster
        char tempData = 0;

        for (int i = 0; i < (256 * 4); i++){
            file.read(&tempData, 1);
            _data[i] = tempData;
        }


	}catch(std::ifstream::failure& e){
        perror("[BMP ERROR] Failed to process file: ");
        return false;
    }

    return true;
}

Palette::~Palette()
{
    //dtor
}

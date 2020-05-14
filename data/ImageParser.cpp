//
// Created by Daniil on 12.05.2020.
//

#include <fstream>
#include <iostream>
#include "ImageParser.h"

#include "../lib/byteswap.h"

ImageParser::ImageParser(std::string file_name) : file_name(std::move(file_name)) {}

std::vector<float **> ImageParser::getImages() {
    std::vector<float **> result;

    auto file = std::ifstream(file_name, std::ifstream::binary);

    __int32 magic;
    __int32 image_num;
    __int32 row_num;
    __int32 column_num;

    file.read((char *) &magic, sizeof(__int32));
    file.read((char *) &image_num, sizeof(__int32));
    file.read((char *) &row_num, sizeof(__int32));
    file.read((char *) &column_num, sizeof(__int32));

    magic = __bswap_constant_32(magic);
    image_num = __bswap_constant_32(image_num);
    row_num = __bswap_constant_32(row_num);
    column_num = __bswap_constant_32(column_num);

    if (magic != 0x00000803 || row_num != column_num) {
        std::cerr << "Magic number in image file does not match!";
        exit(1);
    }
    length = row_num;

    char* data = new char[image_num * row_num * column_num];
    file.read(data, image_num * row_num * column_num);

    result.reserve(image_num);
    for (int image = 0; image < image_num; ++image) {
        auto** image_data = new float *[row_num];
        for (int row = 0; row < row_num; ++row) {
            image_data[row] = new float[column_num];
            for (int column = 0; column < column_num; ++column) {
                image_data[row][column] = ((data[image * row_num * column_num + row * column_num + column] == 0) ? 0.0f : 1.0f);
            }
        }
        result.push_back(image_data);
    }

    delete[] data;

    file.close();
    return result;
}

unsigned int ImageParser::getLength() const {
    return length;
}

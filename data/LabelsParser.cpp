//
// Created by Daniil on 12.05.2020.
//

#include "LabelsParser.h"

#include <fstream>
#include <iostream>
#include "../lib/byteswap.h"

LabelsParser::LabelsParser(std::string file_name) : file_name(std::move(file_name)) {}

std::vector<unsigned char> LabelsParser::getLabels() {
    std::vector<unsigned char> result;

    std::ifstream file(file_name, std::ifstream::binary);

    __int32 magic;
    __int32 item_num;

    file.read((char *) &magic, sizeof(__int32));
    file.read((char *) &item_num, sizeof(__int32));
    magic = __bswap_constant_32(magic);
    item_num = __bswap_constant_32(item_num);
    if (magic != 0x00000801) {
        std::cerr << "Magic number in label file does not match!";
        exit(1);
    }

    auto* labels = new unsigned char[item_num];
    file.read((char *)(labels), item_num);

    result.reserve(item_num);
    for (int i = 0; i < item_num; ++i) {
        result.push_back(labels[i]);
    }

    delete [] labels;
    file.close();
    return result;
}

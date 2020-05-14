//
// Created by Daniil on 12.05.2020.
//

#include <iostream>
#include "LabeledImage.h"


LabeledImage::LabeledImage(float **data, unsigned int length, unsigned char label) : data(data), length(length), label(label) {}

float **LabeledImage::getData() const {
    return data;
}

unsigned int LabeledImage::getLength() const {
    return length;
}

unsigned char LabeledImage::getLabel() const {
    return label;
}

void LabeledImage::printImage() const {
    std::cout << "Label:" << (int) label << std::endl;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

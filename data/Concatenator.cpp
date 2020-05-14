//
// Created by Daniil on 12.05.2020.
//

#include <iostream>
#include "Concatenator.h"

std::vector<LabeledImage>
Concatenator::concat(const std::vector<float **> &data, unsigned int length, const std::vector<unsigned char> &labels) {
    if (data.size() != labels.size()) {
        std::cerr << "Data and labels sizes does not match!";
        exit(1);
    }
    std::vector<LabeledImage> result;
    size_t size = data.size();
    result.reserve(size);

    for (int i = 0; i < size; ++i) {
        result.emplace_back(data[i], length, labels[i]);
    }

    return result;
}

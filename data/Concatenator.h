//
// Created by Daniil on 12.05.2020.
//

#ifndef NEOPERCEPTRON_CONCATENATOR_H
#define NEOPERCEPTRON_CONCATENATOR_H


#include <vector>
#include <string>
#include "LabeledImage.h"

class Concatenator {
public:
    Concatenator() = delete;
    static std::vector<LabeledImage> concat(const std::vector<float **> &data, unsigned length, const std::vector<unsigned char> &labels);
};


#endif //NEOPERCEPTRON_CONCATENATOR_H

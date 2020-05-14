//
// Created by Daniil on 12.05.2020.
//

#ifndef NEOPERCEPTRON_LABELEDIMAGE_H
#define NEOPERCEPTRON_LABELEDIMAGE_H


#include <string>

class LabeledImage {
private:
    unsigned char label;
    float **data;
    unsigned length;
public:
    [[nodiscard]] unsigned char getLabel() const;
    [[nodiscard]] float **getData() const;
    [[nodiscard]] unsigned int getLength() const;

    void printImage() const;

    LabeledImage(float **data, unsigned length, unsigned char label);
};


#endif //NEOPERCEPTRON_LABELEDIMAGE_H

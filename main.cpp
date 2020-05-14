#include <iostream>
#include "data/LabelsParser.h"
#include "data/ImageParser.h"
#include "data/Concatenator.h"
#include "nodes/SLayer.h"

int main() {
    LabelsParser labelsParser("train-labels.idx1-ubyte");
    ImageParser imageParser("train-images.idx3-ubyte");

    auto rawImages = imageParser.getImages();
    auto length = imageParser.getLength();
    auto rawLabels = labelsParser.getLabels();
    auto images = Concatenator::concat(rawImages, length, rawLabels);

    images[0].printImage();
    SLayer s_layer(100);

    for (int i = 0; i < 100; ++i) {
        s_layer.train(std::vector<float**>{images[0].getData()}, images[0].getLength());
    }
    s_layer.print();
    return 0;
}

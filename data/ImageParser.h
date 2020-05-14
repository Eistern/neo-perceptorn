//
// Created by Daniil on 12.05.2020.
//

#ifndef NEOPERCEPTRON_IMAGEPARSER_H
#define NEOPERCEPTRON_IMAGEPARSER_H


#include <string>
#include <vector>

class ImageParser {
private:
    std::string file_name;
    unsigned length = 0;
public:
    std::vector<float **> getImages();
    [[nodiscard]] unsigned int getLength() const;

    explicit ImageParser(std::string  file_name);
};


#endif //NEOPERCEPTRON_IMAGEPARSER_H

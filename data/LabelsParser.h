//
// Created by Daniil on 12.05.2020.
//

#ifndef NEOPERCEPTRON_LABELSPARSER_H
#define NEOPERCEPTRON_LABELSPARSER_H


#include <string>
#include <vector>

class LabelsParser {
private:
    std::string file_name;
public:
    std::vector<unsigned char> getLabels();
    explicit LabelsParser(std::string file_name);
};


#endif //NEOPERCEPTRON_LABELSPARSER_H

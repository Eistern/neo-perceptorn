cmake_minimum_required(VERSION 3.16)
project(neoperceptron)

set(CMAKE_CXX_STANDARD 17)

add_executable(neoperceptron main.cpp nodes/SLayer.cpp nodes/SLayer.h nodes/SPane.cpp nodes/SPane.h Utils.h nodes/VNode.cpp nodes/VNode.h data/LabelsParser.cpp data/LabelsParser.h data/ImageParser.cpp data/ImageParser.h data/LabeledImage.cpp data/LabeledImage.h data/Concatenator.cpp data/Concatenator.h)
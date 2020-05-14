//
// Created by Daniil on 10.05.2020.
//

#ifndef NEOPERCEPTRON_SPANE_H
#define NEOPERCEPTRON_SPANE_H

#include <random>
#include "VNode.h"

class SPane {
private:
    static std::random_device random_distribution;
    static std::mt19937 generator;
    static std::uniform_real_distribution<float> real_distribution;
    static float activation_fun(float input);
    const static float SENSITIVITY;

    bool v_check = false;
    int radius;
    float **weights_a = nullptr;
    float weight_b;
    std::vector<std::pair<int, int>> empty_tiles;
    const VNode *connected_v_node;

    [[nodiscard]] float single_compute(const std::vector<float **> &input, unsigned length, int base_vector_y, int base_vector_x);
public:
    [[nodiscard]] const std::vector<std::pair<int, int>> &getEmptyTiles() const;
    [[nodiscard]] float **compute(const std::vector<float **> &input, unsigned length);
    void train_pane(const std::vector<float **> &input, unsigned length, int base_y, int base_x, float edu_speed);
    void print_result() const;

    explicit SPane(const VNode *connected_v_node, unsigned int radius = 2u);
};


#endif //NEOPERCEPTRON_SPANE_H

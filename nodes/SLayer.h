//
// Created by Daniil on 10.05.2020.
//

#ifndef NEOPERCEPTRON_SLAYER_H
#define NEOPERCEPTRON_SLAYER_H


#include <vector>
#include "SPane.h"

class SLayer {
private:
    std::vector<float **> prev_results = std::vector<float **>();
    std::vector<SPane> feature_panes = std::vector<SPane>();
    VNode panes_v_node;
    float education_speed;
    [[nodiscard]] bool vCheckTileIsEmpty(int base_y, int base_x) const;
public:
    bool train(const std::vector<float **>& input, unsigned length);
    std::vector<float **> compute_layer(const std::vector<float **>& input, unsigned length);
    void print() const;

    explicit SLayer(float education_speed);
};


#endif //NEOPERCEPTRON_SLAYER_H

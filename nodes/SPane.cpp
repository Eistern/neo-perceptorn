//
// Created by Daniil on 10.05.2020.
//
#include <algorithm>
#include <iostream>
#include "SPane.h"
#include "../Utils.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

std::random_device SPane::random_distribution;
std::mt19937 SPane::generator(random_distribution());
std::uniform_real_distribution<float> SPane::real_distribution(0.0f, 0.08f);

const float SPane::SENSITIVITY = 0.1f;

SPane::SPane(const VNode *connected_v_node, unsigned int radius) {
    this->connected_v_node = connected_v_node;
    this->radius = radius;
    this->weight_b = 0.0f;
    this->weights_a = (float **) malloc(sizeof(float *) * radius);

    for (int i = 0; i < radius * 2 + 1; ++i) {
        this->weights_a[i] = (float *) malloc(sizeof(float) * (radius * 2 + 1));

        for (int j = 0; j < radius * 2 + 1; ++j) {
            this->weights_a[i][j] = real_distribution(generator);
        }
    }
}

float
SPane::single_compute(const std::vector<float **> &input, unsigned length, int base_vector_y, int base_vector_x) {
    float result = 1.0f;
    float v_result = 0.0f;

    for (const auto &input_layer : input) {
        for (int add_vector_y = -1 * (int) this->radius; add_vector_y <= this->radius; ++add_vector_y) {
            for (int add_vector_x = -1 * (int) this->radius; add_vector_x <= this->radius; ++add_vector_x) {
                //Computing S neuron
                float input_value = Utils::get_2d_input_safe(input_layer, base_vector_x + add_vector_x, base_vector_y + add_vector_y, length);
                float interconnection = input_value;
                interconnection *= this->weights_a[add_vector_y + this->radius][add_vector_x + this->radius];
                result += interconnection;

                //Computing V neuron
                v_result = input_value * input_value * this->connected_v_node->get_weight(add_vector_x, add_vector_y,
                                                                                          this->radius);
            }
        }
    }

    v_result = std::sqrt(v_result);
    v_check = (v_result == 0.0f);

    v_result *= this->weight_b;
    v_result *= SENSITIVITY;
    v_result += 1;

    result /= v_result;
    result -= 1.0f;

    result = SPane::activation_fun(result);

    result *= SENSITIVITY / (1.0f - SENSITIVITY);

    return result;
}

float **SPane::compute(const std::vector<float **> &input, const unsigned length) {
    empty_tiles.clear();
    auto **result = (float **) malloc(sizeof(float *) * length);
    //Compute results of the whole cell-pane
    for (int base_vector_y = 0; base_vector_y < length; ++base_vector_y) {
        result[base_vector_y] = (float *) malloc(sizeof(float) * length);
        for (int base_vector_x = 0; base_vector_x < length; ++base_vector_x) {
            //Computing as the single cell
            v_check = false;
            result[base_vector_y][base_vector_x] = this->single_compute(input, length, base_vector_y, base_vector_x);
            if (v_check)
                empty_tiles.emplace_back(base_vector_y, base_vector_x);
        }
    }

    return result;
}

void SPane::train_pane(const std::vector<float **> &input, unsigned length, int base_y, int base_x, float edu_speed) {
    float v_result = 0.0f;

    for (const auto &input_layer : input) {
        for (int add_vector_y = -1 * (int) this->radius; add_vector_y <= this->radius; ++add_vector_y) {
            for (int add_vector_x = -1 * (int) this->radius; add_vector_x <= this->radius; ++add_vector_x) {
                //Computing S neuron
                float input_value = Utils::get_2d_input_safe(input_layer, base_x + add_vector_x, base_y + add_vector_y, length);
                float interconnection = input_value;
                interconnection *= this->connected_v_node->get_weight(add_vector_x, add_vector_y, this->radius);
                this->weights_a[add_vector_y + this->radius][add_vector_x + this->radius] += interconnection * edu_speed;

                //Computing V neuron
                v_result = input_value * input_value * this->connected_v_node->get_weight(add_vector_x, add_vector_y,
                                                                                          this->radius);
            }
        }
    }

    weight_b += v_result * edu_speed;
}

float SPane::activation_fun(const float input) {
    return input > 0.0f ? input : 0.0f;
}

void SPane::print_result() const {
    std::cout << "Pane weights" << std::endl;
    for (int i = 0; i < radius * 2 + 1; ++i) {
        for (int j = 0; j < radius * 2 + 1; ++j) {
            std::cout << (this->weights_a[i][j] < 1 ? 0 : 1) << " ";
        }
        std::cout << std::endl;
    }
}

const std::vector<std::pair<int, int>> &SPane::getEmptyTiles() const {
    return empty_tiles;
}

#pragma clang diagnostic pop
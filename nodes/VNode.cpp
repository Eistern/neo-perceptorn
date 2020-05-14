//
// Created by Daniil on 10.05.2020.
//

#include "VNode.h"

#include <cmath>

const float VNode::sigma = 5.0f;

VNode::VNode() {
    for (int i = 0; i < RADIUS * 2 + 1; ++i) {
        for (int j = 0; j < RADIUS * 2 + 1; ++j) {
            weights[i][j] = generate_weight(j - RADIUS, i - RADIUS);
        }
    }
}

float VNode::get_weight(int x, int y, unsigned int radius) const {
    if (x + radius > RADIUS * 2 + 1 || y + radius > RADIUS * 2 + 1 || x + radius < 0 || y + radius < 0)
        return generate_weight(x, y);
    else
        return weights[y][x];
}

float VNode::generate_weight(int x, int y) {
    return 1.0f/(M_PI * sigma) * (1.0f - 0.5f * (x * x + y * y) / sigma) * std::exp(-0.5f * (x * x + y * y) / sigma);
}

//
// Created by Daniil on 10.05.2020.
//

#include "SLayer.h"
#include "../Utils.h"
#include <map>
#include <algorithm>

bool SLayer::train(const std::vector<float **>& input, const unsigned length) {
    bool result = false;
    compute_layer(input, length);

    std::map<int, std::vector<std::pair<int, int>>> candidates;

    for (int base_y = 0; base_y < length; ++base_y) {
        for (int base_x = 0; base_x < length; ++base_x) {
            float max = 0.0f;
            int layer_num = -1;
            for (int layer = 0; layer < prev_results.size(); ++layer) {
                if (max < prev_results[layer][base_y][base_x]) {
                    layer_num = layer;
                    max = prev_results[layer][base_y][base_x];
                }
            }

            if (layer_num == -1 && !vCheckTileIsEmpty(base_y, base_x)) {
                result = true;
            }
        }
    }

    if (result) {
        auto new_pane = SPane(&panes_v_node);
        prev_results.push_back(new_pane.compute(input, length));
        feature_panes.emplace_back(new_pane);
    }

    for (int base_y = 0; base_y < length; ++base_y) {
        for (int base_x = 0; base_x < length; ++base_x) {
            float max = 0.0f;
            int layer_num = -1;
            for (int layer = 0; layer < prev_results.size(); ++layer) {
                if (max < prev_results[layer][base_y][base_x]) {
                    layer_num = layer;
                    max = prev_results[layer][base_y][base_x];
                }
            }

            if (layer_num == -1 && !vCheckTileIsEmpty(base_y, base_x)) {
                candidates[layer_num].push_back(std::pair<int, int>(base_y, base_x));
            }
        }
    }


    for (const auto& layer_candidates : candidates) {
        int layer_num = layer_candidates.first;
        float max = 0.0f;
        int max_candidate_y = -1;
        int max_candidate_x = -1;
        for (const auto& layer_candidate : layer_candidates.second) {
            if (prev_results[layer_num][layer_candidate.first][layer_candidate.second] > max) {
                max = prev_results[layer_num][layer_candidate.first][layer_candidate.second];
                max_candidate_y = layer_candidate.first;
                max_candidate_x = layer_candidate.second;
            }
        }
        if (max_candidate_y != -1 && max_candidate_x != -1)
            feature_panes[layer_num].train_pane(input, length, max_candidate_y, max_candidate_x, education_speed);
    }

    return result;
}

std::vector<float **> SLayer::compute_layer(const std::vector<float **> &input, const unsigned int length) {
    for (float** result : prev_results) {
        Utils::remove_2d_float(result, length);
    }
    prev_results.clear();
    for (auto& feature_pane : feature_panes) {
        prev_results.push_back(feature_pane.compute(input, length));
    }

    return prev_results;
}

SLayer::SLayer(float education_speed) : education_speed(education_speed) {}

void SLayer::print() const {
    for (const auto &pane : feature_panes) {
        pane.print_result();
    }
}

bool SLayer::vCheckTileIsEmpty(int base_y, int base_x) const {
    std::pair<int, int> check(base_y, base_x);
    for (const auto &pane : feature_panes) {
        auto tiles = pane.getEmptyTiles();
        if (std::find(tiles.begin(), tiles.end(), check) != tiles.end())
            return true;
    }
    return false;
}

//
// Created by Daniil on 10.05.2020.
//

#ifndef NEOPERCEPTRON_UTILS_H
#define NEOPERCEPTRON_UTILS_H


#include <cstdlib>

class Utils {
public:
    Utils() = delete;
    static void remove_2d_float(float **src, unsigned length) {
        for (int i = 0; i < length; ++i) {
            free(src[i]);
        }
        free(src);
    }
    static float get_2d_input_safe(float **src, int x, int y, unsigned length) {
        if (x < 0 || y < 0) {
            return 0.0f;
        }

        if (x >= length || y >= length) {
            return 0.0f;
        }

        return src[y][x];
    }
};


#endif //NEOPERCEPTRON_UTILS_H

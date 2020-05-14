//
// Created by Daniil on 10.05.2020.
//

#ifndef NEOPERCEPTRON_VNODE_H
#define NEOPERCEPTRON_VNODE_H

#define RADIUS 2

class VNode {
private:
    static const float sigma;
    float weights[RADIUS * 2 + 1][RADIUS * 2 + 1];
    static float generate_weight(int x, int y) ;
public:
    [[nodiscard]] float get_weight(int x, int y, unsigned radius) const;

    explicit VNode();
};


#endif //NEOPERCEPTRON_VNODE_H

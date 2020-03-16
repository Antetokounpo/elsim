#pragma once

#include "circuit.hpp"

class UIMath
{
    public:
        static float distance_between_nodes(Node a, Node b);
        static float angle_between_nodes(Node a, Node b);
        static bool check_collision(Node n, int x, int y);
    private:
        UIMath() {} // Static class
};

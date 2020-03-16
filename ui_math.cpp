#include "ui_math.hpp"

#include<cmath>

float UIMath::distance_between_nodes(Node a, Node b)
{
    return std::sqrt(std::pow(a.y - b.y, 2) + std::pow(a.x - b.x, 2));
}

float UIMath::angle_between_nodes(Node a, Node b)
{
    return -std::atan2(b.y - a.y, b.x - a.x) * 180 / M_PI; // Le signe négatif est parce que l'axe y est inversé
}

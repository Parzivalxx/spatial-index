#pragma once
#include "Point.h"

struct KDNode {
    Point point;
    int dimension;
    KDNode* left;
    KDNode* right;

    KDNode(Point _point, int _dimension) : point(_point), dimension(_dimension), left(nullptr), right(nullptr) {};
};

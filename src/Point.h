#pragma once
#include "QuadtreeNode.h"

struct Point {
    double x;
    double y;
    Point(double _x, double _y);
    double euclideanDistance(double x1, double y1) const;
    double minDistToPoint(const Point& otherPoint) const;
    double minDistToNode(const QuadtreeNode& node) const;
};

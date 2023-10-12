#pragma once
#include "Point.h"
#include <vector>

class SpatialIndex {
public:
    virtual ~SpatialIndex() {}

    virtual void build(std::vector<Point>& points) = 0;
    virtual std::vector<Point> rangeQuery(double startX, double startY, double endX, double endY) const = 0;
    virtual std::vector<Point> knnQuery(double queryX, double queryY, int k) const = 0;
    virtual void deletePoint(const Point& point) = 0;
};

#pragma once

#include <vector>
#include "Point.h"
#include "SpatialIndex.h"

class BruteForce : public SpatialIndex {
public:
    BruteForce();

    void build(std::vector<Point>& points);

    std::vector<Point> rangeQuery(double startX, double startY, double endX, double endY) const;
    std::vector<Point> knnQuery(double queryX, double queryY, int k) const;
    void deletePoint(const Point& point);
    void clear();

private:
    std::vector<Point> data_;
};

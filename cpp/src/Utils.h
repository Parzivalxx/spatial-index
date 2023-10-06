#pragma once
#include <iostream>
#include <vector>
#include "Point.h"

// Function to generate synthetic 2D point cloud data
std::vector<Point> generateSyntheticData(int numPoints, double xMin, double xMax, double yMin, double yMax) {
    std::vector<Point> data;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < numPoints; ++i) {
        double x = (static_cast<double>(std::rand()) / RAND_MAX) * (xMax - xMin) + xMin;
        double y = (static_cast<double>(std::rand()) / RAND_MAX) * (yMax - yMin) + yMin;
        data.push_back(Point(x, y));
    }

    return data;
}

#pragma once
#include <iostream>
#include <vector>
#include "Point.h"
#include <typeinfo>
#include <cmath>
#include <random>
#include <chrono>

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

void measureQueryTimeAndPrint(const std::string& queryType, SpatialIndex& index, const std::vector<Point>& data, int numQueries,
    double minX, double minY, double maxX, double maxY, int numNearestNeighbours, std::vector<Point> syntheticData) {
    std::default_random_engine rng;
    std::uniform_real_distribution<double> queryXDist(minX, maxX);
    std::uniform_real_distribution<double> queryYDist(minY, maxY);
    std::chrono::duration<double> queryTime(0);

    if (queryType == "build") {
        auto start = std::chrono::high_resolution_clock::now();
        index.build(syntheticData);
        auto end = std::chrono::high_resolution_clock::now();
        queryTime += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
    }
    else {
        for (int i = 0; i < numQueries; ++i) {
            double startX = queryXDist(rng);
            double startY = queryYDist(rng);
            double endX = queryXDist(rng);
            double endY = queryYDist(rng);

            auto start = std::chrono::high_resolution_clock::now();

            if (queryType == "range") {
                std::vector<Point> result = index.rangeQuery(startX, startY, endX, endY);
            }
            else if (queryType == "knn") {
                std::vector<Point> result = index.knnQuery(startX, startY, numNearestNeighbours);
            }
            else if (queryType == "delete") {
                Point pointToDelete(startX, startY);
                index.deletePoint(pointToDelete);
            }

            auto end = std::chrono::high_resolution_clock::now();
            queryTime += std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        }
    }

    queryTime /= numQueries;
    const std::type_info& typeInfo = typeid(index);
    double microSeconds = queryTime.count() * std::pow(10, 6);
    std::string typeName = typeInfo.name();
    std::cout << "Average Time for " << typeName << " " << queryType << " Queries: " << microSeconds << " microseconds" << std::endl;
}

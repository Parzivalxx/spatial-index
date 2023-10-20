#pragma once
#include <iostream>
#include <vector>
#include "Point.h"
#include <typeinfo>
#include <cmath>
#include <random>
#include <chrono>

std::vector<Point> generateUniformData(int numPoints, double xMin, double xMax, double yMin, double yMax) {
    std::vector<Point> data;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (int i = 0; i < numPoints; ++i) {
        double x = (static_cast<double>(std::rand()) / RAND_MAX) * (xMax - xMin) + xMin;
        double y = (static_cast<double>(std::rand()) / RAND_MAX) * (yMax - yMin) + yMin;
        data.push_back(Point(x, y));
    }

    return data;
}

std::vector<Point> generateNonUniformData(int numPoints, double xMin, double xMax, double yMin, double yMax) {
    std::vector<Point> data;
    std::default_random_engine generator;

    std::normal_distribution<double> xDistribution((xMax - xMin) / 2.0, (xMax - xMin) / 100.0);
    std::normal_distribution<double> yDistribution((yMax - yMin) / 2.0, (yMax - yMin) / 100.0);

    for (int i = 0; i < numPoints; ++i) {
        double x = xDistribution(generator);
        double y = yDistribution(generator);

        x = std::max(xMin, std::min(xMax, x));
        y = std::max(yMin, std::min(yMax, y));

        data.push_back(Point(x, y));
    }

    return data;
}

void measureQueryTimeAndPrint(const std::string& queryType, SpatialIndex& index, int numQueries,
    double minX, double minY, double maxX, double maxY, int numNearestNeighbours, std::vector<Point> syntheticData, bool querySmallArea, double maxArea = 50.0) {
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
            double startX, startY, endX, endY, width, height;
            if (!querySmallArea) {
                startX = queryXDist(rng);
                startY = queryYDist(rng);
                endX = queryXDist(rng);
                endY = queryYDist(rng);
                if (endX < startX) {
                    std::swap(startX, endX);
                }
                if (endY < startY) {
                    std::swap(startY, endY);
                }
            }
            else {
                width = queryXDist(rng);
                height = maxArea / width;

                startX = queryXDist(rng);
                startY = queryYDist(rng);

                endX = std::min(startX + width, maxX);
                endY = std::min(startY + height, maxY);
            }


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
    if (!querySmallArea) {
        std::cout << "Average Time for " << typeName << " " << queryType << " Queries: " << microSeconds << " microseconds (normal)" << std::endl;
    }
    else {
        std::cout << "Average Time for " << typeName << " " << queryType << " Queries: " << microSeconds << " microseconds (small)" << std::endl;
    }
    
}

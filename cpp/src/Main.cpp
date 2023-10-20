#include <vector>
#include <chrono>
#include <random>
#include <cmath>
#include "Point.h"
#include "Quadtree.h"
#include "KDTree.h"
#include "BruteForce.h"
#include "Utils.h"

int main() {
    int numPoints = (int)std::pow(10, 5);
    double xMin = 0.0, xMax = 1000.0;
    double yMin = 0.0, yMax = 1000.0;
    int numQueries = 100;
    int numNearestNeighbours = 10;

    std::vector<Point> uniformData = generateUniformData(numPoints, xMin, xMax, yMin, yMax);
    std::vector<Point> nonUniformData = generateNonUniformData(numPoints, xMin, xMax, yMin, yMax);

    Quadtree quadtree(xMin, yMin, xMax, yMax);
    KDTree kdtree;
    BruteForce bruteForce;

    std::vector<std::string> queryTypes = { "build", "range", "knn", "delete" };

    std::cout << "Uniform data" << std::endl;
    for (const std::string& queryType : queryTypes) {
        measureQueryTimeAndPrint(queryType, quadtree, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, uniformData, false);
        measureQueryTimeAndPrint(queryType, kdtree, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, uniformData, false);
        measureQueryTimeAndPrint(queryType, bruteForce, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, uniformData, false);
        if (queryType == "range") {
            measureQueryTimeAndPrint(queryType, quadtree, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, uniformData, true);
            measureQueryTimeAndPrint(queryType, kdtree, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, uniformData, true);
            measureQueryTimeAndPrint(queryType, bruteForce, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, uniformData, true);
        }
    }

    quadtree.clear();
    kdtree.clear();
    bruteForce.clear();


    std::cout << "Non-uniform data" << std::endl;
    for (const std::string& queryType : queryTypes) {
        measureQueryTimeAndPrint(queryType, quadtree, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, nonUniformData, false);
        measureQueryTimeAndPrint(queryType, kdtree, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, nonUniformData, false);
        measureQueryTimeAndPrint(queryType, bruteForce, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, nonUniformData, false);
        if (queryType == "range") {
            measureQueryTimeAndPrint(queryType, quadtree, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, nonUniformData, true);
            measureQueryTimeAndPrint(queryType, kdtree, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, nonUniformData, true);
            measureQueryTimeAndPrint(queryType, bruteForce, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, nonUniformData, true);
        }
    }

    return 0;
}

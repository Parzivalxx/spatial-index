#include <vector>
#include <chrono>
#include <random>
#include "Point.h"
#include "Quadtree.h"
#include "KDTree.h"
#include "BruteForce.h"
#include "Utils.h"

int main() {
    int numPoints = 1000;
    double xMin = 0.0, xMax = 100.0;
    double yMin = 0.0, yMax = 100.0;
    int numQueries = 1000;
    int numNearestNeighbours = 5;

    std::vector<Point> syntheticData = generateSyntheticData(numPoints, xMin, xMax, yMin, yMax);

    Quadtree quadtree(xMin, yMin, xMax, yMax);
    KDTree kdtree;
    BruteForce bruteForce;

    std::vector<std::string> queryTypes = { "build", "range", "knn", "delete" };

    for (const std::string& queryType : queryTypes) {
        measureQueryTimeAndPrint(queryType, quadtree, syntheticData, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, syntheticData);
        measureQueryTimeAndPrint(queryType, kdtree, syntheticData, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, syntheticData);
        measureQueryTimeAndPrint(queryType, bruteForce, syntheticData, numQueries, xMin, yMin, xMax, yMax, numNearestNeighbours, syntheticData);
    }

    return 0;
}

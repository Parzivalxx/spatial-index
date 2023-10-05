#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Point.h"
#include "Quadtree.h"
#include "KDTree.h"

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

int main() {
    int numPoints = 1000;
    double xMin = 0.0;
    double xMax = 100.0;
    double yMin = 0.0;
    double yMax = 100.0;

    std::vector<Point> syntheticData = generateSyntheticData(numPoints, xMin, xMax, yMin, yMax);

    std::ofstream outFile("synthetic_data.txt");
    if (outFile.is_open()) {
        for (const Point& point : syntheticData) {
            outFile << point.x << " " << point.y << "\n";
        }
        outFile.close();
    }
    else {
        std::cerr << "Unable to open the output file." << std::endl;
        return 1;
    }

    // Create and populate the Quadtree
    Quadtree quadtree(xMin, yMin, xMax, yMax);
    for (const Point& point : syntheticData) {
        quadtree.insert(point);
    }

    // Create and populate the KD-tree
    KDTree kdtree;
    kdtree.build(syntheticData);

    // Define the query rectangle for range query
    double startX = 0.0, startY = 0.0, endX = 10.0, endY = 10.0;

    // Perform range query on Quadtree
    std::vector<Point> quadtreeRangeResult = quadtree.rangeQuery(startX, startY, endX, endY);

    // Perform range query on KD-tree
    std::vector<Point> kdtreeRangeResult = kdtree.rangeQuery(startX, startY, endX, endY);

    // Compare and print the results of the range query
    std::cout << "Range Query Results:" << std::endl;
    for (const Point& point : quadtreeRangeResult) {
        std::cout << "Quadtree Result: (" << point.x << ", " << point.y << ")\n";
    }
    for (const Point& point : kdtreeRangeResult) {
        std::cout << "KD-tree Result: (" << point.x << ", " << point.y << ")\n";
    }

    // Define the query point and k for KNN query
    int queryX = 5, queryY = 5, k = 5;

    // Perform KNN query on Quadtree
    std::vector<Point> quadtreeKnnResult = quadtree.knnQuery(queryX, queryY, k);

    // Perform KNN query on KD-tree
    std::vector<Point> kdtreeKnnResult = kdtree.kNearestNeighbors(queryX, queryY, k);

    // Compare and print the results of the KNN query
    std::cout << "KNN Query Results:" << std::endl;
    for (const Point& point : quadtreeKnnResult) {
        std::cout << "Quadtree Result: (" << point.x << ", " << point.y << ")\n";
    }
    for (const Point& point : kdtreeKnnResult) {
        std::cout << "KD-tree Result: (" << point.x << ", " << point.y << ")\n";
    }

    return 0;
}

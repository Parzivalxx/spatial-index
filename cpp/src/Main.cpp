#include <vector>
#include "Point.h"
#include "Quadtree.h"
#include "KDTree.h"
#include "BruteForce.h"
#include "Utils.h"

int main() {
    int numPoints = 1000;
    double xMin = 0.0;
    double xMax = 100.0;
    double yMin = 0.0;
    double yMax = 100.0;

    std::vector<Point> syntheticData = generateSyntheticData(numPoints, xMin, xMax, yMin, yMax);

    // Create and populate the Quadtree
    Quadtree quadtree(xMin, yMin, xMax, yMax);
    quadtree.build(syntheticData);

    // Create and populate the KD-tree
    KDTree kdtree;
    kdtree.build(syntheticData);

    // Create BruteForce object
    BruteForce bruteForce(syntheticData);

    // Define the query rectangle for range query
    double startX = 0.0, startY = 0.0, endX = 10.0, endY = 10.0;

    // Perform range query on Quadtree
    std::vector<Point> quadtreeRangeResult = quadtree.rangeQuery(startX, startY, endX, endY);

    // Perform range query on KD-tree
    std::vector<Point> kdtreeRangeResult = kdtree.rangeQuery(startX, startY, endX, endY);

    // Perform range query with brute force
    std::vector<Point> bruteForceRangeResult = bruteForce.rangeQuery(startX, startY, endX, endY);

    // Compare and print the results of the range query
    std::cout << "Range Query Results:" << std::endl;
    for (const Point& point : quadtreeRangeResult) {
        std::cout << "Quadtree Result: (" << point.x << ", " << point.y << ")\n";
    }
    for (const Point& point : kdtreeRangeResult) {
        std::cout << "KD-tree Result: (" << point.x << ", " << point.y << ")\n";
    }
    for (const Point& point : bruteForceRangeResult) {
        std::cout << "BruteForce Result: (" << point.x << ", " << point.y << ")\n";
    }

    // Define the query point and k for KNN query
    int queryX = 5, queryY = 5, k = 5;

    // Perform KNN query on Quadtree
    std::vector<Point> quadtreeKnnResult = quadtree.knnQuery(queryX, queryY, k);

    // Perform KNN query on KD-tree
    std::vector<Point> kdtreeKnnResult = kdtree.knnQuery(queryX, queryY, k);

    // Perform range query with brute force
    std::vector<Point> bruteForceKnnResult = bruteForce.knnQuery(queryX, queryY, k);

    // Compare and print the results of the KNN query
    std::cout << "KNN Query Results:" << std::endl;
    for (const Point& point : quadtreeKnnResult) {
        std::cout << "Quadtree Result: (" << point.x << ", " << point.y << ")\n";
    }
    for (const Point& point : kdtreeKnnResult) {
        std::cout << "KD-tree Result: (" << point.x << ", " << point.y << ")\n";
    }
    for (const Point& point : bruteForceKnnResult) {
        std::cout << "BruteForce Result: (" << point.x << ", " << point.y << ")\n";
    }

    return 0;
}

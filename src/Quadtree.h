#pragma once
#include "QuadtreeNode.h" // Include the header for QuadtreeNode
#include <vector>
#include <queue>

class Quadtree {
public:
    Quadtree(double xmin, double ymin, double xmax, double ymax);
    ~Quadtree(); // Destructor to deallocate memory
    void insert(const Point& point);
    std::vector<Point> rangeQuery(double startX, double startY, double endX, double endY) const;
    // Function to perform KNN query in the entire quadtree
    std::vector<Point> knnQuery(const Point& queryPoint, int k);

private:
    QuadtreeNode* root;
    void knnSearch(QuadtreeNode* currentNode, const Point& queryPoint, int k,
        std::priority_queue<std::pair<double, Point>>& nearestNeighbors);
    void destroyTree(QuadtreeNode* node);
};

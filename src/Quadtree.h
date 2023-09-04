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
    std::vector<Point> knnQuery(int x, int y, int k) const;

private:
    QuadtreeNode* root;
    struct Element;
    void knnSearch(const Point& queryPoint, int k,
        std::priority_queue<Element, std::vector<Element>, std::greater<Element>> priorityQueue, std::vector<Point>& nearestNeighbors) const;
    void destroyTree(QuadtreeNode* node);
};

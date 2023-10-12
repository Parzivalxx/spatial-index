#pragma once
#include <iostream>
#include "QuadtreeNode.h"
#include "Point.h"
#include "SpatialIndex.h"
#include <vector>
#include <queue>

class Quadtree : public SpatialIndex {
public:
    Quadtree(double xmin, double ymin, double xmax, double ymax);
    ~Quadtree();
    void build(std::vector<Point>& points);
    std::vector<Point> rangeQuery(double startX, double startY, double endX, double endY) const;
    std::vector<Point> knnQuery(double x, double y, int k) const;
    void deletePoint(const Point& point);

private:
    QuadtreeNode* root;
    struct Element;
    void knnSearch(const Point& queryPoint, int k,
        std::priority_queue<Element, std::vector<Element>, std::greater<Element>> priorityQueue, std::vector<Point>& nearestNeighbors) const;
    void destroyTree(QuadtreeNode* node);
    void deletePoint(QuadtreeNode* currentNode, const Point& point);
};

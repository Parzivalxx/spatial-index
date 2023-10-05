#pragma once
#include "Point.h"
#include "KDNode.h"
#include "KDNodeComparator.h"
#include <vector>
#include <queue>

class KDTree {
public:
    KDTree();
    ~KDTree();

    void build(std::vector<Point>& points);
    std::vector<Point> rangeQuery(double startX, double startY, double endX, double endY);
    std::vector<Point> kNearestNeighbors(double queryX, double queryY, int k);

private:
    KDNode* root;

    // Private helper functions for building and querying
    KDNode* buildTree(std::vector<Point> points, int depth);
    void rangeQuery(KDNode* node, double startX, double startY, double endX, double endY, int depth, std::vector<Point>& result);
    void kNearestNeighbors(KDNode* node, const Point& queryPoint, int k, std::priority_queue<KDNode*, std::vector<KDNode*>, KDNodeComparator>& result);
    void destroyTree(KDNode* node);
};

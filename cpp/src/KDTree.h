#pragma once
#include "Point.h"
#include "KDNode.h"
#include "KDNodeComparator.h"
#include "SpatialIndex.h"
#include <vector>
#include <queue>

class KDTree : public SpatialIndex {
public:
    KDTree();
    ~KDTree();

    void build(std::vector<Point>& points);
    std::vector<Point> rangeQuery(double startX, double startY, double endX, double endY) const;
    std::vector<Point> knnQuery(double queryX, double queryY, int k) const;
    void deletePoint(const Point& point);
    void clear();

private:
    KDNode* root;

    KDNode* buildTree(std::vector<Point> points, int depth);
    void rangeQuery(KDNode* node, double startX, double startY, double endX, double endY, int depth, std::vector<Point>& result) const;
    void kNearestNeighbors(KDNode* node, const Point& queryPoint, int k, std::priority_queue<KDNode*, std::vector<KDNode*>, KDNodeComparator>& result) const;
    void destroyTree(KDNode* node);
    KDNode* findMin(KDNode* node, int dimension);
    KDNode* deletePoint(KDNode* node, const Point& point, int depth);
};

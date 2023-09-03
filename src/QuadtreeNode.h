#pragma once
#include <vector>

struct Point;
class QuadtreeNode {
public:
    QuadtreeNode(double xmin, double ymin, double xmax, double ymax);
    void insert(const Point& point);
    std::vector<Point> rangeQuery(double startX, double startY, double endX, double endY);
    std::vector<Point> knnQuery(const Point& queryPoint, int k);
    bool isLeaf() const;
    bool intersectsRange(double startX, double startY, double endX, double endY) const;
    QuadtreeNode* children[4];

private:
    double xMin;
    double yMin;
    double xMax;
    double yMax;
    static const size_t maxCapacity = 4;
    std::vector<Point> points;

    bool contains(const Point& point);
    void splitNode();
};

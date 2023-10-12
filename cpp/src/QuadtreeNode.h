#pragma once
#include <vector>
#include <iostream>

struct Point;
class QuadtreeNode {
public:
    QuadtreeNode(double xmin, double ymin, double xmax, double ymax);
    void insert(const Point& point);
    std::vector<Point> rangeQuery(double startX, double startY, double endX, double endY);
    bool isLeaf() const;
    bool intersectsRange(double startX, double startY, double endX, double endY) const;
    double getXMin() const;
    double getYMin() const;
    double getXMax() const;
    double getYMax() const;
    std::vector<Point> getPoints() const;
    QuadtreeNode** getChildren();
    bool isEmpty() const;
    void removePoint(const Point& point);
    bool contains(const Point& point);

private:
    double xMin;
    double yMin;
    double xMax;
    double yMax;
    QuadtreeNode* children[4];
    static const std::size_t maxCapacity = 4;
    std::vector<Point> points;
    void splitNode();
};

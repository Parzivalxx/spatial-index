#include <cmath>
#include "Point.h"

Point::Point(double _x, double _y) : x(_x), y(_y) {}

// Member function to find shortest distance to a point given coordinates
double Point::euclideanDistance(double x1, double y1) const {
    double dx = x - x1;
    double dy = y - y1;
    return (dx * dx + dy * dy);
}

double Point::euclideanDistance(const Point otherPoint) const {
    double dx = x - otherPoint.x;
    double dy = y - otherPoint.y;
    return dx * dx + dy * dy;
}

// Member function to calculate Euclidean distance to another point
double Point::minDistToPoint(const Point& otherPoint) const {
    return euclideanDistance(otherPoint.x, otherPoint.y);
}

// Member function to calculate minimum distance between a point and a QuadtreeNode
// Distances are squared as sqrt is unnecessary
double Point::minDistToNode(const QuadtreeNode& node) const {
    double xMin = node.getXMin();
    double yMin = node.getYMin();
    double xMax = node.getXMax();
    double yMax = node.getYMax();
    double dx1 = x - xMin, dx2 = x - xMax;
    double dy1 = y - yMin, dy2 = y - yMax;

    if (dx1 * dx2 < 0) { // x is between minx and maxx
        if (dy1 * dy2 < 0) { // (x,y) is inside the rectangle
            return 0; // return 0 as point is in rect
        }
        return std::min(std::pow(std::abs(dy1), 2), std::pow(std::abs(dy2), 2));
    }
    if (dy1 * dy2 < 0) { // y is between miny and maxy
        // We don't have to test for being inside the rectangle, it's already tested.
        return std::min(std::pow(std::abs(dx1), 2), std::pow(std::abs(dx2), 2));
    }
    return std::min(std::min(euclideanDistance(xMin, yMin), euclideanDistance(xMax, yMax)),
        std::min(euclideanDistance(xMin, yMax), euclideanDistance(xMax, yMin)));
}

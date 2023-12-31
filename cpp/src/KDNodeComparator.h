#pragma once

#include "Point.h"
#include "KDNode.h"

struct KDNodeComparator {
    Point queryPoint;

    KDNodeComparator(Point point) : queryPoint(point) {}

    bool operator()(KDNode* a, KDNode* b) {
        // Compare nodes based on their distances to the query point
        double distanceA = a->point.euclideanDistance(queryPoint);
        double distanceB = b->point.euclideanDistance(queryPoint);
        return distanceA < distanceB;
    }
};

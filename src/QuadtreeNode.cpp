#include "QuadtreeNode.h"
#include "Point.h"

QuadtreeNode::QuadtreeNode(double xmin, double ymin, double xmax, double ymax)
    : xMin(xmin), yMin(ymin), xMax(xmax), yMax(ymax) {
    // Initialize other members if needed
    for (int i = 0; i < 4; ++i) {
        children[i] = nullptr;
    }
    // Initialize the points vector to be empty
    points.clear();
}

// Function to check if a point is within the bounds of the node
bool QuadtreeNode::contains(const Point& point) {
    return (point.x >= xMin && point.x <= xMax && point.y >= yMin && point.y <= yMax);
}

// Function to split a quadtree node into four child nodes
void QuadtreeNode::splitNode() {
    // Calculate the midpoint of the current node's bounding box
    double xMid = (xMin + xMax) / 2.0;
    double yMid = (yMin + yMax) / 2.0;

    // Create four child nodes, each representing a quadrant of the current node
    children[0] = new QuadtreeNode(xMin, yMid, xMid, yMax); // NW
    children[1] = new QuadtreeNode(xMid, yMid, xMax, yMax); // NE
    children[2] = new QuadtreeNode(xMin, yMin, xMid, yMid); // SW
    children[3] = new QuadtreeNode(xMid, yMin, xMax, yMid); // SE

    // Iterate through the points stored in the current node
    // and determine which child node each point belongs to
    std::vector<Point> remainingPoints;
    for (const Point& point : points) {
        bool inserted = false;
        for (int i = 0; i < 4; ++i) {
            if (children[i]->contains(point)) {
                children[i]->insert(point); // Insert the point into the child node
                inserted = true;
                break;
            }
        }
        if (!inserted) {
            // Point doesn't fit in any child node, keep it in the current node
            remainingPoints.push_back(point);
        }
    }

    // Clear the points vector of the current node
    points = remainingPoints;
}

// Function to insert a point into the quadtree node
void QuadtreeNode::insert(const Point& point) {
    // Check if the point is within the bounds of this node
    if (contains(point)) {
        // If this node is a leaf (has no children), add the point to this node
        if (children[0] == nullptr) {
            points.push_back(point);

            // Check if this node has exceeded its capacity
            // If so, split this node
            if (points.size() > maxCapacity) {
                splitNode();
            }
        }
        else {
            // If this node has children, insert the point into the appropriate child
            for (int i = 0; i < 4; ++i) {
                if (children[i]->contains(point)) {
                    children[i]->insert(point);
                    break;
                }
            }
        }
    }
    // If the point is outside the bounds of this node, ignore it (don't insert).
}

bool QuadtreeNode::isLeaf() const {
    // A node is considered a leaf if all of its children are nullptr (i.e., it has no children).
    return children[0] == nullptr && children[1] == nullptr && children[2] == nullptr && children[3] == nullptr;
}

std::vector<Point> QuadtreeNode::rangeQuery(double startX, double startY, double endX, double endY) {
    std::vector<Point> result;

    // Iterate through the points stored in this node
    for (const Point& point : points) {
        if (point.x >= startX && point.x <= endX && point.y >= startY && point.y <= endY) {
            // Point falls within the specified range, add it to the result
            result.push_back(point);
        }
    }

    // If this node has children, recursively query child nodes that intersect with the range
    if (!isLeaf()) {
        for (int i = 0; i < 4; ++i) {
            if (children[i]->intersectsRange(startX, startY, endX, endY)) {
                // Recursively query the child node
                std::vector<Point> childResult = children[i]->rangeQuery(startX, startY, endX, endY);
                // Append child results to the result vector
                result.insert(result.end(), childResult.begin(), childResult.end());
            }
        }
    }

    return result;
}

bool QuadtreeNode::intersectsRange(double startX, double startY, double endX, double endY) const {
    return (xMax >= startX && xMin <= endX && yMax >= startY && yMin <= endY);
}

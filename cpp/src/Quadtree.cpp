#include "Quadtree.h"
#include "QuadtreeNode.h"
#include "Point.h"
#include <limits>

// Element struct used in priorityQueue
struct Quadtree::Element {
    double distance; // Distance to the query point
    bool isNode; // true if it's a node, false if it's a point
    union {
        QuadtreeNode* node; // Pointer to a QuadtreeNode
        Point point;        // A Point
    };

    // Constructor for a node
    Element(double _distance, QuadtreeNode* _node) : distance(_distance), isNode(true), node(_node) {}

    // Constructor for a point
    Element(double _distance, const Point& _point) : distance(_distance), isNode(false), point(_point) {}

    // Comparison operator to sort elements based on distance
    bool operator>(const Element& other) const {
        return distance > other.distance;
    }
};

Quadtree::Quadtree(double xmin, double ymin, double xmax, double ymax) {
    root = new QuadtreeNode(xmin, ymin, xmax, ymax);
}

// Destructor to deallocate memory
// Destructor for the Quadtree class
Quadtree::~Quadtree() {
    // Call a recursive function to delete nodes starting from the root
    destroyTree(root);
}

// Recursive function to delete nodes
void Quadtree::destroyTree(QuadtreeNode* node) {
    if (node != nullptr) {
        // Recursively delete child nodes first
        for (int i = 0; i < 4; ++i) {
            destroyTree(node->getChildren()[i]);
        }
        // Delete the current node
        delete node;
    }
}

// Function to build a quadtree
void Quadtree::build(std::vector<Point>& points) {
    for (const Point& point : points) {
        root->insert(point);
    }
}

// Function for range query
std::vector<Point> Quadtree::rangeQuery(double startX, double startY, double endX, double endY) const {
    std::vector<Point> result;

    // Check if the root node intersects with the specified range
    if (root->intersectsRange(startX, startY, endX, endY)) {
        // If it intersects, perform the range query starting from the root node
        result = root->rangeQuery(startX, startY, endX, endY);
    }

    return result;
}

std::vector<Point> Quadtree::knnQuery(double x, double y, int k) const {
    std::vector<Point> nearestNeighbors;

    // Create a priority queue to store nearest nodes or points
    std::priority_queue<Element, std::vector<Element>, std::greater<Element>> priorityQueue;
    priorityQueue.push(Element(std::numeric_limits<double>::infinity(), root));

    Point queryPoint = Point(x, y);
    // Call a recursive function to perform the KNN query starting from the root node
    knnSearch(queryPoint, k, priorityQueue, nearestNeighbors);

    return nearestNeighbors;
}

void Quadtree::knnSearch(const Point& queryPoint, int k, std::priority_queue<Element, std::vector<Element>, std::greater<Element>> priorityQueue, std::vector<Point>& nearestNeighbors) const {
    if (priorityQueue.empty()) return;

    Element topElement = priorityQueue.top();
    while (!priorityQueue.empty()) {
        topElement = priorityQueue.top();
        priorityQueue.pop();

        // Check if the top element is a point
        if (!topElement.isNode) {
            nearestNeighbors.push_back(topElement.point);

            // Check if we have found k nearest neighbors
            if (nearestNeighbors.size() == k) {
                return;
            }
        }
        else {
            // If the top element is a node, break out of the loop
            break;
        }
    }

    if (!topElement.isNode) {
        return;
    }
    // If the node is a leaf, process the node's points
    QuadtreeNode* node = topElement.node;
    if (node->isLeaf()) {
        for (const Point& point : node->getPoints()) {
            double distance = queryPoint.minDistToPoint(point);
            priorityQueue.push(Element(distance, point));
        }
    }
    // Else process its children
    else {
        QuadtreeNode** children = node->getChildren();
        for (int i = 0; i < 4; ++i) {
            if (children[i] != nullptr) {
                // Calculate the distance from the child node to the query point
                double childDistance = queryPoint.minDistToNode(*children[i]);

                // Push the child node and its distance to the priority queue
                priorityQueue.push(Element(childDistance, children[i]));
            }
        }
    }

    knnSearch(queryPoint, k, priorityQueue, nearestNeighbors);
}

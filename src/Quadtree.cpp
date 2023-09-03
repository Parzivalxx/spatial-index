#include "Quadtree.h"
#include "QuadtreeNode.h"
#include "Point.h"

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
            destroyTree(node->children[i]);
        }
        // Delete the current node
        delete node;
    }
}

// Function to insert a point into the quadtree
void Quadtree::insert(const Point& point) {
    // Call the insert function of the root node to start the insertion process
    root->insert(point);
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


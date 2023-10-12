#include "KDTree.h"
#include <algorithm>

KDTree::KDTree() : root(nullptr) {}

KDTree::~KDTree() {
    destroyTree(root);
}

void KDTree::destroyTree(KDNode* node) {
    if (node == nullptr) {
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

void KDTree::build(std::vector<Point>& points) {
    root = buildTree(points, 0);
}

KDNode* KDTree::buildTree(std::vector<Point> points, int depth) {
    if (points.empty()) {
        return nullptr;
    }

    int dimension = depth % 2; // Alternate between x and y dimensions
    std::size_t medianIndex = points.size() / 2;

    // Sort points based on the current dimension
    if (dimension == 0) {
        std::sort(points.begin(), points.end(), [](Point& a, Point& b) {
            return a.x < b.x;
        });
    }
    else {
        std::sort(points.begin(), points.end(), [](Point& a, Point& b) {
            return a.y < b.y;
        });
    }

    KDNode* medianNode = new KDNode(points[medianIndex], dimension);
    medianNode->left = buildTree(std::vector<Point>(points.begin(), points.begin() + medianIndex), depth + 1);
    medianNode->right = buildTree(std::vector<Point>(points.begin() + medianIndex + 1, points.end()), depth + 1);

    return medianNode;
}

std::vector<Point> KDTree::rangeQuery(double startX, double startY, double endX, double endY) const {
    std::vector<Point> result;
    rangeQuery(root, startX, startY, endX, endY, 0, result);
    return result;
}

void KDTree::rangeQuery(KDNode* node, double startX, double startY, double endX, double endY, int depth, std::vector<Point>& result) const {
    if (node == nullptr) {
        return;
    }

    int dimension = depth % 2;

    if (node->point.x >= startX && node->point.x <= endX && node->point.y >= startY && node->point.y <= endY) {
        result.push_back(node->point);
    }

    if (dimension == 0) {
        if (node->point.x >= startX) {
            rangeQuery(node->left, startX, startY, endX, endY, depth + 1, result);
        }
        if (node->point.x <= endX) {
            rangeQuery(node->right, startX, startY, endX, endY, depth + 1, result);
        }
    }
    else {
        if (node->point.y >= startY) {
            rangeQuery(node->left, startX, startY, endX, endY, depth + 1, result);
        }
        if (node->point.y <= endY) {
            rangeQuery(node->right, startX, startY, endX, endY, depth + 1, result);
        }
    }
}


std::vector<Point> KDTree::knnQuery(double queryX, double queryY, int k) const {
    std::vector<Point> result;
    Point queryPoint(queryX, queryY);
    KDNodeComparator comparator(queryPoint);
    std::priority_queue<KDNode*, std::vector<KDNode*>, KDNodeComparator> priorityQueue(comparator);
    kNearestNeighbors(root, queryPoint, k, priorityQueue);

    while (!priorityQueue.empty()) {
        result.push_back(priorityQueue.top()->point);
        priorityQueue.pop();
    }

    return result;
}

void KDTree::kNearestNeighbors(KDNode* node, const Point& queryPoint, int k, std::priority_queue<KDNode*, std::vector<KDNode*>, KDNodeComparator>& priorityQueue) const {
    if (node == nullptr) {
        return;
    }

    // Calculate the distance between the current node's point and the query point
    double distance = node->point.euclideanDistance(queryPoint);


    // If the priority queue size exceeds k, remove the farthest node
    if (priorityQueue.size() > k) {
        priorityQueue.pop();
    }

    // Determine which child (left or right) to search first based on the splitting dimension
    KDNode* nearChild = nullptr;
    KDNode* farChild = nullptr;
    if (node->dimension == 0) {
        if (queryPoint.x < node->point.x) {
            nearChild = node->left;
            farChild = node->right;
        }
        else {
            nearChild = node->right;
            farChild = node->left;
        }
    }
    else { // Assuming dimension 1 corresponds to y-coordinate
        if (queryPoint.y < node->point.y) {
            nearChild = node->left;
            farChild = node->right;
        }
        else {
            nearChild = node->right;
            farChild = node->left;
        }
    }

    // Recursively search the nearest child
    kNearestNeighbors(nearChild, queryPoint, k, priorityQueue);

    // Check if we need to search the far child
    if (priorityQueue.size() < k || distance < priorityQueue.top()->point.euclideanDistance(queryPoint)) {
        priorityQueue.push(node);
        if (priorityQueue.size() > k) {
            priorityQueue.pop();
        }
        kNearestNeighbors(farChild, queryPoint, k, priorityQueue);
    }
}

KDNode* KDTree::deletePoint(KDNode* node, const Point& point, int depth) {
    if (node == nullptr) {
        return nullptr; // Point not found in the KD-Tree
    }

    int currentDim = depth % 2;

    if (point == node->point) {
        // Found the node with the point, remove it
        if (node->right == nullptr && node->left == nullptr) {
            delete node;
            return nullptr; // Node has no children, simply delete it
        }
        else {
            // Find the in-order successor node in the subtree
            KDNode* successor = findMin(node->right, depth);
            node->point = successor->point;
            node->right = deletePoint(node->right, successor->point, depth + 1);
        }
    }
    else if (point < node->point) {
        node->left = deletePoint(node->left, point, depth + 1);
    }
    else {
        node->right = deletePoint(node->right, point, depth + 1);
    }
    return node;
}

KDNode* KDTree::findMin(KDNode* node, int depth) {
    if (node == nullptr) {
        return nullptr;
    }

    int currentDim = depth % 2; // Assuming a 2D KD-Tree

    KDNode* leftMin = findMin(node->left, depth + 1);
    KDNode* rightMin = findMin(node->right, depth + 1);
    KDNode* minNode = node;

    if (leftMin != nullptr) {
        if (currentDim == 0) {
            if (leftMin->point < minNode->point) {
                minNode = leftMin;
            }
        }
        else {
            if (leftMin->point < minNode->point) {
                minNode = leftMin;
            }
        }
    }

    if (rightMin != nullptr) {
        if (currentDim == 0) {
            if (rightMin->point < minNode->point) {
                minNode = rightMin;
            }
        }
        else {
            if (rightMin->point < minNode->point) {
                minNode = rightMin;
            }
        }
    }

    return minNode;
}

void KDTree::deletePoint(const Point& point) {
    root = deletePoint(root, point, 0);
}


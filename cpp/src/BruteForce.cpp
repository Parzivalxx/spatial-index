#include "BruteForce.h"
#include <queue>
#include <algorithm>
#include <functional>

BruteForce::BruteForce(const std::vector<Point>& data) : data_(data) {}

std::vector<Point> BruteForce::rangeQuery(double startX, double startY, double endX, double endY) const {
    std::vector<Point> result;
    for (const Point& point : data_) {
        if (point.x >= startX && point.x <= endX && point.y >= startY && point.y <= endY) {
            result.push_back(point);
        }
    }
    return result;
}

std::vector<Point> BruteForce::knnQuery(double queryX, double queryY, int k) const {
    // Create a priority queue to store k-nearest points
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::less<std::pair<double, Point>>> pq;

    for (const Point& point : data_) {
        double distance = point.euclideanDistance(queryX, queryY);
        pq.push(std::make_pair(distance, point));

        if (pq.size() > k) {
            pq.pop();
        }
    }

    // Extract the k-nearest points from the priority queue
    std::vector<Point> kNearestPoints;
    while (!pq.empty()) {
        kNearestPoints.push_back(pq.top().second);
        pq.pop();
    }

    return kNearestPoints;
}
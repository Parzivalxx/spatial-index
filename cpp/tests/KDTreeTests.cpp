#include <gtest/gtest.h>
#include "KDTree.h"

TEST(KDTreeTest, DeletePoint) {
    KDTree kdTree;
    std::vector<Point> points = { Point(1.0, 2.0), Point(3.0, 4.0), Point(5.0, 6.0) };
    kdTree.build(points);

    Point pointToDelete(3.0, 4.0);
    kdTree.deletePoint(pointToDelete);

    std::vector<Point> result = kdTree.rangeQuery(pointToDelete.x, pointToDelete.y, pointToDelete.x, pointToDelete.y);
    EXPECT_TRUE(result.empty());
}

#include <gtest/gtest.h>
#include "BruteForce.h"

TEST(BruteForceTest, DeletePoint) {
    BruteForce bf;

    std::vector<Point> points = { Point(1.0, 2.0), Point(3.0, 4.0), Point(5.0, 6.0) };
    bf.build(points);

    Point pointToDelete(3.0, 4.0);
    bf.deletePoint(pointToDelete);

    std::vector<Point> result = bf.rangeQuery(pointToDelete.x, pointToDelete.y, pointToDelete.x, pointToDelete.y);
    EXPECT_TRUE(result.empty());
}

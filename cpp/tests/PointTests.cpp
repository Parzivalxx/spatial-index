#include "gtest/gtest.h"
#include "Point.h"

TEST(PointTests, EuclideanDistance) {
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);

    double expectedDistance = 25.0;

    double actualDistance = p1.euclideanDistance(p2.x, p2.y);

    EXPECT_DOUBLE_EQ(expectedDistance, actualDistance);
}

TEST(PointTests, MinDistToPoint) {
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);

    double expectedMinDist = 25.0;

    double actualMinDist = p1.minDistToPoint(p2);

    EXPECT_DOUBLE_EQ(expectedMinDist, actualMinDist);
}

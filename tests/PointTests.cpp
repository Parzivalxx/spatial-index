#include "gtest/gtest.h" // Include Google Test headers
#include "Point.h"       // Include your Point class header

TEST(PointTests, EuclideanDistance) {
    // Create two points
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);

    // Calculate the expected Euclidean distance
    double expectedDistance = 25.0;

    // Calculate the actual distance using the function
    double actualDistance = p1.euclideanDistance(p2.x, p2.y);

    // Check if the actual distance matches the expected distance
    EXPECT_DOUBLE_EQ(expectedDistance, actualDistance);
}

TEST(PointTests, MinDistToPoint) {
    // Create two points
    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);

    // Calculate the expected minimum distance
    double expectedMinDist = 25.0;

    // Calculate the actual minimum distance using the function
    double actualMinDist = p1.minDistToPoint(p2);

    // Check if the actual minimum distance matches the expected minimum distance
    EXPECT_DOUBLE_EQ(expectedMinDist, actualMinDist);
}


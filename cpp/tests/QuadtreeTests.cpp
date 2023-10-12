#include <gtest/gtest.h>
#include "Quadtree.h"

TEST(QuadtreeTest, DeletePoint) {
    Quadtree quadtree(0.0, 0.0, 10.0, 10.0);

    std::vector<Point> points = { Point(1.0, 2.0), Point(3.0, 4.0), Point(5.0, 6.0) };
    quadtree.build(points);

    // Delete a point
    Point pointToDelete(3.0, 4.0);
    quadtree.deletePoint(pointToDelete);

    std::vector<Point> result = quadtree.rangeQuery(pointToDelete.x, pointToDelete.y, pointToDelete.x, pointToDelete.y);
    EXPECT_TRUE(result.empty());
}

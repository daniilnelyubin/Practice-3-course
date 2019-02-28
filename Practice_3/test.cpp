#include "task.h"
#include <gtest/gtest.h>

const double EPS = 1e-6;

TEST(structTest, input1) {
    point testPoint = point(1, 1);
    EXPECT_EQ(testPoint.x, 1);
    EXPECT_EQ(testPoint.y, 1);
}

TEST(structTest, operatorMinus1) {
    point testPoint1 = point(2, 2);
    point testPoint2 = point(1, 1);
    point testPointResult = testPoint2 - testPoint1;
    EXPECT_EQ(testPointResult.x, -1);
    EXPECT_EQ(testPointResult.y, -1);
}

TEST(structTest, operatorMinus2) {
    point testPoint1 = point(2, 2);
    point testPoint2 = point(1, 1);
    point testPointResult = testPoint1 - testPoint2;
    EXPECT_EQ(testPointResult.x, 1);
    EXPECT_EQ(testPointResult.y, 1);
}

TEST(structTest, operatorPower1) {
    point testPoint = point(2, 3) * 2;
    EXPECT_EQ(testPoint.x, 4);
    EXPECT_EQ(testPoint.y, 6);
}

TEST(structTest, operatorPower2) {
    point testPoint = point(2, 3) * -2;
    EXPECT_EQ(testPoint.x, -4);
    EXPECT_EQ(testPoint.y, -6);
}

TEST(structTest, operatorDiv1) {
    point testPoint = point(2, 6) / 2;
    EXPECT_EQ(testPoint.x, 1);
    EXPECT_EQ(testPoint.y, 3);
}

TEST(structTest, operatorDiv2) {
    point testPoint = point(2, 6) / -2;
    EXPECT_EQ(testPoint.x, -1);
    EXPECT_EQ(testPoint.y, -3);
}

TEST(structTest, operatorPlus1) {
    point testPoint1 = point(-2, -2);
    point testPoint2 = point(1, 1);
    point testPointResult = testPoint2 + testPoint1;
    EXPECT_EQ(testPointResult.x, -1);
    EXPECT_EQ(testPointResult.y, -1);
}

TEST(structTest, operatorPlus2) {
    point testPoint1 = point(2, 2);
    point testPoint2 = point(-1, -1);
    point testPointResult = testPoint1 + testPoint2;
    EXPECT_EQ(testPointResult.x, 1);
    EXPECT_EQ(testPointResult.y, 1);
}

TEST(structTest, normalized) {
    point testPoint = point(1, 1);
    testPoint.normalized();
    EXPECT_GT(testPoint.y,1/sqrt(2)-EPS);
    EXPECT_GT(testPoint.x,1/sqrt(2)-EPS);
}
TEST(structTest, dist2) {
    point testPoint = point(5, 5);
    EXPECT_EQ(testPoint.dist2(),50);
}

TEST(structTest, dist) {
    point testPoint = point(5, 5);
    EXPECT_GT(testPoint.dist(),sqrt(50)-EPS);
}

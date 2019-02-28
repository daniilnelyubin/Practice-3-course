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

TEST(inputData,NTest1){
    point *points = new point[2];
    EXPECT_THROW(task(0,1,1,points),std::logic_error);
}
TEST(inputData,NTest2){
    point *points = new point[2];
    EXPECT_THROW(task(101,1,1,points),std::logic_error);
}
TEST(inputData,RTest1){
    point *points = new point[2];
    EXPECT_THROW(task(1,0,1,points),std::logic_error);
}
TEST(inputData,RTest2){
    point *points = new point[2];
    EXPECT_THROW(task(1,10001,1,points),std::logic_error);
}
TEST(inputData,rTest1){
    point *points = new point[2];
    EXPECT_THROW(task(1,1,0,points),std::logic_error);
}
TEST(inputData,rTest2){
    point *points = new point[2];
    EXPECT_THROW(task(1,1,10001,points),std::logic_error);
}
TEST(examples,example1){
    point *points = new point[3];
    points[0].x=0;
    points[0].y=0;
    points[1].x=0;
    points[1].y=4;
    points[2].x=4;
    points[2].y=0;
    EXPECT_EQ(task(3,3,1,points),2);
}
TEST(examples,example2){
    point *points = new point[5];
    points[0].x=0;
    points[0].y=0;
    points[1].x=0;
    points[1].y=1;
    points[2].x=0;
    points[2].y=2;
    points[3].x=0;
    points[3].y=3;
    points[4].x=0;
    points[4].y=4;
    EXPECT_EQ(task(5,1,1,points),1);
}
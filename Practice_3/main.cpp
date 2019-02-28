#include <gtest/gtest.h>
#include "task.h"

int main(int argc, char* argv []) {
    testing::InitGoogleTest(&argc, argv);
    int code = RUN_ALL_TESTS();
    point *points= new point[100];
//    int N, x, y, R, r;
//    std::cin >> N;
//    for (int i = 0; i < N; i++)
//        std::cin >> points[i].x >> points[i].y;
//    std::cin >> R >> r;
//    std::cout<<task(N,R,r,points);
    return code;

}
#include <gtest/gtest.h>
#include "task.h"

int main(int argc, char* argv []) {
    testing::InitGoogleTest(&argc, argv);
    int code = RUN_ALL_TESTS();
    task();
    return code;

}
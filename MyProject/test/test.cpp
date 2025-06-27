#include <gtest/gtest.h>
#include "../src/tensor.hpp"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    Tensor<int, 3, 3, 3> MyTensor(0);
    int element =  MyTensor(2,0,0);
    ASSERT_EQ(0, MyTensor(2,0,0));
}
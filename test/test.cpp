#include <gtest/gtest.h>

// Function to be tested
int add(int a, int b) {
    return a + b;
}

// Test case for the add function
TEST(AddTest, PositiveNumbers) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(10, 7), 17);
    EXPECT_EQ(add(-5, 3), -2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
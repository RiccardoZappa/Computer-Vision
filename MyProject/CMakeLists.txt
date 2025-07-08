cmake_minimum_required(VERSION 3.22)

project(MyProject LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)


# --- Find Dependencies ---
find_package(OpenCV REQUIRED)
find_package(Protobuf REQUIRED)
find_package(GTest REQUIRED)

enable_testing()

# --- Project Sources and Executable ---
add_executable(my_project
    src/main.cpp
    src/cudaOperations/cudaOperations.cu
)

add_executable(runUnitTests
    test/test.cpp
)

# --- Linking Libraries ---
target_link_libraries(my_project PRIVATE
    ${OpenCV_LIBS}
)

target_link_libraries(runUnitTests PRIVATE
    GTest::gtest_main
)


# --- Optional: Set CUDA architecture flags ---
set_target_properties(my_project PROPERTIES
    CUDA_ARCHITECTURES "75" # Specify your target GPU architecture(s)
)

set(TEST_EXECUTABLE $<TARGET_FILE:runUnitTests>)

gtest_discover_tests(
    runUnitTests
    TEST_PREFIX "Test"
    TEST_LAUNCH_COMMAND ${TEST_EXECUTABLE}
)
cmake_minimum_required(VERSION 3.0)
project(MySimpleProject)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(Boost REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})

set(SOURCE_DIR Application)
# Add the executable target
set(SOURCES ${SOURCE_DIR}/main.cpp)

# Add the executable target
add_executable(MySimpleProject ${SOURCES})
target_link_libraries(MySimpleProject ${BOOST_LIBRARIES})

set(TEST_DIR test)

set(TESTS ${TEST_DIR}/test.cpp)

add_executable(MyTests ${TESTS})

target_link_libraries(MyTests ${GTEST_LIBRARIES} pthread)
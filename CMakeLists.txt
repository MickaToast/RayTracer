cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES    src/Camera/Camera.cpp
                    src/Vector/Vector2.cpp
                    src/Vector/Vector3.cpp
                    src/loader/OBJLoader.hh)
add_executable(RayTracer ${SOURCE_FILES} src/main.cpp)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system graphics window network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
set(TEST_FILES  src/main_test.cpp
                src/Camera/Camera_test.cpp)
add_executable(runTests ${TEST_FILES} ${SOURCE_FILES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
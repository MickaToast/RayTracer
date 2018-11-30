cmake_minimum_required(VERSION 3.9)
project(RayTracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES    src/Engine/Engine.cc
                    src/Camera/Camera.cc
                    src/Vector/Vector2.cc
                    src/Vector/Vector3.cc
                    src/Loader/OBJLoader.cc
                    src/Engine/Color.cc)
add_executable(RayTracer ${SOURCE_FILES} src/main.cc)

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
set(TEST_FILES  src/main_test.cc
                src/Engine/Color_test.cc
                src/Engine/Engine_test.cc
                src/Camera/Camera_test.cc
                src/Vector/Vector2_test.cc
                src/Vector/Vector3_test.cc)
add_executable(runTests ${SOURCE_FILES} ${TEST_FILES})
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
target_compile_definitions(runTests PUBLIC RT_TESTING_ENV)
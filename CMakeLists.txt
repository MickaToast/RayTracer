cmake_minimum_required(VERSION 3.9)
project(RayTracer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES    src/Camera/Camera.cc
                    src/Dispatcher/Dispatcher.cc
                    src/Engine/Color.cc
                    src/Engine/Engine.cc
                    src/KDTree/KDBox.cc
                    src/KDTree/KDNode.cc
                    src/Loader/AssimpLoader.cc
                    src/Material/Material.cc
                    src/Mesh/Mesh.cc
                    src/Mesh/Object.cc
                    src/Mesh/Triangle.cc)
add_executable(RayTracer ${SOURCE_FILES} src/main.cc)

target_compile_options(RayTracer PUBLIC
        -W -Wall -Wextra -Werror -Wuninitialized -Wduplicated-cond
        -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wold-style-cast
        -Wuseless-cast -Wdouble-promotion -Wshadow -O3 -Ofast)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Detect and add SFML
find_package(SFML 2 REQUIRED system graphics window network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
endif()

# Detect and add Assimp
find_package(assimp REQUIRED)
if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif()

target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES} ${SFML_LIBRARIES} pthread)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
set(TEST_FILES  src/main_test.cc
                src/Camera/Camera_test.cc
                src/Dispatcher/Dispatcher_test.cc
                src/Engine/Color_test.cc
                src/Engine/Engine_test.cc
                src/KDTree/KDBox_test.cc
                src/KDTree/KDNode_test.cc
                src/Loader/AssimpLoader_test.cc
                src/Mesh/Triangle_test.cc
                src/Vector/Vector2_test.cc
                src/Vector/Vector3_test.cc)
add_executable(runTests ${SOURCE_FILES} ${TEST_FILES})
target_compile_options(runTests PUBLIC -W -Wall -Wextra -Werror -Wuninitialized -Wduplicated-cond
        -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wold-style-cast
        -Wuseless-cast -Wdouble-promotion -Wshadow -fprofile-arcs -ftest-coverage)
target_link_libraries(runTests ${GTEST_LIBRARIES} ${ASSIMP_LIBRARIES} pthread gcov)
target_compile_definitions(runTests PUBLIC RT_TESTING_ENV)

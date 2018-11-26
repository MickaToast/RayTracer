#include "gtest/gtest.h"
#include "Camera.hh"

namespace rt {
    TEST(Camera, initBasic) {
        Camera cam = Camera(Vector3(), Vector3(0, 0, -1));

        EXPECT_EQ(cam.getAxis()[0], Vector3(1, 0, 0));
        EXPECT_EQ(cam.getAxis()[1], Vector3(0, 1, 0));
        EXPECT_EQ(cam.getAxis()[2], Vector3(0, 0, -1));
    }
}
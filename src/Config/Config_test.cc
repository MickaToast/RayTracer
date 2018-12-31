/* Copyright (c) 2018 mickael.leclerc@epitech.eu charles.fraisse@epitech.eu
 Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
 The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
OR OTHER DEALINGS IN THE SOFTWARE. */

#include "gtest/gtest.h"
#include "Config.h"

namespace rt {
    TEST(Config, default_config) {
        Config config;

        ASSERT_FALSE(config.RequestBackground());
        ASSERT_FALSE(config.RequestImageOutput());
    }

    TEST(Config, background_config) {
        char const *argv[3];
        argv[0] = argv[1] = "";
        argv[2] = "--background-image=test.jpg";
        Config config;

        config.LoadFromArguments(3, const_cast<char **>(argv));
        ASSERT_TRUE(config.RequestBackground());
        ASSERT_STREQ(config.GetBackgroundPath().c_str(), "test.jpg");
    }

    TEST(Config, output_config) {
        char const *argv[3];
        argv[0] = argv[1] = "";
        argv[2] = "--output-image=5";
        Config config;

        config.LoadFromArguments(3, const_cast<char **>(argv));
        ASSERT_TRUE(config.RequestImageOutput());
        ASSERT_EQ(config.GetImageOutputFrames(), 5);
    }

    TEST(Config, unknown_config) {
        char const *argv[3];
        argv[0] = argv[1] = "";
        argv[2] = "--test=test";
        Config config;

        testing::internal::CaptureStderr();
        config.LoadFromArguments(3, const_cast<char **>(argv));
        ASSERT_STREQ(testing::internal::GetCapturedStderr().c_str(), "Warning: --test is not a recognized option\n");
    }
}  // namespace rt

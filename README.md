# RayTracer

![Current RayTracer Version](https://github.com/MickaToast/RayTracer/blob/master/raytracer_current.png?raw=true)

[![Build Status](https://travis-ci.com/MickaToast/RayTracer.svg?branch=master)](https://travis-ci.com/MickaToast/RayTracer)
[![Coverage Status](https://coveralls.io/repos/github/MickaToast/RayTracer/badge.svg?branch=master)](https://coveralls.io/github/MickaToast/RayTracer?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/c64977c42e714c96a3e85cad31ab8103)](https://www.codacy.com/app/MickaToast/RayTracer?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=MickaToast/RayTracer&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/mickatoast/raytracer/badge/master)](https://www.codefactor.io/repository/github/mickatoast/raytracer/overview/master)

## How to launch

1. Make sure to have SFML installed. Link for installation: <https://www.sfml-dev.org/tutorials/2.5/start-linux.php>
2. Create a directory called cmake-build-debug in the root directory and go to it
3. Execute the following command
```bash
cmake .. && make && ./RayTracer scene.obj
```

# Validation tests
* Make sure to have image-magic installed
* Make sure to build Raytracer in cmake-build-debug

## How to create a test
Create a directory in validation_test with the name of the scene (it must match the name of the scene).
Create test files inside the directory with the following name format: `<number_of_frame_to_render>_<difference_threshold>.jpg`
Then, follow the next point in order to generate the test.

## How to regenerate tests
Go in validation_test directory and launch `./regenerate.sh`

## How to test
Go in validation_test directory and launch `./test.sh`

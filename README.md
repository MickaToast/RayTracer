# RayTracer
[![Build Status](https://travis-ci.com/MickaToast/RayTracer.svg?branch=master)](https://travis-ci.com/MickaToast/RayTracer)
[![Coverage Status](https://coveralls.io/repos/github/MickaToast/RayTracer/badge.svg?branch=master)](https://coveralls.io/github/MickaToast/RayTracer?branch=master)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/0424d0e3189740c7b2628803cb677d56)](https://www.codacy.com/app/MickaToast/RayTracer?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=MickaToast/RayTracer&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/mickatoast/raytracer/badge/master)](https://www.codefactor.io/repository/github/mickatoast/raytracer/overview/master)

## How to launch

1. Make sure to have SFML installed. Link for installation: <https://www.sfml-dev.org/tutorials/2.5/start-linux.php>
2. Create a directory called cmake-build-debug in the root directory and go to it
3. Execute the following command
```bash
cmake .. && make && ./RayTracer scene.obj
```

## How to regenerate validation tests
1. Make sure to build RayTracer in cmake-build-debug
2. `cd validation_test`
3. `./regenerate.sh`
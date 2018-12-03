#!/usr/bin/env bash

echo "Launching validation tests"
status=0
for directory in $(ls -d */ | sed 's#/##')
do
    for test in $(ls ${directory} -I output.jpg -I difference.jpg | sed -e 's/\..*$//')
    do
        echo "Launching test on scene $directory with test $test"
        ../cmake-build-debug/RayTracer ../scenes/${directory}.obj $(echo ${test} | cut -d '_' -f1) --output-image $(echo ${test} | cut -d '_' -f2)
        convert output.bpm ${directory}/output.jpg
        diff=$(compare -metric AE -fuzz 5% ${directory}/output.jpg ${directory}/${test}.jpg ${directory}/difference.jpg 2>&1)
        if [[ ${diff} -ge $(echo ${test} | cut -d '_' -f3) ]]; then
            echo "FAIL: Too many diff for $directory/${test}: $diff"
            status=1
        else
            echo "SUCCESS: Passed ${directory}/${test}: $diff"
        fi
    done
done
exit ${status}
#!/usr/bin/env bash

cd ../cmake-build-debug && cmake .. && make && cd -
echo "Launching validation tests"
status=0
for directory in $(ls -d */ | sed 's#/##')
do
    for test in $(ls ${directory} -I output.jpg -I difference.jpg | sed -e 's/\..*$//')
    do
        echo
        echo "Launching test on scene $directory with test $test"
        ../cmake-build-debug/RayTracer ../scenes/${directory}.dae --output-image=$(echo ${test} | cut -d '_' -f1)
        convert -quality 100% output.bmp ${directory}/output.jpg
        diff=$(compare -metric AE -fuzz 5% ${directory}/output.jpg ${directory}/${test}.jpg ${directory}/difference.jpg 2>&1)
        if [[ ${diff} -ge $(echo ${test} | cut -d '_' -f2) ]]; then
            echo "FAIL: Too many diff for $directory/${test}: $diff"
            echo "Uploading difference..."
            ./upload.sh ${directory}/difference.jpg
            status=1
        else
            echo "SUCCESS: Passed ${directory}/${test}: $diff"
        fi
    done
done
exit ${status}
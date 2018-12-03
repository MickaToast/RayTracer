#!/usr/bin/env bash

echo "Launching validation tests"
status=0
for directory in `ls -d */ | sed 's#/##'`
do
    for test in `ls ${directory} -I difference.bpm | sed -e 's/\..*$//'`
    do
        echo "Launching test on scene $directory with test $test"
        ../cmake-build-debug/RayTracer ../scenes/${directory}.obj `echo ${test} | cut -d '_' -f1` --output-image `echo ${test} | cut -d '_' -f2`
        diff=`compare -metric AE -fuzz 5% output.bpm ${directory}/${test}.bpm ${directory}/difference.bpm 2>&1`
        if [[ ${diff} -ge 15 ]]; then
            echo "FAIL: Too many diff for $directory: $diff"
            status=1
        fi
    done
done
exit ${status}
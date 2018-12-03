#!/usr/bin/env bash

echo "Launching regeneration of validation tests"
for directory in $(ls -d */ | sed 's#/##')
do
    for parameter in $(ls ${directory} -I output.jpg -I difference.jpg | sed -e 's/\..*$//')
    do
        echo "Launching regeneration on scene $directory with parameter ${parameter}"
        ../cmake-build-debug/RayTracer ../scenes/${directory}.obj $(echo ${parameter} | cut -d '_' -f1) --output-image $(echo ${parameter} | cut -d '_' -f2)
        convert output.bpm ${directory}/${parameter}.jpg
    done
done
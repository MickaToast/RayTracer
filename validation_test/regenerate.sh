#!/usr/bin/env bash

cd ../cmake-build-debug && cmake .. && make && cd -
echo "Launching regeneration of validation tests"
for directory in $(ls -d */ | sed 's#/##')
do
    for parameter in $(ls ${directory} -I output.jpg -I difference.jpg | sed -e 's/\..*$//')
    do
        echo "Launching regeneration on scene $directory with parameter ${parameter}"
        ../cmake-build-debug/RayTracer ../scenes/${directory}.dae --output-image=$(echo ${parameter} | cut -d '_' -f1)
        convert -quality 100% output.bmp ${directory}/${parameter}.jpg
    done
done
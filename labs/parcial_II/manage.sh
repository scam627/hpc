#!/bin/bash

g++ -std=c++11 pi-needle-algorithm.cpp -o needle
g++ -std=c++11 pi-dardboard-algorithm.cpp -o dartboard

let N=10

for i in `seq  1 8`
do
    let n=$N*10
    echo $n
    ./dartboard $n >> out_dart.csv
    N=$n
done

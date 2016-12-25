#!/bin/sh

for i in {0..65000}
do
./p1 $i < in | grep "010101010101010101010101010101"
done

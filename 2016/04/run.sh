#!/bin/sh

cat $1 | sed -e 's/-\([0-9]\)/\ \1/g' | sed -e 's/-//g' | sed -E 's/\]//g' | sed -e 's/\[/ /g' | ./p1
cat $1 | sed -e 's/-\([0-9]\)/\ \1/g' | sed -e 's/-//g' | sed -E 's/\]//g' | sed -e 's/\[/ /g' | ./p2
cat $1 | sed -e 's/-\([0-9]\)/\ \1/g' | sed -e 's/-//g' | sed -E 's/\]//g' | sed -e 's/\[/ /g' | ./p3

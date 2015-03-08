#!/bin/sh

i=0
path=$1
name=$2
count=$3

if [ -f $path ] || [ -f $name ] || [ -f $count ]; then
    echo "Usage: ./launcher.sh pathname teamname teamsize"
else
    while (($i < $count)); do
	./lemipc $path $name&
	i=$(expr $i + 1)
	usleep 100000
	echo "Creating player $i"
    done
    fi

#!/bin/sh
g++ -std=c++11 *.cpp -o a
if [ $? -eq 0 ] 
then
    ./a 
    pid=$!
else
    echo "Not running the last compiled bin"
fi
echo "finished running"

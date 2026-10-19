#!/bin/sh

if [ $# -lt 2 ]
then
    echo "Usage: $0 <writefile> <writestr>"
    echo "Error: both a file path and a string to write are required"
    exit 1
fi

writefile=$1
writestr=$2

mkdir -p "$(dirname "$writefile")"
if [ $? -ne 0 ]
then
    echo "Error: could not create directory for $writefile"
    exit 1
fi

echo "$writestr" > "$writefile"
if [ $? -ne 0 ]
then
    echo "Error: could not write to $writefile"
    exit 1
fi

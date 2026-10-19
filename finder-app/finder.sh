#!/bin/sh

if [ $# -lt 2 ]
then
    echo "Usage: $0 <filesdir> <searchstr>"
    echo "Error: both a directory and a search string are required"
    exit 1
fi

filesdir=$1
searchstr=$2

if [ ! -d "$filesdir" ]
then
    echo "Error: $filesdir is not a directory"
    exit 1
fi

nb_files=$(find "$filesdir" -type f | wc -l)
nb_lines=$(grep -r -- "$searchstr" "$filesdir" | wc -l)

echo "The number of files are $nb_files and the number of matching lines are $nb_lines"

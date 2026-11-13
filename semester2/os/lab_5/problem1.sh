#!/bin/bash
#Write a bash script that receives as command line arguments pairs of arguments A and B.
#For each pair, if argumat A contains argument B, display them.

while test $# -ge 2; do
	if echo "$1" | grep -E -q "$2"; then
		echo "$2 found in $1"
	fi
	shift 2
done

if test $# -gt 0; then
	echo "Incomplete pair: $1 -$2"
fi

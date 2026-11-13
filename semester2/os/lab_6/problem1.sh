#!/bin/bash


while test $# -ge 2; do
	n=$1
	if test -d $2;then
	#calculate 
		storage=`ls -l $2 | awk 'BEGIN{storage=0} {storage+=$5} END {print storage}'`
		n1=$((n*9/10))
		if test $storage -ge $n;then
			echo "Oh no! PLIN!"
		elif test $storage1 -ge $n1;then
			echo "Oh no! Aproape plin"

		fi
	else
		echo "$2 is not a directory"
	fi
	shift 2
done


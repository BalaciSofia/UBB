#!/bin/bash
#if the argument is file->display first 10 lines from it
#if the argument is directory->create a file with the same name as the dir with extension 
#".info" that contains the output of ls -l command
#if neither display message
#

while test $# -ge 1; do
	if test -f $1; then
		echo "regular file"
		#head -n 10 $1 
		awk 'NR<11 {print $0}' $1
	elif test -d $1; then
		echo "directory"
		#d_name=$(echo "$1" | awk -F/ '{print $NF}')
		d_name=`echo "$1" | awk -F/ '{print $NF}'`
		f_name="${1}/$d_name.info"
		ls -l $1 > $f_name

	else
		echo "The argument $1 is neither a regular file nor a directory"
	fi
	shift
done

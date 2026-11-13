#!/bin/bash
if test $# -ne 1;then
	echo "not enough arguments"
else
	(sed '1i DATE DESPRE PERSONAL' $1 | sed '/49$/d' | sed '$i TERMINAT') |
	sed -E 's/^([^ ]*) ([^ ]*)/\2 \1/'
fi

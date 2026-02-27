#!/bin/bash
#

dir=$1
t=0
for f in $(ls "$dir" | grep -E "\.c$");do
	if test -f "$dir/$f";then
		count=$(grep -E -c -v "^\s*$" "$dir/$f")
		echo "$f has $count lines"
		t=$((t+count))
	fi
done
echo "total lines: $t"

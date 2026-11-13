#!/bin/bash
# Calculați numărul mediu de linii ale fișierelor de tip text dintr-un director dat ca parametru.
#(comenzi: find, file, wc)

dir=$1
s=0
n=0
for file in $(find $dir -type f);do
	c=`wc -l $file | awk '{print $1}'`
	s=$((s+c))
	n=$((n+1))
done
average=$((s/n))
echo "$average"

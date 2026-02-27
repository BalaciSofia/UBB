#!/bin/bash
# Afișați primele 5 linii și ultimele 5 linii ale tuturor fișierelor de tip text din directorul curent. Dacă un fișier are mai puțin de 10 linii, atunci se va afișa întreg conținutul său.
#(comenzi: head, tail, find, file, wc)


for file in $(find . -type f);do
	cnt=`wc -l $file | awk '{print $1}'`
	if test $cnt -le 10;then
		cat $file
	else
	head -n 5 $file	
	tail -n 5 $file
	fi
done

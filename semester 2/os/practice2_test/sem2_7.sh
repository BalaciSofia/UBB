#!/bin/bash
# Să se scrie un script shell care are ca parametri triplete formate dintr-un nume de fișier, un cuvânt și un număr k. Pentru fiecare astfel de triplet, se vor afișa toate liniile din fișierul care conțin cuvântul dat de exact k ori.
#(comenzi: shift, awk)

while test $# -gt 0;do
	f=$1
	c=$2
	k=$3
	awk -v cuv="$c" -v nr="$k" '
			{
				h=0
                        for (i=1; i<=NF; i++) {
                                if ($i == cuv) h++
                        }
                        if (h == nr) print $0
                }' "$f"
	shift 3
done

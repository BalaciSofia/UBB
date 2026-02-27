#!/bin/bash
#Pentru fiecare fișier dat în linia de comandă, să se afișeze linia care apare de cele mai multe ori. Afișarea se va face în ordinea descrescatoare a numărului de apariții.
#(comenzi: sort, uniq, head)

while test $# -gt 0;do
	f=$1
	sort "$f" |uniq -c |sort -n -r| head -n 1
	shift
done

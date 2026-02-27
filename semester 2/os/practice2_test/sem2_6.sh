#!/bin/bash
#Să se scrie un script shell care va afișa toate fișierele dintr-un director dat și din subdirectoarele acestuia asupra cărora au drepturi de scriere toate cele trei categorii de utilizatori. Aceste fișiere vor fi apoi redenumite, prin adăugarea sufixul '.all' la numele lor inițial.
#(comenzi: find -perm, mv)

dir=$1
#`-perm -g=w
for file in $(find $dir -perm -a=w);do
	echo $file
	mv "$file" "$file.all"	
done	

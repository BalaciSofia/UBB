#!/bin/bash
#Să se scrie un script shell care pentru fiecare fișier cu drepturile 755 dintr-un director dat ca parametru (si subdirectoarele sale) va schimba drepturile de acces în 744. Înainte de modificarea drepturilor de acces, scriptul va cere confirmare din partea utilizatorului (pentru fiecare fișier în parte).
#(comenzi: find, chmod, read)
dir=$1

for file in $(find $dir -type f -perm 755);do
	echo "sure changing for $file?"
	read yn
	if test "$yn" = "yes";then
	       chmod 744 $file
       		echo "permissions changed"	       
	else
		echo "skiped"
	fi
done

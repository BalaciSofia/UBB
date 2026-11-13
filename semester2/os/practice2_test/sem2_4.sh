#$/bin/bash
#Afișați numele fișierelor dintr-un director dat ca parametru care conțin numere cu mai mult de 5 cif

dir=$1
for files in $(find $dir -type f);do
	cnt=`cat $files | grep -E '[0-9]{5,}' -c`
	if test $cnt -gt 0;then
		echo "$files"
	fi
done	

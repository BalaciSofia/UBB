#Find recursively in a directory all ".c" files having more than 500 lines. Stop after finding 2 such files.
#!/bin/bash
dir=$1
i=0
for file in $(find $dir -type f -name "*\.c");do
	cnt=$(wc -l $file | awk '{print $1}')
	if test $cnt -ge 500;then
		echo $file
		i=$((i+1))
		if test $i -eq 2;then
			break
		fi
	fi
done

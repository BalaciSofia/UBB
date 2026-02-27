#Find recursively in a directory, all the files with the extension ".log" and sort their lines (replace the original file with the sorted content).
#!/bin/bash

dir=$1
for file in $(find $dir -type f -name "*.log");do
	touch new_file
	cat $file | sort | awk '{print $0}'>new_file
	mv new_file $file
done

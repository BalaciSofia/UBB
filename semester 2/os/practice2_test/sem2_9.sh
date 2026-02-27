#!/bin/bash
# Să se scrie un script shell care va afișa toate numele fișierelor dintr-un director dat ca parametru și din subdirectoarele sale, al căror nume sunt mai scurte de 8 caractere. Dacă aceste fișiere sunt de tip text, se va afișa și primele 10 linii de text pe care le conțin.

dir=$1

for file in $(find "$dir" -type f); do
        name=$(basename "$file")
        len=${#name}

        if test "$len" -lt 8; then
                echo "$file" 
                if file "$file" | grep -q "text"; then
                        head -n 10 "$file" 
                fi
        fi
done












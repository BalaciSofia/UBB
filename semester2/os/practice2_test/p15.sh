#!/bin/bash

echo 'Nume    Prenume    Data    Telefon    Salariu'
awk '$0!~/^\s*$/ {print $0}' angajati.txt
awk 'BEGIN{c=0} $0!~/^\s*$/ {c++} END{print c}' angajati.txt

#!/bin/sh

for input in ./student-tests/*.in
do
	output="results/"
	output+=$(basename "$input")
	output+=".out"
	echo "============================="
	echo "$input"
	echo "_____________________________"
	./NetConsulting < "$input"
	echo "............................."
done
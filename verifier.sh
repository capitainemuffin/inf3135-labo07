#! /bin/bash

while read i; do 

	if [ -f $i ]; then 

		echo $i ":"
		git log -1 --format="%ar" -- $i

	else 

		echo $i "n'existe pas."
		
	fi 

done < "fichiers.lst"
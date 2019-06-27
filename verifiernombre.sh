#! /bin/bash

fichier=$1
re='^[0-9]+$'
while read line; do 
	
	valide=0

	for mot in $line; do

		if ! [[ $mot =~ $re ]] ; then
			valide=1;
		fi

	done

	if [ $valide -eq 0 ]; then

		for mot in $line; do
			
			resultat="$( printf '%s + %d\n' "$mot" 100 | bc )"
			echo -n $resultat ""

		done

		echo '';

	fi 

done < "$fichier"
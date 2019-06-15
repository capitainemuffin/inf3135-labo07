options=-Wall -pedantic -std=c11
CP = $(shell cat cp.txt)
.PHONY : data clean default test 

default : tp1

tp1 : tp1.o
	gcc tp1.o -o tp1 $(options)

tp1.o : tp1.c
	gcc tp1.c -c -o tp1.o $(options)

clean : 
	rm -f *.o tp1
	rm -f data/*

test : tp1
	./tp1 -d -k 2 -c $(CP) -i nom_du_fichier_en_entree.ext > fichier_sortie.ext
	./tp1 -k 1 -e -c $(CP)
	./tp1 -c $(CP) -d -k 3 -o fichier.out
	./tp1 -c $(CP) -i nom_du_fichier_en_entree.ext -o fichier_sortie.ext -k 7 -e
	./tp1 -c $(CP) -d -k 9 < nom_du_fichier_en_entree.ext > fichier_sortie.ext
	./tp1 -c $(CP) -d -k -1 -a ./data/

data :
	curl https://www.github.com/guyfrancoeur/INF3135_E2019_TP/raw/master/crypto-data.zip -sLO -o crypto-data.zip
	if [ ! -d "data" ]; then mkdir data; fi
	mv crypto-data.zip data/
	unzip data/crypto-data.zip -d data/



options=-Wall -pedantic -std=c11
CP = $(shell cat cp.txt)
entree = data/crypto-msg01.in
sortie = data/crypto-msg01.out
alphabet = data/crypto-msg01.alphabet
cle = $(shell cat data/crypto-msg01.cle)
action = $(shell cat data/crypto-msg01.action)

.PHONY : data clean default test resultat 

default : tp1

tp1 : tp1.o
	gcc tp1.o -o tp1 $(options)

tp1.o : tp1.c
	gcc tp1.c -c -o tp1.o $(options)

clean : 
	rm -fr *.o tp1 alphabet.txt data

test : tp1
	./tp1 -c $(CP) $(action) -k $(cle) -i $(entree) -o $(sortie) -a $(alphabet)

data :
	curl https://www.github.com/guyfrancoeur/INF3135_E2019_TP/raw/master/crypto-data.zip -sLO -o crypto-data.zip
	if [ ! -d "data" ]; then mkdir data; fi
	mv crypto-data.zip data/
	unzip -o data/crypto-data.zip -d data/
	rm -f data/crypto-data.zip

resultat : note-du-tp.txt
	git add note-du-tp.txt
	git commit -m 'note du tp'
	git push origin master



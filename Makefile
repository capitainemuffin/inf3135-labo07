options=-Wall -pedantic -std=c11

.PHONY : data clean default

default : tp1

tp1 : tp1.o
	gcc tp1.o -o tp1 $(options)

tp1.o : tp1.c
	gcc tp1.c -c -o tp1.o $(options)

clean : 
	rm -f *.o tp1
	rm -f data/*

data :
	curl https://www.github.com/guyfrancoeur/INF3135_E2019_TP/raw/master/crypto-data.zipp -L -O
	if [ ! -d "data" ]; then mkdir data; fi
	mv crypto-data.zip data/
	unzip data/crypto-data.zip




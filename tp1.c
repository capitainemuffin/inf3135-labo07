#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum {
	ENCRYPT, DECRYPT
} Action;

typedef struct {
	bool present;
	Action action;
} Mode;

typedef struct {
	bool option_choisie;
	FILE * fichier;
} Fichier_Entree;

typedef struct {
	bool option_choisie;
	FILE * fichier;
} Fichier_Sortie ;

typedef struct {
	bool option_choisie;
	FILE* fichier;
} Alphabet;

typedef struct {
	bool option_choisie;
	double cle;
} Cle;

typedef struct {
	//obligatoire
	char * code_perm;
	Cle cle;
	Mode mode;

	//optionnel
	Fichier_Entree fichier_entree;
	Fichier_Sortie fichier_sortie;
	Alphabet alphabet;

} Arguments;

void lectureArguments(int argc, char* argv[], Arguments* arguments){

	/**
	* Mettre les arguments dans la structure
	**/
	for (int i = 1 ; i < argc ; i++){

		if (strcmp(argv[i], "-c") == 0) {
			/**
			* i+1 doit être le code permanent
			**/
			arguments->code_perm = argv[i+1]; 
			i++;

		} else if(strcmp(argv[i], "-i") == 0) {
			/**
			* i+1 doit être le fichier source
			**/
			arguments->fichier_entree.option_choisie = true;
			arguments->fichier_entree.fichier = fopen(argv[i+1],"r");
			i++;

		} else if(strcmp(argv[i], "-o") == 0) {
			/**
			* i+1 doit être le fichier de sortie
			**/
			arguments->fichier_sortie.option_choisie = true;
			arguments->fichier_sortie.fichier = fopen(argv[i+1], "w");
			i++;

		} else if(strcmp(argv[i], "-d") == 0) {
			/**
			* decodage
			**/
			arguments->mode.present = true;
			arguments->mode.action = DECRYPT;

		} else if (strcmp(argv[i], "-e") == 0 ) {
			/**
			* encodage
 			**/
			arguments->mode.present = true;
 			arguments->mode.action = ENCRYPT;

		} else if(strcmp(argv[i], "-k")) {
			/**
			* i+1 doit être la clé simple
			**/
			arguments->cle.option_choisie = true;
			arguments->cle.cle = atof(argv[i+1]);
			i++;

		} else if (strcmp(argv[i], "-a")) {
			/**
			* i+1 doit être chemin vers alphabet
			**/

			arguments->alphabet.option_choisie = true;
			char* chemin = malloc( strlen(argv[i+1]) + strlen("alphabet.txt") + 1);
			strcpy(chemin,argv[i+1]);
			strcat(chemin, "alphabet.txt");

			arguments->alphabet.fichier = fopen(chemin, "r");

			i++;

		} else {
			/**
			* Argument non permis
			**/
			exit(3);
		}
	}

	/**
	* Vérifier que les arguments obligatoires ont bien étés mis
	**/
	if (arguments->code_perm == NULL){
		//pas de code permanent 
		fprintf(stderr, "Usage: %s <-c CODEpermanent> <-d | -e> <-k valeur> [-i fichier.in] [-o fichier.out] [-a chemin]\n", argv[0]);
		exit(1);
	} 

	//code permanent trop court
	if(strlen(arguments->code_perm) != 12) exit(2);

	//pas d'indication encryption ou decryption
	if (!arguments->mode.present) exit(4);

	//erreur à l'ouverture du fichier d'entrée
	if (arguments->fichier_entree.option_choisie && arguments->fichier_entree.fichier == NULL) exit(5);

	//erreur à l'ouverture du fichier de sortie
	if (arguments->fichier_sortie.option_choisie && arguments->fichier_sortie.fichier == NULL) exit(6);

	//clé non valide ou non fournie
	if(!arguments->cle.option_choisie || !isdigit(arguments->cle.cle)) exit(7);

	//option -a fournie mais erreur à l'ouverture du fichier alphabet
	if(arguments->alphabet.option_choisie && arguments->alphabet.fichier == NULL) exit(8);
	
}

void decryptage(Arguments* arguments){

}

void encryptage(Arguments* arguments){

}


int main(int argc, char ** argv){

	Arguments arguments; 
	lectureArguments(argc, argv, &arguments);

	return 0;
}

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
	bool present;
	FILE * fichier;
} Fichier_Entree;

typedef struct {
	bool present;
	FILE * fichier;
} Fichier_Sortie ;

typedef struct {
	bool present;
	FILE* fichier;
} Alphabet;

typedef struct {
	bool present;
	int cle;
} Cle;

typedef struct {
	//obligatoire
	char * code_perm;
	Cle cle;
	Mode mode;
	Alphabet alphabet;

	//optionnel
	Fichier_Entree fichier_entree;
	Fichier_Sortie fichier_sortie;

} Arguments;

void lectureArguments(int argc, char* argv[], Arguments* arguments){

	arguments->mode.present = false;
	arguments->fichier_entree.present = false;
	arguments->fichier_sortie.present = false;
	arguments->alphabet.present = false;
	arguments->cle.present = false;
	arguments->fichier_sortie.fichier = NULL;
	arguments->fichier_entree.fichier = NULL;
	arguments->alphabet.fichier = NULL;
	arguments->code_perm = NULL;

	/**
	* Mettre les arguments dans la structure.
	* La validation des arguments optionnels se fait
	* directement dans la boucle.
	**/
	for (int i = 1 ; i < argc ; i++){

		if (strcmp(argv[i], "-c") == 0) {
			/**
			* i+1 doit être le code permanent
			**/
			if(i + 1 < argc){
				arguments->code_perm = argv[i+1]; 
				i++;
			}
		
		} else if(strcmp(argv[i], "-i") == 0) {
			/**
			* i+1 doit être le fichier source
			**/
			arguments->fichier_entree.present = true;

			if(i + 1 < argc){
				arguments->fichier_entree.fichier = fopen(argv[i+1],"r");
				i++;
			} 
				
			if(arguments->fichier_entree.fichier == NULL){
				printf("%s\n", "Erreur à l'ouverture du fichier d'entrée");
				exit(5);
			}
				
		} else if(strcmp(argv[i], "-o") == 0) {
			/**
			* i+1 doit être le fichier de sortie
			**/
			arguments->fichier_sortie.present = true;
			if(i + 1 < argc){
				arguments->fichier_sortie.fichier = fopen(argv[i+1], "w");
				i++;
			} 

			if(arguments->fichier_sortie.fichier == NULL){
				printf("%s\n", "Erreur à l'ouverture du fichier de sortie");
				exit(6);
			}
			
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

		} else if(strcmp(argv[i], "-k") == 0) {
			/**
			* i+1 doit être la clé simple
			**/
			arguments->cle.present = true;

			if(i+1 < argc) {
				/**
				* Vérifier que la clé est un nombre
				**/
				char* ptr = argv[i+1];
				for(int j = 0 ; j < strlen(argv[i+1]); j++){
					if (!isdigit(ptr[j])){
						arguments->cle.present = false;
						break;
					} 
				}

				if(arguments->cle.present){
					arguments->cle.cle = atoi(argv[i+1]);
				}
				i++;
			} 

		} else if (strcmp(argv[i], "-a") == 0) {
			/**
			* i+1 doit être chemin vers alphabet
			**/

			arguments->alphabet.present = true;

			if(i + 1 < argc) {
				char* chemin = malloc( strlen(argv[i+1]) + strlen("alphabet.txt") + 1);
				strcpy(chemin,argv[i+1]);
				strcat(chemin, "alphabet.txt");
				arguments->alphabet.fichier = fopen(chemin, "r");
				i++;
			} 

			if(arguments->alphabet.fichier == NULL){
				printf("%s\n", "-A mais erreur à l'ouverture de l'alphabet");
				exit(8);
			}
			
		} else {
			/**
			* Argument non permis
			**/
			printf("%s (%s)\n", "Argument non permis", argv[i]);
			exit(3);
		}
	}

	/**
	* Si option -a non fournie, ouverture de alphabet.txt par défaut
	**/
	if(!arguments->alphabet.present) {
		arguments->alphabet.fichier = fopen("alphabet.txt", "r");
	}

	/**
	* Valider les arguments obligatoires.
	**/
	if (arguments->code_perm == NULL){
		//pas de code permanent 
		printf("Usage: %s <-c CODEpermanent> <-d | -e> <-k valeur> [-i fichier.in] [-o fichier.out] [-a chemin]\n", argv[0]);
		exit(1);
	} 

	if(strlen(arguments->code_perm) != 12) {
		//code permanent trop court
		printf("%s\n", "Code permanent non conforme");
		exit(2);
	}

	if (!arguments->mode.present){
		//pas d'indication encryption ou decryption
		printf("%s\n", "Pas d'indication encryption ou decryption");
		exit(4);
	} 

	if(!arguments->cle.present) {
		//clé non valide ou non fournie
		printf("%s\n", "Clé non valide ou non fournie");
		exit(7);
	}

	if(arguments->alphabet.fichier == NULL){
		printf("%s\n", "Erreur à l'ouverture de l'alphabet");
		exit(8);
	}
	
}

int main(int argc, char ** argv){

	Arguments arguments; 
	lectureArguments(argc, argv, &arguments);

	if(arguments.fichier_entree.present){

		//lire le fichier

		if(arguments.fichier_sortie.present){

			//ecrire dans le fichier

		} else {

			//ecrire dans stdout

		}

	} else {

		//lire stdin

		if(arguments.fichier_sortie.present){

			//ecrire dans le fichier

		} else {

			//ecrire dans stdout

		}

	}

	return 0;
}

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
    int cle;
} Cle;

typedef struct {
    char *code_perm;
    Cle cle;
    Mode mode;
    FILE* alphabet;
    FILE* entree;
    FILE* sortie;

} Arguments;

void validation_args(int argc, char *argv[], Arguments *arguments) {

    for (int i = 1; i < argc; i++) {

        if (strcmp(argv[i], "-c") == 0) {

            if (i + 1 < argc) {
                arguments->code_perm = argv[i + 1];
            } 

            if(i + 1 >= argc || strlen(arguments->code_perm) != 12){
                printf("%s\n", "Code permanent non conforme");
                exit(2);
            }

            i++;

        } else if (strcmp(argv[i], "-i") == 0) {
   
            if (i + 1 < argc) {
                arguments->entree = fopen(argv[i + 1], "r");
            }

            if (i + 1 >= argc || arguments->entree == NULL) {
                printf("%s\n", "Erreur à l'ouverture du fichier d'entrée");
                exit(5);
            }

            i++;

        } else if (strcmp(argv[i], "-o") == 0) {
   
            if (i + 1 < argc) {
                arguments->sortie = fopen(argv[i + 1], "w");
            } 

            if (i + 1 >= argc || arguments->sortie == NULL) {
                printf("%s\n", "Erreur à l'ouverture du fichier de sortie");
                exit(6);
            }

            i++;

        } else if (strcmp(argv[i], "-d") == 0) {

            arguments->mode.present = true;
            arguments->mode.action = DECRYPT;

        } else if (strcmp(argv[i], "-e") == 0) {

            arguments->mode.present = true;
            arguments->mode.action = ENCRYPT;

        } else if (strcmp(argv[i], "-k") == 0) {
    
            if (i + 1 < argc) {

                arguments->cle.present = true;

                char *ptr = argv[i + 1];
                bool negatif = false;
                for (int j = 0; j < strlen(argv[i + 1]); j++) {

                	if(ptr[j] == '-'){

                		if(negatif){
                			arguments->cle.present = false;
                			break;
                		} else {
                			negatif = true;
                		}

                	} else if (!isdigit(ptr[j])) {
                        arguments->cle.present = false;
                        break;
                    }
                }

                if (arguments->cle.present) {
                    arguments->cle.cle = atoi(argv[i+1]);
                }

                i++;
            }

        } else if (strcmp(argv[i], "-a") == 0) {
    
            if (i + 1 < argc) {

                if( argv[i+1][strlen(argv[i+1]) -1] != '/' ){
                    arguments->alphabet = fopen(argv[i+1], "r");
                } else {
                    char *chemin = malloc(strlen(argv[i + 1]) + strlen("alphabet.txt") + 1);
                    strcpy(chemin, argv[i + 1]);
                    strcat(chemin, "alphabet.txt");
                    arguments->alphabet = fopen(chemin, "r");
                    free(chemin);
                }
     
                i++;
            }

        } else {

            printf("%s (%s)\n", "Argument non permis", argv[i]);
            exit(3);
        }
    }

    if (arguments->code_perm == NULL) {
        printf("Usage: %s <-c CODEpermanent> <-d | -e> <-k valeur> [-i fichier.in] [-o fichier.out] [-a chemin]\n",
               argv[0]);
        exit(1);
    }

    if (!arguments->mode.present) {
        printf("%s\n", "Pas d'indication encryption ou decryption");
        exit(4);
    }

    if (!arguments->cle.present) {
        printf("%s\n", "Clé non valide ou non fournie");
        exit(7);
    }

    if (arguments->alphabet == NULL) {
        printf("%s\n", "Erreur à l'ouverture de l'alphabet");
        exit(8);
    }

}

int main(int argc, char **argv) {

    Arguments arguments;
    arguments.mode.present = false;
    arguments.cle.present = false;
    arguments.entree = stdin;
    arguments.sortie = stdout;
    arguments.alphabet = fopen("alphabet.txt", "r");
    arguments.code_perm = NULL;

    validation_args(argc, argv, &arguments);

	if(arguments.mode.action == DECRYPT){
		arguments.cle.cle = -(arguments.cle.cle);
	}

	// taille de l'alphabet
	fseek(arguments.alphabet, 0, SEEK_END);
	int taille = ftell(arguments.alphabet);
	fseek(arguments.alphabet, 0, SEEK_SET);

    char old;
    char new;

    while ((old = fgetc(arguments.entree)) != EOF) {

    	char alphabet;
    	bool trouve = false;

    	while((alphabet = fgetc(arguments.alphabet)) != EOF){
    		if(alphabet == old) {
    			trouve = true;
    			fseek(arguments.alphabet, -1, SEEK_CUR);
    			break;
    		}
    	}

    	if(trouve){

    		//loop dans l'alphabet
    		int decalage = taille % arguments.cle.cle;
    		fseek(arguments.alphabet, decalage, SEEK_CUR);
    		new = fgetc(arguments.alphabet);

    	} else {
    		new = old;
    	}

    	fseek(arguments.alphabet, 0, SEEK_SET);
    	fprintf(arguments.sortie, "%c", new);

    } 

    if (!feof(arguments.entree)){
    	printf("%s\n", "Erreur à l'ouverture du fichier d'entrée");
    	exit(5);
    }

    fclose(arguments.entree);
    fclose(arguments.sortie);

    return 0;
}

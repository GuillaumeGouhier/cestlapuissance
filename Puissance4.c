#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char tableau[6][7] = {{' ',' ',' ',' ',' ',' ',' '},
											{' ',' ',' ',' ',' ',' ',' '},
											{' ',' ',' ',' ',' ',' ',' '},
											{' ',' ',' ',' ',' ',' ',' '},
											{' ',' ',' ',' ',' ',' ',' '},
											{' ',' ',' ',' ',' ',' ',' '}};

int column, line, alternanceJoueur = 1;
char symboleJoueur1 = 'O', symboleJoueur2 = 'X', symboleJoueur, joueur1[30] = "", joueur2[30] = "";


// mise en place de la grille

void initialisationTableau() {
	int line, column;
	printf("\n\t\t\t\t---------------\n");
	printf("\t\t\t\t| Puissance 4 |\n");
	printf("\t\t\t\t---------------\n\n\n");
	printf("\t\t\t\t 1 2 3 4 5 6 7\n");
	for(line = 0; line < 6; line++) {
		printf("\t\t\t\t");
		printf("+-+-+-+-+-+-+-+");
		printf("\n");
		printf("\t\t\t\t");
		for (column = 0; column < 7; column++) {
			printf("|%c", tableau[5 - line][column]);
		}
		printf("|");
		if (line == 6){
			printf("+-+-+-+-+-+-+-+");
			printf("\n");
			printf("\t\t\t\t");
			printf("+-+-+-+-+-+-+-+");
		}
		printf("\n");
	}
	printf("\n");
}


int recommencerPartie() {
  char reponse[3];
  while(true) {
    printf("Voulez vous faire une autre partie ? (oui/non) ");
    scanf("%s", reponse);
    if(!strncmp(reponse, "oui", 3)) {
     printf("\nC'est parti !\n");
     return 1;
    }
   else if(!strncmp(reponse, "non", 3)) {
     return 0;
   }
   else {
     printf("\nVeuillez rentrer oui ou non.\n");
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Gestion Utilisateur


int entreeUtilisateur(alternanceJoueur) {
  int choixJoueur;
	int l;
  while (true) {
    printf("\n");
    printf("Joueur %d, entrez le numéro de colonne souhaité (entre 1 et 7 inclus) : ", alternanceJoueur);
    scanf("\n");
    scanf("%c", &choixJoueur);
		if((int)choixJoueur > 48 && (int)choixJoueur < 56) {
			column = (int)choixJoueur - 49;
	    return column;
		}
  }
}


int placerJetonLigne(column) {
  while (true) {
    for(line = 0; line < 6; line++) {
      if(tableau[line][column] == ' ') {
        return line;
      }
			if((tableau[line][column] == 'X') || (tableau[line][column] == '+')) {
				if(line == 5) {
		    	printf("Vous ne pouvez pas jouer dans cette colonne\n");
		    	column = entreeUtilisateur(alternanceJoueur);
				}
			}
    }
  }
}


void RemplacerCase(line, column, symboleJoueur) {
	tableau[line][column] = symboleJoueur;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// JOUEUR 1 //
	// Possibilité en vérifiant si le point adjacent est bien le même:

	int is_adjacent_1(int column, int line, int vertical, int horizontal) {
		int n = 0;

		// Alignement vers la droite

		if (vertical == 0) {
			if (horizontal == 1) {
				while ((tableau[line][column]) == (tableau[line][column+1])&&(tableau[line][column] =='O'))
				{
					n++;
					column++;
				}
			}

		// Alignement vers la gauche

			else if (horizontal == -1) {
				while ((tableau[line][column]) == (tableau[line][column-1])&&(tableau[line][column] =='O'))
				{
					n++;
					column--;
				}
			}
		}

		// Alignement vers le haut

		if (vertical == 1) {
			if (horizontal == 0) {
				while ((tableau[line][column]) == (tableau[line+1][column])&&(tableau[line][column] =='O'))
				{
					n++;
					line++;
				}
			}

		//Diagonale haut gauche

			else if (horizontal == -1) {
				while ((tableau[line][column]) == (tableau[line+1][column-1])&&(tableau[line][column] =='O'))
				{
					n++;
					line++;
					column--;
				}
			}

		//Diagonale haut droite

			else if (horizontal == 1) {
				while ((tableau[line][column]) == (tableau[line+1][column+1])&&(tableau[line][column] =='O'))
				{
					n++;
					line++;
					column++;
				}
			}
		}

		// Alignement vers le bas

		if (vertical == -1) {
			if (horizontal == 0) {
				while ((tableau[line][column]) == (tableau[line-1][column])&&(tableau[line][column] =='O'))
				{
					n++;
					line--;
				}
			}

		// Diagonale bas gauche

			else if (horizontal == -1) {
				while ((tableau[line][column]) == (tableau[line-1][column-1])&&(tableau[line][column] =='O'))
				{
					n++;
					line--;
					column--;
				}
			}

		// Diagonale bas droite

			else if (horizontal == 1) {
				while ((tableau[line][column]) == (tableau[line-1][column+1])&&(tableau[line][column] =='O'))
				{
					n++;
					line--;
					column++;
				}
			}
		}
		return(n);
	}

	//Vérification de victoire joueur 1

int success_player_1(int column, int line) {
	if(is_adjacent_1(column, line, 0, 1) + is_adjacent_1(column, line, 0, -1) > 2 ||
		is_adjacent_1(column, line, 1, 0) + is_adjacent_1(column, line, -1, 0) > 2 ||   // Si 4 caractères se suivent, on renvoie True
		is_adjacent_1(column, line, 1, 1) + is_adjacent_1(column, line, -1, -1) > 2 ||   // Sinon on renvoie False
		is_adjacent_1(column, line, 1, -1) + is_adjacent_1(column, line, -1, 1) > 2) {
      printf("Victoire de %s\n", joueur1);
		  return 0;
		}
	return 1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// JOUEUR 2 //
	// Possibilité en vérifiant si le point adjacent est bien le même:

	int is_adjacent_2(int column, int line, int vertical, int horizontal) {
		int n = 0;

		// Alignement vers la droite

		if (vertical == 0) {
			if (horizontal == 1) {
				while ((tableau[line][column]) == (tableau[line][column+1])&&(tableau[line][column] =='X'))
				{
					n++;
					column++;
				}
			}

		// Alignement vers la gauche

			else if (horizontal == -1) {
				while ((tableau[line][column]) == (tableau[line][column-1])&&(tableau[line][column] =='X'))
				{
					n++;
					column--;
				}
			}
		}

		// Alignement vers le haut

		if (vertical == 1) {
			if (horizontal == 0) {
				while ((tableau[line][column]) == (tableau[line+1][column])&&(tableau[line][column] =='X'))
				{
					n++;
					line++;
				}
			}

		//Diagonale haut gauche

			else if (horizontal == -1) {
				while ((tableau[line][column]) == (tableau[line+1][column-1])&&(tableau[line][column] =='X'))
				{
					n++;
					line++;
					column--;
				}
			}

		//Diagonale haut droite

			else if (horizontal == 1) {
				while ((tableau[line][column]) == (tableau[line+1][column+1])&&(tableau[line][column] =='X'))
				{
					n++;
					line++;
					column++;
				}
			}
		}

		// Alignement vers le bas

		if (vertical == -1) {
			if (horizontal == 0) {
				while ((tableau[line][column]) == (tableau[line-1][column])&&(tableau[line][column] =='X'))
				{
					n++;
					line--;
				}
			}

		// Diagonale bas gauche

			else if (horizontal == -1) {
				while ((tableau[line][column]) == (tableau[line-1][column-1])&&(tableau[line][column] =='X'))
				{
					n++;
					line--;
					column--;
				}
			}

		// Diagonale bas droite

			else if (horizontal == 1) {
				while ((tableau[line][column]) == (tableau[line-1][column+1])&&(tableau[line][column] =='X'))
				{
					n++;
					line--;
					column++;
				}
			}
		}
		return(n);
	}

	//Vérification de victoire joueur 2

int success_player_2(int column, int line) {
	if(is_adjacent_2(column, line, 0, 1) + is_adjacent_2(column, line, 0, -1) > 2 ||
		is_adjacent_2(column, line, 1, 0) + is_adjacent_2(column, line, -1, 0) > 2 ||   // Si 4 caractères se suivent, on renvoie True
		is_adjacent_2(column, line, 1, 1) + is_adjacent_2(column, line, -1, -1) > 2 ||   // Sinon on renvoie False
		is_adjacent_2(column, line, 1, -1) + is_adjacent_2(column, line, -1, 1) > 2) {
      printf("Victoire de %s\n", joueur2);
		  return 0;
		}
	return 1;
}




int verif_egalite() {
	int i, j;
	for(i=0; i<6; i++) {
		for (j=0; j<7; j++) {
			if(tableau[i][j] != ' ') {   // On teste la présence d'une chaîne vide dans le tableau
				return 0;                  // Si il n'y en a plus, la partie est declarée comme une égalité
      }
		}
	}
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Fonction principale


int main(int argc, char const *argv[]) {
	 // Règles du jeux

	 printf("\n\n\n\x1B[31m\t\t****Bienvenue au jeu Puissance 4****\n \x1B[0m\n");
	 printf("\t\x1B[32m*Règles du jeu*\n");
	 printf("\tChacun de vous a droit a 21 jetons, à vous de les utiliser à bon escient pour gagner\n");
	 printf("\tChaque joueur devra lancer un jeton à tour de rôle dans la case de son choix\n");
	 printf("\tLe but du jeu est d'aligner 4 de vos jetons avant votre adversaire(Horizontal, Vertical ou même diagonale).\n\x1B[0m");

	 // initialisation des joueurs et attribution des jetons

	 printf("\n");
	 printf(" Joueur 1, veuillez entrer votre nom: \n");
	 fgets(joueur1, sizeof(joueur1), stdin);
	 printf(" 21 jetons '\x1B[34mO\x1B[0m' sont prêts pour vous, %s\n", joueur1);
	 printf(" Joueur 2, veuillez entrer votre nom: \n");
	 fgets(joueur2, sizeof(joueur2), stdin);
	 printf(" 21 jetons '\x1B[31mX\x1B[0m' sont prêts pour vous, %s\n", joueur2);
	 printf("\t\x1B[32mEt c'est parti!! Pas besoin de chance, soyez juste stratège!!!\n\x1B[0m");

	 initialisationTableau();
	 while (true) {
		 if(alternanceJoueur == 1) {
			 symboleJoueur = symboleJoueur1;
		 }  else {
				symboleJoueur = symboleJoueur2;
			}
		column = entreeUtilisateur(alternanceJoueur);
		line = placerJetonLigne(column);
		RemplacerCase(line, column, symboleJoueur);
		if(alternanceJoueur == 1) {
			 alternanceJoueur = 2;
		} else {
			   	alternanceJoueur = 1;
		  }
		system("clear");
		initialisationTableau();

		if(verif_egalite() != 0 || success_player_1(column, line) == 0 || success_player_2(column, line) == 0) {
		   if(recommencerPartie() == 0) {
				 system("clear");
         return 0;
       }
       else {
       int i, j;
         for(i = 0; i < 6; i++) {
           for(j = 0; j < 7; j++) {
             tableau[i][j] = ' ';
           }
         }
       initialisationTableau();
       }
  	}
  }
}

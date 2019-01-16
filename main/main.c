#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "fonctions.h"
#include "interpreteRequeteSQL.h"
#include "recupereFichiers.h"

int main(int argc, char *argv[])
{
	int quit=0;
	printf("\n\n");
	printf(BLU"BBBBBBBBBBBBBBBBB  "RESET" DDDDDDDDDDDDD   "RED"   DDDDDDDDDDDDD  \n"RESET);      
	printf(BLU"B::::::::::::::::B "RESET" D::::::::::::DDD  "RED" D::::::::::::DDD  \n"RESET);   
	printf(BLU"B::::::BBBBBB:::::B "RESET"D:::::::::::::::DD"RED" D:::::::::::::::DD   \n"RESET);
	printf(BLU"BB:::::B     B:::::B"RESET"DDD:::::DDDDD:::::D"RED"DDD:::::DDDDD:::::D  \n"RESET);
	printf(BLU"  B::::B     B:::::B "RESET" D:::::D    D:::::D "RED"D:::::D    D:::::D \n"RESET);
	printf(BLU"  B::::B     B:::::B "RESET" D:::::D     D:::::D"RED"D:::::D     D:::::D\n"RESET);
	printf(BLU"  B::::BBBBBB:::::B  "RESET" D:::::D     D:::::D"RED"D:::::D     D:::::D\n"RESET);
	printf(BLU"  B:::::::::::::BB  "RESET"  D:::::D     D:::::D"RED"D:::::D     D:::::D\n"RESET);
	printf(BLU"  B::::BBBBBB:::::B  "RESET" D:::::D     D:::::D"RED"D:::::D     D:::::D\n"RESET);
	printf(BLU"  B::::B     B:::::B "RESET" D:::::D     D:::::D"RED"D:::::D     D:::::D\n"RESET);
	printf(BLU"  B::::B     B:::::B "RESET" D:::::D     D:::::D"RED"D:::::D     D:::::D\n"RESET);
	printf(BLU"  B::::B     B:::::B "RESET" D:::::D    D:::::D"RED" D:::::D    D:::::D \n"RESET);
	printf(BLU"BB:::::BBBBBB::::::B"RESET"DDD:::::DDDDD:::::D"RED"DDD:::::DDDDD:::::D  \n"RESET);
	printf(BLU"B:::::::::::::::::B "RESET"D:::::::::::::::DD"RED" D:::::::::::::::DD   \n"RESET);
	printf(BLU"B::::::::::::::::B  "RESET"D::::::::::::DDD  "RED" D::::::::::::DDD     \n"RESET);
	printf(BLU"BBBBBBBBBBBBBBBBB  "RESET" DDDDDDDDDDDDD    "RED"  DDDDDDDDDDDDD   \n\n\n"RESET);
	
	printf("Bonjour, bienvenue dans l'espace de gestion des bases de données. \n");
	do{
	
	printf("Entrez votre commande SQL : \n");

	//insertDonnee("membres", "nom", "laura");
	quit = interpreteRequeteSQL(); // interprête la requête sql
	}while(quit==0);
	
	
return 0;
}

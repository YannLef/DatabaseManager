#define RED   "\x1B[1;31m"
#define GRN   "\x1B[1;32m"
#define YEL   "\033[1;33m"
#define BLU   "\x1B[1;34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[1;36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef char chaine[200]; // temporaire : si le temps il faudrait faire des malloc en fonction du besoin !!!!!!!!!

/**
 * structure permettant de stocker des valeurs récupérées de la base de données, permet de gérer les différents types de données
 * */
typedef struct donnee{
	int type;
	
	int* entier;
	float* flottant;
	chaine* texte;
}donnee;

/**
 * structure contenant les chaines nécessaires aux requetes SQL : décomposition des données envoyé par l'utilisateur
 * 
 * */
typedef struct requeteSQL{
	chaine select;
	chaine nom_colonne;
	chaine from;
	chaine nom_table;
	chaine where;
	chaine conditionMembreGauche;
	chaine conditionOperateur;
	chaine conditionMembreDroite;
}requeteSQL;

typedef struct reponseSQL{
	donnee* d;
	chaine* c;
	int* e;
	int cpt;
}reponseSQL;





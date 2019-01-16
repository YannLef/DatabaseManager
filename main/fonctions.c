#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "fonctions.h"
#include "interpreteRequeteSQL.h"
#include "recupereFichiers.h"

/**
 * fonction permettant d'initialiser une donnee : passe tous les tableaux à NULL
 * */
donnee initDonnee(){
	donnee d; // Déclarer la structure donnée en variable locale
	
	d.type=-1;
	
	d.entier = NULL; // Initialise l'entier
	d.flottant = NULL; // Initialise le flottant
	d.texte = NULL; // Initialise la chaine
	
	return d; // Renvoi la structure initialisée
}

/**
 * fonction permettant de récupérer une donnée se trouvant dans un fichier à une ligne précise, quelle que soit son type grâce à la structure donnee
 * nomFichier : nom du fichier dans lequel on va chercher les données
 * ligne : tableau contenant les lignes à récupérer
 * nombreLigneValidees : le nombre de lignes vérifiant la condition
 * 
 * @param chaine nomFichier
 * @param int* ligne
 * @param int nombreLigneValidees
 * 
 * @return donnee
 * 
 * */
donnee getDonnee(chaine nomFichier, int* ligne, int nombreLigneValidees){
	donnee d;
	d = initDonnee(); // initialise la donnée
	printf("\n");
	printf(YEL "[Récupération Donnees]\n" RESET);
	printf("Ouverture du fichier %s.\n",nomFichier);
	FILE* fichier = fopen(nomFichier, "rt"); // tentative d'ouverture du fichier // commentaire concernant la tentative d'ouverture du fichier // commentaire de commentaire concernant la tentative d'ouverture du fichier
	if(fichier == NULL){
		perror("Erreur"); // affiche une erreur si le fichier ne parvient pas à être ouvert
	}else{
	
	fscanf(fichier, "%d\n", &(d.type)); // récupère le type de donnée
	
	// récupère la valeur du nombre d'éléments du fichier
	int nombreElements;
	fscanf(fichier, "%d\n", &nombreElements);
	//printf("nbElements : %d\n",nombreElements); // affiche le nombre d'éléments du fichier
	
	int z=0; // compteur pour indice de tableau de donnee
	
	int w; // variable inutile (utile pour l'offset)
	float x; // variable inutile (utile pour l'offset)
	chaine y; // variable inutile (utile pour l'offset)
	
		switch(d.type){
		case 1 : // <=> donnee = entier
			d.entier = (int*)malloc(sizeof(int)*nombreLigneValidees);
			
			break;
		case 2 : // <=> donnee = flottant
			d.flottant = (float*)malloc(sizeof(float)*nombreLigneValidees);
			
			break;
		case 3 : // <=> donnee = chaine
			d.texte = (chaine*)malloc(sizeof(chaine)*nombreLigneValidees);
			
			break;
	}
	int b=0; // variable spécifiant si la ligne actuelle est à prendre
	for(int i=1;i<=nombreElements;i++){ // boucle pour vérifier chaque ligne
		for(int a=0;a<nombreLigneValidees;a++){ // vérifie si la ligne correspond à n'importe laquelle des lignes à prendre
			if(i==ligne[a]) // vérifie si la ligne correspond à n'importe laquelle des lignes à prendre
				b=1; // passe b à 1 seulement si il faut prendre la ligne
			//printf("i: %d / ligne z : %d\n",i, ligne[a]); // vérification en temps réel des vérifications effectuées par le programme
			}
			
		if(b==1){ // si b=1 => si il faut prendre la ligne
			b=0; // on repasse b à 0 pour pouvoir s'en servir à nouveau
		printf("Recupération de la ligne %d\n",i);
		
		switch(d.type){
		case 1 : // <=> donnee = entier
			fscanf(fichier,"%d\n",&(d.entier[z])); // récuèpre l'entier présent sur la ligne
			break;
		case 2 : // <=> donnee = flottant
			fscanf(fichier,"%f\n",&(d.flottant[z])); // récuèpre le flottant présent sur la ligne
			break;
		case 3 : // <=> donnee = chaine
			fscanf(fichier,"%[^\n]\n",d.texte[z]); // récuèpre le texte présent sur la ligne
			break;
		}
		z++;
		}else{
		switch(d.type){
		case 1 : // <=> donnee = entier
			fscanf(fichier,"%d\n",&w); // récuèpre l'entier présent sur la ligne	
			break;
		case 2 : // <=> donnee = flottant
			fscanf(fichier,"%f\n",&x); // récuèpre le flottant présent sur la ligne
			break;
		case 3 : // <=> donnee = chaine
			fscanf(fichier,"%[^\n]\n",y); // récuèpre le texte présent sur la ligne
			break;
	}
			
			
		}
	}
	
	fclose(fichier); // ferme le fichier
	}
	return d; // renvoie la donnée
}

/**
 * fonction permettant de construire le nom d'un fichier à partir du nom de la table (dossier) et du nom de la colonne (nom fichier)
 * 
 * @param chaine* nomFichier
 * @param chaine nom_table
 * @param chaine nom_colonne
 * */
void getNomFichier(chaine* nomFichier, chaine nom_table, chaine nom_colonne){
	strcpy(*nomFichier,"");
	strcat(*nomFichier,nom_table);
	strcat(*nomFichier,"/");
	strcat(*nomFichier,nom_colonne);
	strcat(*nomFichier,".txt");
}


/**
 * fonction permettant de convertir n'importe quel type de donnée en chaine
 * donnee d est la donnée à convertir, chaine c la chaine qui recupère la donnée convertie, int i l'indice dans la donnée à convertir
 * 
 * @param donnee d
 * @param chaine c
 * @param int i
 * */
void convertiVersChaine(donnee d, chaine c, int i){ 
	
	switch(d.type){
		case 1 : // <=> donnee = entier
			sprintf(c,"%d",d.entier[i]);
			break;
		case 2 : // <=> donnee = flottant
			sprintf(c,"%f",d.flottant[i]);
			break;
		case 3 : // <=> donnee = chaine
			strcpy(c,d.texte[i]);
			break;
	}
}


/**
 * fonction permettant de créer un tableau et d'augementer sa taille en fonction du nombre de lignes validees
 * ancienneListe est le tableau initial. nouvelleLigne est le numero de la ligne a ajouter. nombreLignesValidees est le nombre de case supplémentaire
 * 
 * @param int* ancienneListe
 * @param int nouvelleLigne
 * @param nombreLignesValidees
 * */
void ajouteLigneValidee(int** ancienneListe, int nouvelleLigne, int nombreLignesValidees){
	
	
int* nouvelleListe=NULL; // déclare une nouvelle liste
	if(*ancienneListe == NULL){ // si la liste est vide..
		nouvelleListe = (int*)malloc(sizeof(int)); // on crée une nouvelle liste
		nouvelleListe[0] = nouvelleLigne; // on rajoute la ligne à la liste
	}else{
		nouvelleListe = (int*)malloc(sizeof(int)*nombreLignesValidees);
		for(int i=0;i<nombreLignesValidees-1;i++)
			nouvelleListe[i] = (*ancienneListe)[i]; // on recopie l'ancienne liste dans la nouvelle
		nouvelleListe[nombreLignesValidees-1] = nouvelleLigne; // on rajoute la ligne à la fin de la liste
		free(*ancienneListe); // libère l'ancienne liste
	}
	

*ancienneListe = nouvelleListe; // attribue la nouvelle liste à l'adresse de l'ancienne liste


}

/**
 * Cherche la ligne des fichiers à laquelle la condition de la reqûete sql est vérifiée
 * 
 * 
 * */
int* trouveLigneViaCondition(chaine condition, chaine nom_table, chaine nom_colonne, int* ligneValides){
	
	//int recupereEntier;
	int nombreLignes;
	chaine recupereChaine="init";
	donnee recupere;
	
	int *ReturnList = NULL;
	
	chaine nomFichier;
	
	getNomFichier(&nomFichier, nom_table, nom_colonne);
	printf("Ouverture du fichier %s.\n",nomFichier);
	
	
	
	FILE* fichier = fopen(nomFichier, "rt");
	
	if(fichier == NULL){
		perror("Erreur");
	}else{
	
	fscanf(fichier,"%d\n",&nombreLignes); // gère l'offset ( car première ligne du fichier indique le type, inutile ici)
	fscanf(fichier,"%d\n",&nombreLignes);
	
	printf("Recherche d'une ligne ou %s = %s .\n",nom_colonne, condition);
	
	int ligne[nombreLignes];
	for(int i=0;i<nombreLignes;i++)
		ligne[i]=i+1;
		//~ printf("%d\n",ligne[0]);
		//~ printf("%d\n",ligne[1]);
		//~ printf("%d\n",ligne[2]);
		//~ printf("%d\n",ligne[3]);
		//~ printf("%d\n",ligne[4]);
		//~ printf("%d\n",ligne[5]);
		
		recupere = getDonnee(nomFichier, ligne, nombreLignes); // recupere la valeur selon la ligne et peu importe son type
		printf("\n");
		//~ printf("%s\n",recupere.texte[0]);
		//~ printf("%s\n",recupere.texte[1]);
		//~ printf("%s\n",recupere.texte[2]);
		//~ printf("%s\n",recupere.texte[3]);
		//~ printf("%s\n",recupere.texte[4]);
		//~ printf("%s\n",recupere.texte[5]);
		
		printf(CYN "[Vérification Donnees]\n" RESET);
	for(int i=0;i<nombreLignes;i++) // test la condition sur chaque ligne
	{
		
		printf("Test de la ligne n°%d.. ",i+1);

		convertiVersChaine(recupere, recupereChaine, i); // converti cette valeur en chaine pour pouvoir effectuer des comparaisons dessus
		
		
		if(strcmp(recupereChaine,condition)==0 ) // compare la chaine récupérée avec la condition
		{
			(*ligneValides)++;
			ajouteLigneValidee(&ReturnList, i+1, *ligneValides);
			printf(GRN "Condition vérifiée ! \n" RESET);
			
		} else {
			printf(RED "Condition non vérifiée ! \n"RESET);
		}
	}

	fclose(fichier); // ferme le fichier
	}
	return ReturnList;
	

}


void recupereToutesLignes(int** ligne, int* lignesValides, chaine nom_table, chaine nom_colonne){
	
	// On construit le nom du fichier
	chaine nomFichier="";
	getNomFichier(&nomFichier, nom_table, nom_colonne);
	
	FILE* fichier = fopen(nomFichier,"rt"); // ouvre le fichier à étudier
	
	if(fichier == NULL){
		perror("Erreur"); // affiche une erreur si le fichier ne parvient pas à être ouvert
	}else{
		
	
	*lignesValides=0; // contiendra le nombre de lignes du fichier
	fscanf(fichier, "%d\n", lignesValides); // passe la première valeur du fichier (offset) car inutile dans ce ca là
	fscanf(fichier, "%d\n", lignesValides); // récupère le nombre de lignes du fichier
	
	*ligne = (int*) malloc(sizeof(int)**lignesValides); // On crée le tableau qui contiendra chaque lignes
	for(int i=0;i<*lignesValides;i++)
		(*ligne)[i]=i+1;
	
	
	fclose(fichier); // ferme le fichier
}
}

/**
 * Cette fonction permet d'inserer des données dans la table.
 * On crée un nouveau fichier, on copie l'ancienne fichier dans le nouveau en modifiant 
 * le nombre d'element puis on ajoute la nouvelle information
 * 
 * @param donnee d
 * @param chaine nomFichier
 * @param chaine info
 * 
 * */
void insertDonnee(chaine table, chaine nom_colonne, chaine info)
{
	
	donnee d;
	chaine nomFichier="";
	strcat(nomFichier,table);
	strcat(nomFichier,"/");
	strcat(nomFichier,nom_colonne);
	strcat(nomFichier,".txt");
	
	FILE *f = fopen(nomFichier, "rt"); //on ouvre le fichier contenant les données de l'utilisateur en lecture
	if(f==NULL)
	{
		perror("Erreur d'ouverture");
	}
	else
	{
		
		fscanf(f, "%d\n", &(d.type)); //on récupère le type du fichier
	
		int nombreElements;
		fscanf(f, "%d\n", &nombreElements); // on récupère le nombre d'element contenu dans le fichier
		char* T = (char*)malloc(sizeof(char)*10000); //on crée un tableau de la taille du nombre d'element
		
		chaine provisoire="";
		strcat(provisoire,table);
		strcat(provisoire,"/");
		strcat(provisoire,"Provisoire");
		
		FILE *fichier = fopen(provisoire, "wt"); //on crée un nouveau fichier temporaire
		if(fichier == NULL)
		{
			perror("Erreur d'ouverture 2 ");
		}
		else
		{
			int nouveau = nombreElements+1; //on augemente le nombre d'element du nouveau fichier
			fprintf(fichier, "%d\n", d.type); //on reecris le type du fichier dans le nouveau
			fprintf(fichier, "%d\n", nouveau); //on reécris le nombre d'element augementé de 1
			while(fgets(T, 1000,f) != NULL) //on récupère toutes les lignes du fichier tant qu'on  arrive pas a la fin du fichier
			{
				fprintf(fichier, "%s", T); //on reécris l'intégralité du fichier sans les deux premières lignes
			}
			
		}
		fclose(f);
		f=NULL;
		remove(nomFichier); //on supprime l'ancien fichier
		rename(provisoire, nomFichier); //on renomme le nouveau fichier avec le nom de l'ancien
		fclose(fichier);
		fichier=NULL;
		
		FILE *f = fopen(nomFichier, "at");
		if(f != NULL)
		{
			fprintf(f, "%s\n", info); //on ajoute l'information que l'utilisateur souhaite ajouter, a la fin du fichier.
			fclose(f);
			f=NULL;
		}
		
		free(T);
	}
}

void createTable(chaine nomTable, chaine* nomColonne, chaine* types, int nombreColonne){
	// Formule la commande
	chaine commande = "mkdir -p ";
	strcat(commande,nomTable);
	// Execute la commande
	system(commande);
	
	for(int i=0;i<nombreColonne;i++){ // Pour chaque colonne de la requête SQL
		chaine nomFichier="";
		strcat(nomFichier, nomTable);
		strcat(nomFichier,"/");
		strcat(nomFichier, nomColonne[i]);
		strcat(nomFichier,".txt");
		printf("%s\n",nomFichier);
		FILE* fichier = fopen(nomFichier,"wt");
		
		fprintf(fichier,"%s\n", types[i]); // spécifie le type de la colonne en première ligne du fichier
		fprintf(fichier,"0\n"); // spécifie le nombre de lignes du fichier (initialement 0)
		
		fclose(fichier);
	}
}

/**
 * Cette fonction permet de modifier des données dans la table en fonction
 * de ce que l'utilisateur rentre dans la requete SQL.
 * 
 * @param donne d
 * @param chaine NomFichier
 * @param chaine infoAChanger
 * @param chaine infoModif
 * 
 * */
void updateDonnee(chaine nomTable, chaine nom_colonne, chaine infoAChanger, chaine infoModif, chaine nom_colonne_condition)
{
	
				int ligneValides = 0;
					int *tableau = NULL; //tableau qui va ensuite contenir le retour de la fonction trouveLigne
			tableau = trouveLigneViaCondition(infoAChanger, nomTable, nom_colonne_condition, &ligneValides);
				
			if(ligneValides > 0){
	donnee d;

	int i = 1; //Compteur
	int k = 0; //Compteur
	
	chaine nomFichier="";
	strcat(nomFichier,nomTable);
	strcat(nomFichier,"/");
	strcat(nomFichier,nom_colonne);
	strcat(nomFichier,".txt");
	
	FILE *f = fopen(nomFichier, "rt"); //on ouvre le fichier en lecture seule
	if(f==NULL)
	{
		perror("Erreur d'ouverture");
	}
	else
	{
		fscanf(f, "%d\n", &(d.type)); //on récupère le type du fichier
	
		int nombreElements;
		fscanf(f, "%d\n", &nombreElements); // on récupère le nombre d'element contenu dans le fichier
		char* T = (char*)malloc(sizeof(char)*nombreElements); //on crée un tableau de la taille du nombre d'element
		
		chaine fichierProvisoire="";
		strcat(fichierProvisoire,nomTable);
		strcat(fichierProvisoire,"/");
		strcat(fichierProvisoire,"fichierProvisoire");
		
		FILE *fichier = fopen(fichierProvisoire, "wt"); //on crée un nouveau fichier temporaire
		if(fichier == NULL)
		{
			perror("Erreur d'ouverture 2 ");
		}
		else
		{
			fprintf(fichier, "%d\n", d.type); //on reecris le type du fichier dans le nouveau
			fprintf(fichier, "%d\n", nombreElements); //on reecirs le nombre d'elements du fichier
			

				while(fgets(T, 1000,f) != NULL) //on récupère toutes les lignes du fichier tant qu'on  arrive pas a la fin du fichier
				{
					

					
					if(i == tableau[k])
					{
						fprintf(fichier, "%s\n", infoModif);
						k++;
					}
					else
					{
						fprintf(fichier, "%s", T); //on reécris l'intégralité du fichier sans les deux premières lignes
						
					}
					i++;
				} 
			
		}
		fclose(f);
		chaine fichierASupprimer="";
		strcat(fichierASupprimer,nomTable);
		strcat(fichierASupprimer,nom_colonne);
		strcat(fichierASupprimer,"/");
		remove(fichierASupprimer); //on supprime l'ancien fichier
		rename(fichierProvisoire, nomFichier); //on renomme le nouveau fichier avec le nom de l'ancien
		fclose(fichier);
	}
}
}

/**
 * Cette fonction permet de modifier des données dans la table en fonction
 * de ce que l'utilisateur rentre dans la requete SQL.
 * 
 * @param donne d
 * @param chaine NomFichier
 * @param chaine infoAChanger
 * @param chaine infoModif
 * 
 * */
void updateDonneeSansConditions(chaine nomTable, chaine nom_colonne, chaine infoModif)
{
	printf("%s %s \n",nomTable, nom_colonne);
	donnee d;

	int i = 1; //Compteur
	int k = 0; //Compteur
	
	chaine nomFichier="";
	strcat(nomFichier,nomTable);
	strcat(nomFichier,"/");
	strcat(nomFichier,nom_colonne);
	strcat(nomFichier,".txt");
	
	FILE *f = fopen(nomFichier, "rt"); //on ouvre le fichier en lecture seule
	if(f==NULL)
	{
		perror("Erreur d'ouverture");
	}
	else
	{
		fscanf(f, "%d\n", &(d.type)); //on récupère le type du fichier
	
		int nombreElements;
		fscanf(f, "%d\n", &nombreElements); // on récupère le nombre d'element contenu dans le fichier
		char* T = (char*)malloc(sizeof(char)*nombreElements); //on crée un tableau de la taille du nombre d'element
		
		chaine fichierProvisoire="";
		strcat(fichierProvisoire,nomTable);
		strcat(fichierProvisoire,"/");
		strcat(fichierProvisoire,"fichierProvisoire");
		
		FILE *fichier = fopen(fichierProvisoire, "wt"); //on crée un nouveau fichier temporaire
		if(fichier == NULL)
		{
			perror("Erreur d'ouverture 2 ");
		}
		else
		{
			fprintf(fichier, "%d\n", d.type); //on reecris le type du fichier dans le nouveau
			fprintf(fichier, "%d\n", nombreElements); //on reecirs le nombre d'elements du fichier
			

				while(fgets(T, 1000,f) != NULL) //on récupère toutes les lignes du fichier tant qu'on  arrive pas a la fin du fichier
				{
					
						fprintf(fichier, "%s\n", infoModif);
						k++;
					i++;
				} 
			
		}
		fclose(f);
		chaine fichierASupprimer="";
		strcat(fichierASupprimer,nomTable);
		strcat(fichierASupprimer,nom_colonne);
		strcat(fichierASupprimer,"/");
		remove(fichierASupprimer); //on supprime l'ancien fichier
		rename(fichierProvisoire, nomFichier); //on renomme le nouveau fichier avec le nom de l'ancien
		fclose(fichier);
	}
}

void AfficheSeparateur(chaine nom_table, reponseSQL reponse, chaine nomColonne)
{
	int nbcol;
	chaine nomFichier="";
	strcat(nomFichier, nom_table);
	strcat(nomFichier,"/");
	strcat(nomFichier, nomColonne);
	strcat(nomFichier,".txt");
	
	nbcol = reponse.e[0];
	
	int tailleMax;
	tailleMax=determineTailleMax(reponse);
	
	int i;
	for(i=0; i<(nbcol*(tailleMax+2))+1; i++)
	{
		printf("-");
	}

		printf("\n");
	
	
}

void afficheTableau(reponseSQL reponse, chaine nom_table, chaine nom_colonne)
{
	if(reponse.d[0].entier != NULL || reponse.d[0].flottant != NULL || reponse.d[0].texte != NULL){ // SI un des tableaux est initialisés, on peut afficher les valeurs qu'il contient
		
	int tailleMax;
	chaine c;
	for(int k=0;k<reponse.cpt;k++)
	{
		AfficheSeparateur(nom_table, reponse, nom_colonne);
		
		tailleMax = determineTailleMax(reponse);
			if(reponse.d[k].entier != NULL)
			{
				for(int i=0;i<reponse.e[k];i++)
				{
					printf("| %d",reponse.d[k].entier[i]);
					sprintf(c,"%d", reponse.d[k].entier[i]);
					//~ printf("Taille max : %d \n", tailleMax);
					for(int l=0; l<tailleMax-strlen(c); l++)
					{
						printf(" ");
					}
				}
			}
			if(reponse.d[k].flottant != NULL)
			{
				for(int i=0;i<reponse.e[k];i++)
				{
					printf("| %f",reponse.d[k].flottant[i]);
					sprintf(c,"%f", reponse.d[k].flottant[i]);
					//~ printf("Taille max : %d \n", tailleMax);
					for(int l=0; l<tailleMax-strlen(c); l++)
					{
						printf(" ");
					}
				}
			}
			if(reponse.d[k].texte != NULL)
			{
				for(int i=0;i<reponse.e[k];i++)
				{
					printf("| %s",reponse.d[k].texte[i]);
					//~ printf("Taille max : %d \n", tailleMax);
					for(int l=0; l<tailleMax-strlen(reponse.d[k].texte[i]); l++)
					{
						printf(" ");
					}
				 }
			}
			printf("|");
			printf(BLU "  %s" RESET, reponse.c[k]);
			printf("\n");

	}
	AfficheSeparateur(nom_table, reponse, nom_colonne);

}
}

int determineTailleMax(reponseSQL reponse)
{
	int taille =0;
	chaine c = "";
	int MaxLocal = 0;
	
	for(int k=0; k<reponse.cpt; k++)
	{
		for(int i=0; i<reponse.e[k]; i++)
		{
			if(reponse.d[k].entier != NULL)
			{
				sprintf(c, "%d", reponse.d[k].entier[i]);
				taille = strlen(c);
				if(taille > MaxLocal)
				{
					MaxLocal = taille;
				}
			}
			
			if(reponse.d[k].flottant != NULL)
			{
				sprintf(c, "%f", reponse.d[k].flottant[i]);
				taille = strlen(c);
				if(taille > MaxLocal)
				{
					MaxLocal = taille;
				}
			}
			
			if(reponse.d[k].texte != NULL)
			{
				sprintf(c, "%s", reponse.d[k].texte[i]);
				taille = strlen(c);
				
				if(taille > MaxLocal)
				{
					MaxLocal = taille;
				}
			}
			
	
		}
	}
	return MaxLocal;
}

void delete(chaine nomTable, chaine nomColonne, chaine condition, int *tableau)
{
	donnee d;
	int i = 1;
	int k = 0;
	chaine vide = "";
	
	chaine nomFichier="";
	strcat(nomFichier, nomTable);
	strcat(nomFichier,"/");
	strcat(nomFichier, nomColonne);
	strcat(nomFichier,".txt");
	
	chaine fichierProvisoire="";
	strcat(fichierProvisoire, nomTable);
	strcat(fichierProvisoire,"/");
	strcat(fichierProvisoire,"Provisoire.txt");
	
	FILE *f = fopen(nomFichier, "rt"); //on ouvre le fichier en lecture seule
	if(f==NULL)
	{
		perror("Erreur d'ouverture");
	}
	else
	{
		fscanf(f, "%d\n", &(d.type)); //on récupère le type du fichier
		int nombreElements;
		fscanf(f, "%d\n", &nombreElements); // on récupère le nombre d'element contenu dans le fichier
		char* T = (char*)malloc(sizeof(char)*nombreElements); //on crée un tableau de la taille du nombre d'element
		FILE *fichier = fopen(fichierProvisoire, "wt"); //on crée un nouveau fichier temporaire
		if(fichier == NULL)
		{
			perror("Erreur d'ouverture du fichier provisoire ");
		}
		else
		{
			fprintf(fichier, "%d\n", d.type); //on reecris le type du fichier dans le nouveau
			int nouveauNombreElement = nombreElements-1;
			fprintf(fichier, "%d\n", nouveauNombreElement);
			while(fgets(T, 1000,f) != NULL) //on récupère toutes les lignes du fichier tant qu'on  arrive pas a la fin du fichier
			{
				int ligneValides = 0;
				if(i == tableau[k])
				{
					//~ fprintf(fichier, "%s\n", vide);
					k++;
					
				}
				else
				{
					fprintf(fichier, "%s", T); //on reécris l'intégralité du fichier sans les deux premières lignes
				}
				i++;
				
			}
		}
		fclose(f);
		remove(nomFichier); //on supprime l'ancien fichier
		rename(fichierProvisoire, nomFichier); //on renomme le nouveau fichier avec le nom de l'ancien
		fclose(fichier);
	}
	
}

void appelleDelete(chaine condition, chaine nomTable, chaine nomColonne)
{
	
	int lignesValides = 0;
	chaine *c; //chaine qui va contenir le nom de tout les fichiers
	chaine ch; //chaine inutile permettant de stocker le début du fichier nomsFichiers
	int compteur = 0; //compteur du nombre de fichiers
	c = recupereToutFichier(nomTable); //on récupère tout les fichiers de la table concercnée
	int *T = NULL;
	T = trouveLigneViaCondition(condition, nomTable, nomColonne, &lignesValides); //on récupère les lignes correponsdantes a la condition
	
	//compteur
	FILE *f = fopen("nomsFichiers","rt");
	if(f == NULL)
	{
		printf("ERREUR\n");
	}
	while(feof(f) == 0)
	{
		fscanf(f,"%[^\n]\n",ch);
		compteur++;
	}
	fclose(f);
	compteur = compteur-1;
	
	//appel a delete pour tout les fichiers
	for(int i=0; i<compteur; i++)
	{
		delete(nomTable, c[i], condition, T);
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "fonctions.h"
#include "interpreteRequeteSQL.h"
#include "recupereFichiers.h"

void recupereToutFichiersSansCondition(chaine param, reponseSQL* reponse)
{
		int i = 0;
		chaine *T = (chaine*)malloc(sizeof(chaine)*50);
		// Formule la commande
		chaine commande = "ls ./";
		strcat(commande, param);
		strcat(commande," -lt>nomsFichiers");
		// Execute la commande
		system(commande);
					
		// Ouvre le fichier contenant le résultat de la commande ls exécutée précedement
		chaine nomFichier="nomsFichiers";
		FILE* fichier = fopen(nomFichier,"rt");
		
	
		chaine nom=""; // Stockera le nom des fichiers une fois récupéres
	
		fscanf(fichier,"%[^\n]",nom); // passe la première ligne du fichier
		

		
		while(feof(fichier) == 0){ // Boucle jusqu'à ce que la fin du fichier soit atteinte
			
			// Pour chaque ligne on passe les 8 premiers termes (inutiles pour nous) renvoyés par la commande système.
			for(int i=0;i<8;i++)
				fscanf(fichier, "%s ", nom);
				
					

			fscanf(fichier, "%[^.]", nom); // On récupère le dernier terme de chaque ligne qui correspond au nom de fichier.
			strcpy(T[i], nom);
			
			
			chaine c;
			fscanf(fichier,"%[^\n]\n",c); // passe la fin de la ligne car inutile (.txt)
	
			
			
			chaine nom1="";
			strcpy(nom1,param);
			strcat(nom1,"/");
			strcat(nom1,nom);
			strcat(nom1,".txt");
			
			
			
			
			int ligneValides=0;
			int* ligne=NULL;
			recupereToutesLignes(&ligne, &ligneValides, param , T[i]);
			
							
				if(ligne!=NULL){
				
				donnee data = getDonnee(nom1, ligne, ligneValides);
				(*reponse).d[(*reponse).cpt]=data;
				(*reponse).e[(*reponse).cpt]=ligneValides;
				strcpy((*reponse).c[(*reponse).cpt],nom);
				(*reponse).cpt++;
				
				}
			}
			fclose(fichier);					
		}
		
void recupereToutFichiersAvecCondition(chaine param1, chaine param2, chaine param3, reponseSQL* reponse)
{
	int i = 0;
		chaine *T = (chaine*)malloc(sizeof(chaine)*50);
		// Formule la commande
		chaine commande = "ls ./";
		strcat(commande, param1);
		strcat(commande," -lt>nomsFichiers");
		// Execute la commande
		system(commande);
					
		// Ouvre le fichier contenant le résultat de la commande ls exécutée précedement
		chaine nomFichier="nomsFichiers";
		FILE* fichier = fopen(nomFichier,"rt");
		
	
		chaine nom=""; // Stockera le nom des fichiers une fois récupéres
	
		fscanf(fichier,"%[^\n]",nom); // passe la première ligne du fichier
		

		
		while(feof(fichier) == 0){ // Boucle jusqu'à ce que la fin du fichier soit atteinte
			
			// Pour chaque ligne on passe les 8 premiers termes (inutiles pour nous) renvoyés par la commande système.
			for(int i=0;i<8;i++)
				fscanf(fichier, "%s ", nom);
				
					

			fscanf(fichier, "%[^.]", nom); // On récupère le dernier terme de chaque ligne qui correspond au nom de fichier.
			strcpy(T[i], nom);
											
			chaine c;
			fscanf(fichier,"%[^\n]\n",c); // passe la fin de la ligne car inutile (.txt)
	
			
			
			chaine nom1="";
			strcpy(nom1,param1);
			strcat(nom1,"/");
			strcat(nom1,nom);
			strcat(nom1,".txt");
			
			
			
			
			int ligneValides=0;
			int* ligne = trouveLigneViaCondition(param2, param1, param3, &ligneValides);
			
			
							
				if(ligne!=NULL){
				
				donnee data = getDonnee(nom1, ligne, ligneValides);
				(*reponse).d[(*reponse).cpt]=data;
				(*reponse).e[(*reponse).cpt]=ligneValides;
				strcpy((*reponse).c[(*reponse).cpt],nom);
				(*reponse).cpt++;
						
				}
			}
			fclose(fichier);					
		}
		
chaine* recupereToutFichier(chaine param)
{
		int i = 0;
		chaine *T = (chaine*)malloc(sizeof(chaine)*50);
		// Formule la commande
		chaine commande = "ls ./";
		strcat(commande, param);
		strcat(commande," -lt>nomsFichiers");
		// Execute la commande
		system(commande);
					
		// Ouvre le fichier contenant le résultat de la commande ls exécutée précedement
		chaine nomFichier="nomsFichiers";
		FILE* fichier = fopen(nomFichier,"rt");
		
	
		chaine nom=""; // Stockera le nom des fichiers une fois récupéres
	
		fscanf(fichier,"%[^\n]",nom); // passe la première ligne du fichier
		

		
		while(feof(fichier) == 0){ // Boucle jusqu'à ce que la fin du fichier soit atteinte
			
			// Pour chaque ligne on passe les 8 premiers termes (inutiles pour nous) renvoyés par la commande système.
			for(int i=0;i<8;i++)
				fscanf(fichier, "%s ", nom);
				
					

			fscanf(fichier, "%[^.]", nom); // On récupère le dernier terme de chaque ligne qui correspond au nom de fichier.
			strcpy(T[i], nom);
			i++;
			
			
			
			chaine c;
			fscanf(fichier,"%[^\n]\n",c); // passe la fin de la ligne car inutile (.txt)
	
			
			
			chaine nom1="";
			strcpy(nom1,param);
			strcat(nom1,"/");
			strcat(nom1,nom);
			strcat(nom1,".txt");
			
		
		}
	
		
		return T;
}

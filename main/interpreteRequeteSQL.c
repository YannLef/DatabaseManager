#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "fonctions.h"
#include "interpreteRequeteSQL.h"
#include "recupereFichiers.h"

int interpreteRequeteSQL(){
	reponseSQL reponse;
	reponse.d = (donnee*)malloc(sizeof(donnee)*100);
	reponse.c = (chaine*)malloc(sizeof(chaine)*100);
	reponse.e = (int*)malloc(sizeof(int)*100);
	reponse.cpt=0;
	
	chaine param[20]; // le tableau contenant les paramètres de la requete sql
	int k=0; // k le nombre d'éléments de la ligne de commande

scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
	if(strcmp(param[0],"SELECT") == 0){ // Si le premier paramètre est SELECT
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
		if(strcmp(param[1],"*") == 0){ // Si le second paramètre est *, toutes les colonnes doivent être selectionnees
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
			if(strcmp(param[2],"FROM") == 0){ // Si le troisième paramètre est FROM, tout va bien car il faut spécifier la table dans laquelle chercher
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
				if(strcmp(param[3],";") == 0){ // Si on ferme la requete sql sans avoir rien mis après FROM
					printf(RED "Requête SQL invalide\n" RESET);
				}else{
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
					if(strcmp(param[4],";") == 0){ // Si le cinquième paramètre est ; on sait que la requête SQL se termine ici et qu'il n'y a pas de condition de recherche
						
						recupereToutFichiersSansCondition(param[3], &reponse);
							printf("\n");
	afficheTableau(reponse, param[3], "nom");
						
					}else if(strcmp(param[4],"WHERE") == 0){ // Si le cinquième element est WHERE, on attend une condition
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
						if(strcmp(param[5],";") == 0){ // Si le sixième élément est ; -> on a pas notre condition, il y a donc une erreur
							printf(RED "Requête SQL invalide\n" RESET);
						}else{ // Si le sixième élément n'est pas ; -> on a l'élément de gauche de notre condition
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
							if(strcmp(param[6],";") == 0){ // Si le septième élément est ; -> on a pas notre condition, il y a donc une erreur
								printf(RED "Requête SQL invalide\n" RESET);
							}else{ // Si le septième élément n'est pas ; -> on a l'opérateur de notre condition
								if(strcmp(param[6],"=") == 0){ // Si le septième élément est = -> on a un opérateur valide car les autres ne sont pas encore gérés
scanf(" '%[^']'",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
									if(strcmp(param[7],";") == 0){ // Si le huitième paramètre est ; -> il nous manque l'élément de droite de la condition, il y a donc une erreur
										printf(RED "Requête SQL invalide\n" RESET);
									}else{ // Si le huitième paramètre n'est pas ; -> on a l'élément de droite de la condition
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
										if(strcmp(param[8],";") == 0){ // Si le neuvième élément est ; -> On peut exécuter la requete avec notre unique condition
											
											recupereToutFichiersAvecCondition(param[3], param[7], param[5], &reponse);
												printf("\n");
	afficheTableau(reponse, param[3], "nom");
											
											
										}else{ // Si le neuvième élément n'est pas ; -> on attend d'autres conditions / PAS GERE PAR NOTRE PROGRAMME DONC ON AFFICHE UNE ERREUR
											printf(RED "Requête SQL invalide\n" RESET);
										}
									}
								}else{ // Si l'opérateur de la condition est différent de =, on ne sait aps encore le gérer... il y a donc une erreur
									printf(RED "Requête SQL invalide\n" RESET);
								}
							}
						}
					}else{ // Si le cinquième paramètre n'est ni ; ni WHERE, alors il y a une erreur
						printf(RED "Requête SQL invalide\n" RESET);
					}
				}
			}else{ // Si le troisième element n'est pas FROM, alors la requete SQL est erronée
				printf(RED "Requête SQL invalide\n" RESET);
			}
		}else if(strcmp(param[1],";") == 0){ // si le deuxième paramètre est un ; -> on a pas assez d'infos pour renvoyer des données
			printf(RED "Requête SQL invalide\n" RESET);
		}else{ // Si le second paramètre n'est pas * et pas ; -> alors une seule colonne doit être selectionne
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
			if(strcmp(param[2],"FROM") == 0){
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
				if(strcmp(param[3],";") == 0){ // Si on ferme la requete sql sans avoir rien mis après FROM
					printf(RED "Requête SQL invalide\n" RESET);
				}else{
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
					if(strcmp(param[4],";") == 0){ // Si le cinquième paramètre est ; on sait que la requête SQL se termine ici et qu'il n'y a pas de condition de recherche
						chaine nomFichier2;
						getNomFichier(&nomFichier2, param[3], param[1]);
						
						int ligneValides=0;
						int* ligne=NULL;
						recupereToutesLignes(&ligne, &ligneValides, param[3], param[1]);
						
						if(ligne!=NULL){
						
						donnee data = getDonnee(nomFichier2, ligne, ligneValides);
						reponse.d[reponse.cpt]=data;
						reponse.e[reponse.cpt]=ligneValides;
						strcpy(reponse.c[reponse.cpt],param[1]);
						reponse.cpt++;
							printf("\n");
	afficheTableau(reponse, param[3], "nom");
								
						}
					}else if(strcmp(param[4],"WHERE") == 0){
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
						if(strcmp(param[5],";") == 0){ // Si le sixième élément est ; -> on a pas notre condition, il y a donc une erreur
							printf(RED "Requête SQL invalide\n" RESET);
						}else{ // Si le sixième élément n'est pas ; -> on a l'élément de gauche de notre condition
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
							if(strcmp(param[6],";") == 0){ // Si le septième élément est ; -> on a pas notre condition, il y a donc une erreur
								printf(RED "Requête SQL invalide\n" RESET);
							}else{ // Si le septième élément n'est pas ; -> on a l'opérateur de notre condition
								if(strcmp(param[6],"=") == 0){ // Si le septième élément est = -> on a un opérateur valide car les autres ne sont pas encore gérés
scanf(" '%[^']'",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
									if(strcmp(param[7],";") == 0){ // Si le huitième paramètre est ; -> il nous manque l'élément de droite de la condition, il y a donc une erreur
										printf(RED "Requête SQL invalide\n" RESET);
									}else{ // Si le huitième paramètre n'est pas ; -> on a l'élément de droite de la condition
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
										if(strcmp(param[8],";") == 0){ // Si le neuvième élément est ; -> On peut exécuter la requete avec notre unique condition
											// EXECUTION
											chaine nomFichier;
											getNomFichier(&nomFichier, param[3], param[1]);
											
											int ligneValides=0;
											int* ligne = trouveLigneViaCondition(param[7], param[3], param[5], &ligneValides);
											
											if(ligne!=NULL){
											
											donnee data = getDonnee(nomFichier, ligne, ligneValides);
											reponse.d[reponse.cpt]=data;
											reponse.e[reponse.cpt]=ligneValides;
											strcpy(reponse.c[reponse.cpt],param[1]);
											reponse.cpt++;
												printf("\n");
	afficheTableau(reponse, param[3], "nom");
											}
										}else{
											printf(RED "Requête SQL invalide\n" RESET);
										}
									}
								}
							}
						}
					}else{ // Si le cinquième paramètre n'est ni ; ni WHERE, alors il y a une erreur
						printf(RED "Requête SQL invalide\n" RESET);
					}
				}
			}else{ // Si le troisième element n'est pas FROM, alors la requete SQL est erronée
				printf(RED "Requête SQL invalide\n" RESET);
			}
		}
	}else if(strcmp(param[0],"CREATE") == 0){ // Si le premier paramètre est INSERT
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
		if(strcmp(param[1],"TABLE") == 0){ // Si le deuxième paramètre est TABLE, tout se déroule comme prévu
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
			if(strcmp(param[2],";") == 0){ // Si le troisème paramètre est ; -> Fin de requête inattendu
				printf(RED "Requête SQL invalide\n" RESET);
			}else{ // Si le troisième élément n'est pas ; -> on a le nom de la table à créer
				chaine nomColonne[20];
				chaine types[20];
				int nombreColonne=0;
				while(1){
// Récupère le type de la colonne
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
					if(strcmp(param[k-1],";") == 0) // Si une des deux lignes saisies ( [type] ou [nom_colonne] ) est un ; -> alors on annule les deux
						break;

// Récupère le nom de la colonne
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
					if(strcmp(param[k-1],";") == 0) // Si une des deux lignes saisies ( [type] ou [nom_colonne] ) est un ; -> alors on annule les deux
						break;
						
					strcpy(nomColonne[nombreColonne],param[k-1]); // le deuxième paramètre saisi est le nom de la colonne
					
					// le premier paramètre saisi est le type de donnée, ici on le traduit car il est matérialisé par un simple nombre dans nos fichiers.
					if(strcmp(param[k-2],"int") == 0){
						strcpy(types[nombreColonne],"1");
					}else
					if(strcmp(param[k-2],"float") == 0){
						strcpy(types[nombreColonne],"2");
					}else
					if(strcmp(param[k-2],"text") == 0){
						strcpy(types[nombreColonne],"3");
					}else{
						printf(RED "Type de donnée pour %s invalide\n" RESET, param[k-1]);
					}
						
					if(strcmp(param[k-2],"int") == 0 || strcmp(param[k-2],"float") == 0 || strcmp(param[k-2],"text") == 0){
						nombreColonne++; // à chaque saisie on augmenter
						createTable(param[2], nomColonne, types, nombreColonne); // On appelle la fonction crate table pour créer la table en fonction des paramètres
					}
				}
			}
		}else{ // Si le deuxième paramètre n'est pas table alors que le premier paramètre est CREATE, il y a une erreur
			printf(RED "Requête SQL invalide\n" RESET);
		}
	}else if(strcmp(param[0],"INSERT") == 0){ // Si le premier paramètre est INSERT
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
		if(strcmp(param[1],"INTO") == 0){ // Si le deuxième paramètre est INTO, il n'y a pas de problèmes
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
			if(strcmp(param[2],";") == 0){ // Si le troisième paramètre est ; -> la requête est incomplète, il y a une erreur
				printf(RED "Requête SQL invalide : ';' inattendu\n" RESET);
			}else{ // Si le troisième paramètre n'est pas ; -> il n'y a pas de problème et on a le nom de la table
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;
				if(strcmp(param[3],"VALUES") == 0){ // Si le quatrième élément est VALUES, il n'y a pas de problèmes
					
					while(1){
scanf("%s",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;

if(strcmp(param[k-1],";") == 0){ // Si une des deux lignes saisies ( [type] ou [nom_colonne] ) est un ; -> alors on annule les deux
	k=k-1;
	break;
}

scanf(" '%[^']'",param[k]); // on recupere les elements saisis
//printf("%d %s\n",k,param[k]);
k++;

if(strcmp(param[k-1],";") == 0){ // Si une des deux lignes saisies ( [type] ou [nom_colonne] ) est un ; -> alors on annule les deux
	k=k-2;
	break;
}
	
				
					}
					
					FILE *f = fopen("nomsFichiers","rt");
					
	if(f == NULL)
	{
		printf("ERREUR\n");
	}
	int compteur=0; // pour avoir le nombre de fichiers/colonnes de la table
	chaine c;
	while(feof(f) == 0)
	{
		
		
		fscanf(f,"%[^\n]\n",c);
		
		compteur++;
	
		
	}
	compteur = compteur-1;
	fclose(f);
					chaine* toutFichiers=recupereToutFichier(param[2]);
					int* utilise = (int*)malloc(sizeof(int)*compteur); // A FREEEEEE
					for(int i=0;i<compteur;i++)
						utilise[i]=0;
					
					int valide = 1;
					int cpt=0;
					
					for(int z=4;z<k;z=z+2){ // z = 4 car de base on a dejà INSERT INTO table VALUES ( 0,1,2,3)
						cpt++;
						for(int w=0;w<compteur;w++){
							if(strcmp(param[z],toutFichiers[w])==0){
								if(utilise[w]==0){
									utilise[w]=1;
									//printf("w %d utilise %d\n",w,utilise[w]);
								}else{
									valide=0;
									printf("déjà utilisé !\n");
								}
							}

						}
					}
					
					if(cpt!=compteur){
						valide=0;
						printf("Pas le bon nombre de param: param:%d attendu:%d\n",cpt,compteur); // param le nombre de params et attendu le nombre de colonnes/fichiers
					}
					
					if(valide==1){
						for(int z=4;z<k-1;z=z+2){
							
							insertDonnee(param[2], param[z], param[z+1]);
						}
						//~ insertDonnee("membres", "nom", "laura");
					}
					

				}else{
					printf(RED "Requête SQL invalide : 'VALUES' attendu\n" RESET);
				}
			}
		}else{ //Si le deuxième paramètre n'est pas INTO, il y a une erreur
			printf(RED "Requête SQL invalide : 'INTO' attendu en second paramètre\n" RESET);
		}
	}else if(strcmp(param[0],"DELETE") == 0){ // Si le premier paramètre est DELETE
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;		
		if(strcmp(param[1],"FROM") == 0){ // Si le deuxième paramètre est FROM -> tout se déroule comme prévu
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
			if(strcmp(param[2],";") == 0){ // Si le troisième paramètre est ; -> la requete sql n'est pas finie, il y a une erreur
				printf(RED "Requête SQL invalide : fin inattendu\n" RESET);
			}else{ // Si le troisième paramètre n'est pas ; -> tout se déroule comme prévu, on a le nom de la table 
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
				if(strcmp(param[3],"WHERE") == 0){ // Si le quatrième paramètre est WHERE -> tout se déroule comme prévu (obligatoire car on a pas codé la version sans condition)
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
					if(strcmp(param[4],";") == 0){ // Si le cinquième paramètre est ; -> la requete sql n'est pas finie, il y a une erreur
						printf(RED "Requête SQL invalide : fin inattendu\n" RESET);
					}else{ // Si le cinquième paramètre n'est pas ; -> tout se déroule comme prévu, on a la colonne pour la condition
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
						if(strcmp(param[5],"=") == 0){ // Si le sixième paramètre est = -> tout se passe comme prévu, on a l'opération
scanf(" '%[^']'",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
							if(strcmp(param[6],";") == 0){ // Si le septième paramètre est ; -> la requete sql n'est pas finie, il y a une erreur
								printf(RED "Requête SQL invalide : fin inattendu\n" RESET);
							}else{ // Si le septième paramètre n'est pas ; -> tout se passe bien, on a la valeur de la condition
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
								if(strcmp(param[7],";") == 0){ // Si le huitième paramètre est ; -> la requete sql est pas finie
									appelleDelete(param[6],param[2],param[4]);
								}else{
									printf(RED "Requête SQL invalide : ; attendu à la fin\n" RESET);
								}
							}
						}else{ // Si le sixième paramètre n'est pas = -> il y a un problème ( seul = est pris en compte pour le moment)
							printf(RED "Requête SQL invalide : '=' attendu\n" RESET);
						}
					}
				}else{ // Si le quatrième paramètre n'est pas WHERE -> il y a une erreur
					printf(RED "Requête SQL invalide : 'WHERE' attendu\n" RESET);
				}
			}
		}else{ // Si le deuxième paramètre n'est pas FROM -> il y a un problème
			printf(RED "Requête SQL invalide : 'FROM' attendu\n" RESET);
		}
			
	}else if(strcmp(param[0],"UPDATE") == 0){ // Si le premier paramètre est UPDATE
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
		if(strcmp(param[1],";") == 0){ // Si le deuxième paramètre est ; -> la requete sql n'est pas finie, il y a erreur
			printf(RED "Requête SQL invalide\n" RESET);
		}else{ // si le deuxième param n'est pas ; -> on a le nom de la table à modifier
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
			if(strcmp(param[2],"SET") == 0){ // Si le troisième élément est SET, tout va bien
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
				if(strcmp(param[3],";") == 0){ // Si le quatrième élément est ; -> fin de requete inattendu, erreur
					printf(RED "Requête SQL invalide\n" RESET);
				}else{ // Si le quatrième élément n'est pas ; -> alors on a le nom de la colonne à éditer
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
					if(strcmp(param[4],"=") == 0){ // Si le cinquième élément est =, tout va bien
scanf(" '%[^']'",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;

scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
						if(strcmp(param[6],";") == 0){ // Si le septième élément est ; -> on arrête la requete SQL, on a pas de condition
							updateDonneeSansConditions(param[1], param[3], param[5]);
						} else if(strcmp(param[6],"WHERE") == 0){ // Si le septième élément est WHERE, la condition se déroule sans problèmes
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
							if(strcmp(param[7],";") == 0){ // Si le huitième élément est ; -> la condition est incomplète, il y a erreur
								printf(RED "Requête SQL invalide\n" RESET);
							}else{ // Si le huitième élément n'est pas ; -> la condition se déroule normalement et on a le nom de la colonne à tester
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
								if(strcmp(param[8],"=") == 0){ // si le neuvième élement est =, la condition se déroule normalement
scanf(" '%[^']'",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
									if(strcmp(param[9],";") == 0){ // si le dixième paramètre est ; -> fin de requete inattendu, il y a erreur
										printf(RED "Requête SQL invalide\n" RESET);
									}else{ // si le dixième paramètre n'est pas ; -> la condition se déroule normalement, on a le membre de droite de la condition
scanf("%s",param[k]); // on recupere les elements saisis
//~ printf("%d %s\n",k,param[k]);
k++;
										if(strcmp(param[10],";") == 0){ // Si le onzième paramètre est ; -> la requete est terminée et peut être envoyée
											updateDonnee(param[1], param[3], param[9], param[5],param[7]);
										}else{ // Si le onzième paramètre n'est pas ; -> il y a une erreur car la condition est censé être finie
											printf(RED "Requête SQL invalide\n" RESET);
										}
									}
								}else{
									printf(RED "Requête SQL invalide\n" RESET);
								}
							}
						}else{ // Si le septième élément n'est ni ; ni WHERE, alors il y a un problème
							printf(RED "Requête SQL invalide\n" RESET);
						}
					}else{
						printf(RED "Requête SQL invalide\n" RESET);
					}
				}
			}else{ // Si le troisième paramètre n'est pas SET, il y a une erreur
				printf(RED "Requête SQL invalide\n" RESET);
			}
		}
	}else if(strcmp(param[0],"quit") == 0){ // Si le premier paramètre est quit -> commande pour quitter
				char confirmQuit;
				printf("Voulez-vous vraiment quitter (y/n) ?\n");
				while(confirmQuit != 'y' && confirmQuit != 'n'){
					
					scanf("%c",&confirmQuit);
				}
				
				if(confirmQuit == 'y')
					return 1;
	}else if(strcmp(param[0],"help") == 0){ // Si le premier paramètre est help -> commande pour afficher l'aide
				printf("\n");
				printf("Aide et fonctionnalités :\n\n" RESET);
				
				printf(GRN "[SELECTION DES DONNEES]\n" RESET);
				printf("Pour selectionner toutes les données d'une table, sans condition : SELECT * FROM <nom_table> ; \n");
				printf("Pour selectionner toutes les données d'une table, avec condition : SELECT * FROM <nom_table> WHERE <nom_colonne_condition> = <valeur_condition> ; \n");
				printf("Pour selectionner certaines données d'une table, sans condition : SELECT <nom_colonne> FROM <nom_table> ; \n");
				printf("Pour selectionner certaines données d'une table, avec condition : SELECT <nom_colonne> FROM <nom_table> WHERE <nom_colonne_condition> = <valeur_condition> ; \n\n");
				
				printf(GRN "[CREATION DE TABLES]\n" RESET);
				printf("Pour créer une table : CREATE TABLE <nom_table> <type_donnee_colonne1> <nom_colonne1> <type_donnee_colonne2> <nom_colonne2> ... ; \n\n");
				
				printf(GRN "[MODIFICATION DES DONNEES]\n" RESET);
				printf("Pour modifier une donnée d'une table, sans condition : UPDATE <nom_table> SET <nom_colonne> = <'nouvelle_valeur'> ; \n");
				printf("Pour modifier une donnée d'une table, avec condition : UPDATE <nom_table> SET <nom_colonne> = <'nouvelle_valeur'> WHERE <nom_colonne_condition> = <'valeur_condition'> ; \n\n");
				
				printf(GRN "[AJOUT DES DONNEES]\n" RESET);
				printf("Pour ajouter des données a une table : INSERT INTO <nom_table> VALUES <nom_colonne1> <valeur1> <nom_colonne2> <valeur2> ... ; \n\n");
				// INSERT INTO membres VALUES nom 'test' id '42' age '42' nationnalite 'test' ;
				
				printf(GRN "[SUPPRESSION DES DONNEES]\n" RESET);
				printf("Pour supprimer une ligne d'une table : DELETE FROM <nom_table> WHERE <nom_colonne_condition> = <'valeur_condition'> ; \n\n");
				
	}else{ // Si le premier paramètre n'est pas SELECT, INSERT, DELETE, UPDATE etc.. alors la requete SQL est erronée
		printf(RED "Requête SQL invalide\n" RESET);
	}
	

	return 0;
}

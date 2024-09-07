#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>
#include <errno.h>

typedef struct {char* eti; int ligne;} etiq;
typedef struct {char* motclef; char* donnee;} instruction; 
typedef struct {int code; int donnee;} instructionNumerique;

#define couleur(param) printf("\033[%sm",param) /* Permet d'avoir un affichage particulier du texte écrit dans le terminal. J'ai appellé cela couleur mais elle n'est pas uniquement lié à des fonctionnalités de couleur mais permet aussi de mettre en gras du texte */

void AffichageEtiquette(etiq* etic){
	printf("C'est l'étiquette %s correspondant à la ligne %d\n",(*etic).eti,(*etic).ligne);
	}
	
void AffichageInstruction(instruction* instr){
	printf("L'instruction est de mot clef : %s et de donnée : %s\n",instr->motclef,instr->donnee);
	}
	
void AffichageInstructionNum(instructionNumerique* instr){
	printf("L'instruction est de mot clef : %d et de donnée : %d\n",instr->code,instr->donnee);
	}

void libereEtiquette(etiq* p){
	free(p->eti);
	free(p);
	}

void libereInstruction(instruction* p){
	free(p->motclef);
	free(p->donnee);
	free(p);
	}

void annonceErreur(){
	couleur("31"); couleur("1"); /* Couleur rouge / Gras */
	printf("Erreur : ");
	couleur("0"); 
	}
	
void afficheLigne(char* nomfichier,int numligne){
	char* ch = malloc(sizeof(char)*100); 
	sprintf(ch,"head -%d %s | tail -%d",numligne,nomfichier,1); /* récupère la ligne où se situe l'erreur */
	FILE* Frecup = popen(ch,"r");
	free(ch);
	while (!(feof(Frecup))){
		char c = fgetc(Frecup);
		if (c == '\n') break;
		printf("%c",c);
		}
	pclose(Frecup);	
	printf("\n");
	}
	
void afficheErreurSyntaxeEti(char* nomfichier, int numligne){
	char* ch = malloc(sizeof(char)*100); 
	sprintf(ch,"head -%d %s | tail -%d",numligne,nomfichier,1);
	FILE* Frecup = popen(ch,"r");
	free(ch);
	couleur("35");
	while (!(feof(Frecup))){
		char c = fgetc(Frecup);
		if (c == '\n') break;
		else if (c == ':') couleur("0");
		printf("%c",c);
		}
	pclose(Frecup);
	printf("\n");
	}
	
void affichageEtiIdentique(char* etiquetteCommune, int nbLigne1, int nbLigne2, char* nomfichier){
	int nbLigneCourant = nbLigne1;
	for(int i = 0; i < 2; i++){
		char* ch = malloc(sizeof(char)*100); 
		sprintf(ch,"head -%d %s | tail -%d",nbLigneCourant,nomfichier,1);
		FILE* Frecup = popen(ch,"r");
		free(ch);
		couleur("35");
		while (!(feof(Frecup))){
			char c = fgetc(Frecup);
			if (c == '\n') break;
			else if (c == ':') couleur("0");
			printf("%c",c);
			}
		printf("\n");
		pclose(Frecup);
		nbLigneCourant = nbLigne2;	
		}
	printf("\n");
	}
	
void afficheErreurDonneeLigne(char* ligne){ /* indiceBlocDonnee ne prends pas en compte le bloc étiquette c'est l'indice dans la chaîne sans étiquette */
	int i = 0;
	while (ligne[i] != '\0'){
		if (ligne[i] == ' ') couleur("35");
		printf("%c",ligne[i]);
		i++;
		}
	printf("\n\n");
	couleur("0");
	}
	
void afficheErreurMotClef(char* ligne){ /* indiceBlocDonnee ne prends pas en compte le bloc étiquette c'est l'indice dans la chaîne sans étiquette */
	int i = 0;
	couleur("35");
	while (ligne[i] != '\0'){
		if (ligne[i] == ' ') couleur("0");
		printf("%c",ligne[i]);
		i++;
		}
	printf("\n\n");
	}
	
int verifEtiquette(char BUFF[], char* p){
	if (p == NULL) return 0; /* Pas d'étiquette on peut sortir directement du programme*/
	int i  = 0;
	if ((BUFF[0] == ':')||((BUFF[0] >= '0')&&(BUFF[0] <= '9'))){ /* Si le premier caractère est ":" ou un caractère numérique (entre 0 et 9) on renvoie un code erreur directement */
		return -1;
		}
	while (BUFF[i] != ':'){ /* On sait qu'on a au moins un caractère (non numérique) et on vérifie simplement que chaque caractère précédent le ':' est valide (a-z / A-Z / 0-9) */
		if (!(((BUFF[i]>='0')&&(BUFF[i]<='9'))||((BUFF[i]>='A')&&(BUFF[i]<='Z'))||((BUFF[i]>='a')&&(BUFF[i]<='z')))){
			return -1; 
			}
		i++;
		}
	return i; /* Si le code est correctement écrit : On retourne l'indice de ':' dans la chaîne. Sinon on renvoie le code erreur -1 */
	}

char* ligneTableauFichier(int i,char BUFF[],int numL,char* nomfichier,int* arret){ 
	/* Récupère tout ce qui n'est pas étiquette en sautant les éventuels espaces-tabulation. i est l'indice du premier élément suivant les deux points s'il y en a ou vaut 0 s'il n'y a pas d'étiquete dans la ligne, BUFF est la ligne qu'on a récupéré, numL est le numéro de la ligne courante (s'il faut afficher une erreur) et Fichier, ETI et nbEtiq pour la libération mémoire si on trouve une ligne sans instruction*/
	int taille = strlen(BUFF);
	while ((i < taille)&&((BUFF[i] == ' ')||(BUFF[i] == '\t'))) i++;
	/* Les espaces entre les deux points de l'étiquette et le mot-clef sont ignorés */
	char* ligne;
	if (i+1 == taille){ /* Il n'y aucune instruction ce n'est pas autorisé (ici on saute de 1 car on récupère toujours le \n */
		annonceErreur();
		printf("Absence d'instruction dans le code Assembleur à la ligne %d\n",numL);
		printf("%s\n",BUFF);
		ligne = malloc(sizeof(char));
		if (ligne == NULL){
			printf("L'allocation mémoire n'a pas pu être effectué \n");
			exit(1);
			}	
		ligne[0] = '\0'; /* On ira le free plus tard, l'objectif est de signaler le probleme pour qu'un certain nombre d'erreur s'affiche*/
		(*arret)++;
		}
	else{
		ligne = malloc(sizeof(char)*(taille-i)); /* Et non pas encore une fois taille-i+1 puisqu'il y a un '\n' */
		if (ligne == NULL){
			printf("L'allocation mémoire n'a pas pu être effectué \n");
			exit(1);
			}		
		int j = 0;
		while (j < taille-i-1){
			ligne[j] = BUFF[i+j];
			j++;
			}
		ligne[j] = '\0';
		}
	return ligne;
	}

int nombreDeLigne(const char* nomfichier){  /*Récupérer la longeur max des lignes*/
	FILE* fsrc = fopen(nomfichier,"r");
	int NbDeLigne = 0;
	char c;
	while((c = fgetc(fsrc)) != EOF){
		if(c == '\n') NbDeLigne += 1; /* Le \n est le caractère de fin de ligne, il figure donc même sur la dernière */
		}
	fclose(fsrc);
	if (NbDeLigne == 0){
		annonceErreur();
		printf("Fichier vide\n");
		exit(1);
		}
	return NbDeLigne;
	}
	
int recupEtiqLigne(char* nomfichier, etiq** ETI, const int nbligne ,char** fichier, int* arret){ 
/* La fonction remplit un tableau de pointeur sur la structure etiq avec le nom des étiquettes et les numéros des lignes correspondantes. Elle permet aussi de récupérer dans un tableau chaque ligne du fichier en supprimant les éléments dérangeant du début */
	FILE* fsrc = fopen(nomfichier,"r"); 
	int cpt = 0; /* Permet de compter le nombre d'étiquettes */
	for(int j = 0; j < nbligne; j++){
		char BUFF[100]; 
		if(fgets(BUFF,100,fsrc) != 0) { /* On vérifie que l'opération de récupération via la fonction fgets s'effectue correctement */
			char* p = strchr(BUFF,':'); /*On vérifie s'il y a effectivement une étiquette dans la ligne de code Assembleur indépendamment de ce qui est écrit après. C'est l'adresse du premier deux points qui est récupéré */
			int i = verifEtiquette(BUFF,p); 
			if (i > 0){ /* On a une étiquette */
				char* ligne = ligneTableauFichier(i+1,BUFF,j+1,nomfichier,arret); /*Tout ce qui suit l'étiquette est récupéré. Si c'est vide le programme s'arrête */
				fichier[j] = ligne;
				ETI[cpt] = malloc(sizeof(etiq));
				if (ETI[cpt] == NULL){
					printf("L'allocation mémoire n'a pas pu être effectué \n");
					exit(1);
					}
				ETI[cpt]->ligne = j+1;
				ETI[cpt]->eti = malloc(sizeof(char)*(i+1));
				if (ETI[cpt]->eti == NULL){
					printf("L'allocation mémoire n'a pas pu être effectué \n");
					exit(1);
					}
				for(int j = 0; j < i; j++) (ETI[cpt]->eti)[j] = BUFF[j];
				(ETI[cpt]->eti)[i] = '\0';
				cpt++;
				}
			else{
				char* ligne;
				if (i == -1){
					annonceErreur();
					printf("Nom d'étiquette non valide à la ligne %d\n",j+1);
					afficheErreurSyntaxeEti(nomfichier,j+1);
					(*arret)++;
					ligne = malloc(sizeof(char));
					ligne[0] = '\0'; /* On ne récupère aucune ligne mais comme on va free le tableau de ligne, on alloue un octet de mémoire pour stocker la chaîne vide */
					}
				else ligne = ligneTableauFichier(i,BUFF,j+1,nomfichier,arret);
				fichier[j] = ligne; 
				}
			}
		}
	fclose(fsrc);
	return cpt;
	}

void doublonEtiq(etiq** ETI, int n,int* arret, char* nomfichier){ /* n désignant le nombre d'étiquette */
	for(int i = 0; i < n-1; i++){ /* La dernière aura été comparée avec tout les autres donc on fixe la condition d'arrêt avant */
		int j = i+1;
		while (j < n) {
			if (strcmp(ETI[j]->eti,ETI[i]->eti) == 0){
				annonceErreur();
				printf("Il y a des doubles parmi vos étiquettes aux lignes %d et %d\n",ETI[i]->ligne,ETI[j]->ligne);
				affichageEtiIdentique(ETI[j]->eti,ETI[i]->ligne,ETI[j]->ligne,nomfichier);
				(*arret)++;
				}
			j ++;
			}
		}
	}
	
void traitementFinDeLigne(char* ch, int* p){ /* Supprime les espaces / les tabulations de fin */
	while((*p - 1 >= 0)&&((ch[*p-1] == ' ')||(ch[*p -1] == '\t'))){
		ch[*p-1] = '\0';
		*p = *p - 1;
		}
	}

void creationInstruction(char** fichier, int nbligne, instruction** tab, int* arret, char* nomfichier){
	int j = 0;
	for (int i = 0; i < nbligne; i++){
		int longeur = strlen(fichier[i]);
		traitementFinDeLigne(fichier[i],&longeur); /* On efface les excès de fin (sinon l'absence de donnée sera confondu avec la "donnée vide"), il n'y a donc ni d'espace avant (cf. étape précédente) ni d'espace après le bloc motclef + espace + donnée. On actualise aussi la longeur */
		tab[i] = malloc(sizeof(instruction));
		if (tab[i] == NULL){
			printf("L'allocation mémoire n'a pas pu être effectué \n");
			exit(1);
			}	
		tab[i]->motclef = malloc(sizeof(char)*longeur);
		if (tab[i]->motclef == NULL){
			printf("L'allocation mémoire n'a pas pu être effectué \n");
			exit(1);
			}	
		while ((fichier[i][j] != ' ')&&(j < longeur)){ /* On récupère le mot-clef */
			(tab[i]->motclef)[j] = fichier[i][j];
			j++;
			}
		tab[i]->motclef = realloc(tab[i]->motclef,sizeof(char)*(j+1));
		(tab[i]->motclef)[j] = '\0';
		j++; /* On suppose qu'il y a un unique espace après le mot clef qu'on ignore ou alors que l'on sort de l'instruction. Si on a un autre espace ou un bout qui n'a pas de rapport avec la donnée --> la suite se chargera de signaler l'erreur*/
		int l = j;
		if (j < longeur){
			tab[i]->donnee = malloc(sizeof(char)*(longeur-j+1));
			if (tab[i]->donnee == NULL){
				printf("L'allocation mémoire n'a pas pu être effectué \n");
				exit(1);
				} 
			do {
				if ((fichier[i][j] == ' ')||(fichier[i][j] == '\t')){ /* S'il y a un espace avant la donnée ou à l'intérieur elle sera fausse donc on s'arrête là */
					annonceErreur();
					printf("Bloc donnée non-conforme à la ligne %d\n",i+1);
					afficheErreurDonneeLigne(fichier[i]);
					tab[i]->donnee[0] = '\0';
					tab[i]->donnee = realloc(tab[i]->donnee,sizeof(char));
					if (tab[i]->donnee == NULL){
						printf("L'allocation mémoire n'a pas pu être effectué \n");
						exit(1);
						} 
					(*arret)++;
					j = 0;
					break;
					}
				(tab[i]->donnee)[j-l] = fichier[i][j];
				j++; 
				} while (j < longeur); /* On ne met pas de back slash 0 à la fin mais ce n'est pas grave pour le traitement suivant puisque nous avons en mémoire le nombre de caractère de ch2 */
			if (j < longeur) continue; /* On ne s'arrête pas pour autant on signale une erreur mais on vérifie le reste des lignes*/	
			(tab[i]->donnee)[j-l] = '\0'; /* On doit cloturer la chaîne */
			tab[i]->donnee = realloc(tab[i]->donnee,sizeof(char)*(j-l+1));
			if (tab[i]->donnee == NULL){
				printf("L'allocation mémoire n'a pas pu être effectué \n");
				exit(1);
				} 
			}	
		else {
			tab[i]->donnee = malloc(sizeof(char)*2);		
			tab[i]->donnee[0] = '@'; /*Le symbole @ signalera l'absence de donnée*/
			tab[i]->donnee[1] = '\0';
			}
		j = 0;
		}
	}
	
void coherenceLigneType1(char* donnee,int numligne,instructionNumerique* IN, int* arret, int min, int max,char** fichier){
/* On récupére la donnée, le numéro de la ligne - pour signaler l'erreur -, on vérifie qu'on soit bien dans un certain intervalle [min;max] qui dépend du mot-clef et on en profite pour remplir le tableau d'instruction numérique qui va permettre d'effectuer la transcription */ 
	char* verif;
	long entier = strtol(donnee,&verif,10);
	if ((errno != ERANGE)&&((*verif) != '\0')){ /* ERRNO ne vaut pas ERANGE donc ce n'est pas un nombre trop gros. Si verif ne pointe pas sur une case mémoire dans laquelle est stocké l'octet nul cela veut dire qu'il a été confronté à un caractère qui a arrêté la transcription numérique qui n'était pas l'octet final de la chaîne de caractère "donnée" */
		annonceErreur();
		printf("La donnée à la ligne %d n'est pas un nombre\n",numligne);
		afficheErreurDonneeLigne(fichier[numligne-1]);
		(*arret)++;
		}
	else if ((entier > max)||(entier < min)){ /* Si errno vaut ERANGE c'est qu'on a dépassé l'intervalle des long c'est à dire un intervalle dans lequel est forcément inclus [min;max] donc onn'a pas besoin de le vérifier. On fait donc simplement le test < max et > min */
		annonceErreur();
		printf("La donnée numérique à la ligne %d dépasse l'intervalle autorisé  [%d;%d] \n",numligne,min,max);
		afficheErreurDonneeLigne(fichier[numligne-1]);
		(*arret)++;
		}
	errno = 0; /*Doit-être réinitialiser à 0, sinon des erreurs qui n'en seraient pas réellement pourrait être signalée */
	IN->donnee = entier;
	}
			
void coherenceLigneType2(char* donnee,int numligne, etiq** ETI, int nbrEtiq,int nbrLigne, instructionNumerique* IN,int* arret, char** fichier){ /* Concerne les étiquettes */
	if ((donnee[0] == '-')||((donnee[0] >= '0')&&(donnee[0] <= '9')))
		coherenceLigneType1(donnee,numligne,IN,arret,-numligne,nbrLigne -numligne - 1,fichier); /* Si après une instruction de saut on indique une valeur numérique, on renvoie le travail à la cohérence des lignes de type 1 avec un min et un max qui correspondent au saut maximum vers le bas et au saut minimum vers le haut que l'on peut faire sans sortir de l'intervalle des lignes du programme */
	else{
		int entier; /* On va traduire une étiquette par une valeur numérique : le saut à faire */
		int i = 0;
		int nontrouve;
		while (i < nbrEtiq){
			nontrouve = strcmp(donnee,(ETI[i]->eti));
			if (!(nontrouve)){
				entier = (ETI[i]->ligne) - numligne - 1; /*JMP 2 te dit que tu sautes 2 instructions donc la case qui a 3 de gap au niveau des numeros de lignes devant toi. JMP 0 tu ne sautes pas d'instructions tu passes à la suivantes. JMP -1 tu passes à celle d'avant càd toi même JMP -2 à celle juste avant. D'où toujours retirer 1*/
				break;
				}
			i++;
			}
			if (nontrouve){
				annonceErreur();
				printf("Etiquette introuvable à la ligne %d\n",numligne);
				afficheErreurDonneeLigne(fichier[numligne-1]);
				(*arret)++;
				return;
				}
			IN->donnee = entier;
			}
		}

void coherenceInstructions(instruction** tab,instructionNumerique** tab2, etiq** ETI, int numcase, int nbretiq,int* arret,char** fichier){ 
/* Cette fonction permet de vérifier la cohérence des données et des mots-clefs. On en profite pour remplir un tableau d'instruction numérique. */
	for(int j = 0; j < numcase; j++){
		tab2[j] = malloc(sizeof(instructionNumerique));
		if (strcmp(tab[j]->donnee,"") == 0){ /* Il y a un problème detecté auparavent mais nous continuons la vérification pour afficher toutes les erreurs */
			continue;
			}
		else if(strcmp((tab[j]->motclef),"push#") == 0){
			tab2[j]->code = 1;
			coherenceLigneType1(tab[j]->donnee,j+1,tab2[j],arret,-2147483648,2147483647,fichier);
			}
		else if (strcmp((tab[j]->motclef),"jmp") == 0){
			tab2[j]->code = 7;
			coherenceLigneType2(tab[j]->donnee,j+1,ETI,nbretiq,numcase,tab2[j],arret,fichier);
			}
		else if(strcmp((tab[j]->motclef),"jpz") == 0){
			tab2[j]->code = 8;
			coherenceLigneType2(tab[j]->donnee,j+1,ETI,nbretiq,numcase,tab2[j],arret,fichier);
			}
		else if (strcmp((tab[j]->motclef),"call") == 0){
			tab2[j]-> code = 12;
			coherenceLigneType2(tab[j]->donnee,j+1,ETI,nbretiq,numcase,tab2[j],arret,fichier);
			}
		else if (strcmp((tab[j]->motclef),"push") == 0){
			tab2[j]-> code = 0;
			coherenceLigneType1(tab[j]->donnee,j+1,tab2[j],arret,0,4999,fichier);
			}
		else if (strcmp((tab[j]->motclef),"pop") == 0){
			tab2[j]-> code = 3;
			coherenceLigneType1(tab[j]->donnee,j+1,tab2[j],arret,0,4999,fichier);
			}
		else if (strcmp((tab[j]->motclef),"rnd") == 0){
			tab2[j]-> code = 9;
			coherenceLigneType1(tab[j]->donnee,j+1,tab2[j],arret,-2147483647,2147483647,fichier); /* Puisqu'on va regarde ENTRE 0 et x-1 */
			}
		else if(strcmp((tab[j]->motclef),"read") == 0){
			tab2[j]-> code = 10;
			coherenceLigneType1(tab[j]->donnee,j+1,tab2[j],arret,0,4999,fichier);
			}
		else if (strcmp((tab[j]->motclef),"write") == 0){
			tab2[j]-> code = 11;
			coherenceLigneType1(tab[j]->donnee,j+1,tab2[j],arret,0,4999,fichier);
			}
		else if (strcmp((tab[j]->motclef),"op") == 0){
			tab2[j]-> code = 6;
			coherenceLigneType1(tab[j]->donnee,j+1,tab2[j],arret,0,15,fichier);
			}
		else if (strcmp((tab[j]->motclef),"ipush") == 0){
			if (!(strcmp((tab[j]->donnee),"@") == 0)){
				printf("Erreur de donnée à la ligne %d\n",j+1);
				afficheErreurDonneeLigne(fichier[j]);
				(*arret)++;
				}
			tab2[j]->code = 2;
			tab2[j]->donnee = 0;
			}
		else if(strcmp((tab[j]->motclef),"ipop") == 0){
			if (!(strcmp((tab[j]->donnee),"@") == 0)){
				printf("Erreur de donnée à la ligne %d\n",j+1);
				afficheErreurDonneeLigne(fichier[j]);
				(*arret)++;
				}
			tab2[j]->code = 4;
			tab2[j]->donnee = 0;
			}
		else if (strcmp((tab[j]->motclef),"dup") == 0){
			if (!(strcmp((tab[j]->donnee),"@") == 0)){
				printf("Erreur de donnée à la ligne %d\n",j+1);
				afficheErreurDonneeLigne(fichier[j]);
				(*arret)++;
				}
			tab2[j]->code = 5;
			tab2[j]->donnee = 0;
			}
		else if(strcmp((tab[j]->motclef),"ret") == 0){
			if (!(strcmp((tab[j]->donnee),"@") == 0)){
				printf("Erreur de donnée à la ligne %d\n",j+1);
				afficheErreurDonneeLigne(fichier[j]);
				(*arret)++;
				}
			tab2[j]->code = 13;
			tab2[j]->donnee = 0;
			}
		else if (strcmp((tab[j]->motclef),"halt") == 0){
			if (!(strcmp((tab[j]->donnee),"@") == 0)){
				printf("Erreur de donnée à la ligne %d\n",j+1);
				afficheErreurDonneeLigne(fichier[j]);
				(*arret)++;
				}
			tab2[j]->code = 14;
			tab2[j]->donnee = 0;
			}
		else{
			annonceErreur();
			printf("Mot-clef invalide à la ligne %d\n",j+1);
			afficheErreurMotClef(fichier[j]);
			(*arret)++;
			}
		} 
	} 
	
void traduction(FILE* fdest,instructionNumerique** tab, int numcase){
	for (int i = 0; i < numcase; i++) {
		fprintf(fdest,"%02x %08x\n", tab[i]->code, tab[i]->donnee);
		}
	}

void recupCode(instruction** tab3,int nbligne){ /* NE MARCHE PLUS */
	FILE* fhexa = fopen("hexa.txt","r"); /* Faire plus proprement */
	for(int i = 0; i < nbligne; i++){
		tab3[i] = malloc(sizeof(instruction));
		if (tab3[i] == NULL){
			printf("Une allocation mémoire n'a pas pu être effectué \n");
			exit(1);
			}
		tab3[i]->motclef = malloc(sizeof(char)*3);
		if (tab3[i]->motclef == 0){
			printf("Une allocation mémoire n'a pas pu être effectué \n");
			exit(1);
			}
		tab3[i]->donnee = malloc(sizeof(char)*9);
		if (tab3[i]->donnee == 0){
			printf("Une allocation mémoire n'a pas pu être effectué \n");
			exit(1);
			}
		fgets(tab3[i]->motclef,3,fhexa); /* On va récupérer les deux premiers caractères */
		fgetc(fhexa); /* On skip l'espace du fichier hexa */
		fgets(tab3[i]->donnee,9,fhexa); /* On récupére la donnée */
		fgetc(fhexa); /*On passe le \n et on place le curseur sur la prochaine ligne */
		}
	fclose(fhexa);
	}

void push(char* donnee,int memoire[],int* pSP){
	int adresse = strtol(donnee,NULL,16); /*Renvoit un long mais normalement les valeurs sont assez petites pr que la conversion en int s'opère efficacement */
	printf("On rentre dans un push avec adresse : %d\n",adresse);
	int valeur = memoire[adresse];
	printf("Valeur trouvé :%d\n",valeur);
	memoire[(*pSP)] = valeur;
	printf("On a mis dans la case %d la valeur %d\n",*pSP,memoire[(*pSP)]);
	(*pSP)++;
	printf("SP vaut maintenant : %d\n",*pSP);
	printf("fin\n\n");
	}
	 
void pushHashtag(char* donnee,int memoire[],int* pSP){
	long valeur = strtol(donnee,NULL,16);
	printf("On rentre dans un push# de valeur (sans inter C2) : %ld\n",valeur);
	if (valeur > 2147483647) valeur = valeur - 4294967296;
	//printf("EN C2 : %ld\n",valeur);
	memoire[(*pSP)] = valeur;
	printf("On a mis dans la case %d la valeur : %d\n",*pSP,memoire[(*pSP)]);
	(*pSP)++;
	printf("SP vaut maintenant : %d\n",*pSP);
	printf("fin\n\n");
	}
	
void ipush(int memoire[],int* pSP){
	if (*pSP == 0){
		(*pSP) = -1;
		return;
		}
	int adresse = memoire[(*pSP)-1];
	printf("On recupere de la case %d l'adresse %d\n",(*pSP)-1,adresse);
	if (!((adresse >=0)&&(adresse<5000))){
		(*pSP) = -1;
		return;
		}
	memoire[(*pSP)-1] = memoire[adresse];
	printf("On a trouvé à l'adresse la valeur : %d, elle est stocké dans %d",memoire[adresse],*pSP-1); 
	printf("fin\n\n");
	}
	
void pop(char* donnee,int memoire[],int* pSP){
	int adresse = strtol(donnee,NULL,16);
	printf("On retire %d de la case %d pour la stocker dans la case %d\n",memoire[(*pSP)-1],(*pSP)-1,adresse);
	(*pSP)--;
	memoire[adresse] = memoire[(*pSP)];
	printf("SP vaut maintenant : %d\n",*pSP);
	printf("fin\n\n");
	}
	 
void ipop(int memoire[],int* pSP){
	if (*pSP <= 1){
		(*pSP) = -1;
		return;
		}
	int adresse = memoire[(*pSP)-1];
	if (!((adresse >=0)&&(adresse<5000))){
		(*pSP) = -1;
		return;
		}
	printf("Je rentre dans un ipop et je récupère l'adresse %d\n",adresse);
	memoire[adresse] = memoire[(*pSP) -2];
	printf("Je stocke la valeur %d de la case %d dans la case %d",memoire[(*pSP) -2],(*pSP) -2,adresse);
	(*pSP) = (*pSP) - 2;
	printf("SP vaut maintenant %d\n",*pSP);
	printf("fin\n\n");
	}
	
void dup(int memoire[], int* pSP){
	if ((*pSP) == 0){
		(*pSP) = -1;
		return;
		}
	memoire[*pSP] = memoire[*pSP-1];
	printf("On dupplique %d\n",memoire[*pSP-1]);
	(*pSP)++;
	printf("SP vaut maintenant %d\n",*pSP);
	printf("fin\n\n");
	}

void op(char* donnee, int memoire[], int *pSP){
	long valeur = strtol(donnee,NULL,16); 
	if (valeur == 0){
		(*pSP)--;
		if ((*pSP) == 0){ /* On fait appel à un deuxième élément situé en dehors de la mémoire, on doit stopper l'exécution */
			(*pSP) = -1;  /*On force l'erreur a être signalée dans la fonction execution, en fixant le pointeur de Pile à -1 */
			return;
			}
		printf("On additionne %d (case %d) et %d (case %d) et cela donne : ",memoire[(*pSP)-1],(*pSP)-1,memoire[(*pSP)],(*pSP));
		memoire[(*pSP)-1] = memoire[(*pSP)-1] + memoire[(*pSP)];
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 1){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On soustrait %d et %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		memoire[(*pSP)-1] = memoire[(*pSP)-1] - memoire[(*pSP)];
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 2){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On multiplie %d et %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		memoire[(*pSP)-1] = memoire[(*pSP)-1] * memoire[(*pSP)];
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 3){
		(*pSP)--;
		if ((memoire[*pSP]) == 0){
			(*pSP) = -100;
			return;
			}
		printf("On effectue la division entière de %d et %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		memoire[(*pSP)-1] = memoire[(*pSP)-1]/memoire[(*pSP)];
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 4){
		(*pSP)--;
		if (memoire[*pSP] == 0){
			(*pSP) = -100;
			return;
			}
		printf("On calcule le modulo de la division entière de %d et %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		memoire[(*pSP)-1] = memoire[(*pSP)-1]%memoire[(*pSP)];
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 5){
		printf("On inverse la valeur de l'élément %d de la case %d\n",memoire[(*pSP)-1],(*pSP)-1);
		memoire[(*pSP)-1] = -memoire[(*pSP)-1];
		}
	else if (valeur == 6){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On teste l'égalité de %d et %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		if (memoire[(*pSP)-1] == memoire[(*pSP)]){
			memoire[(*pSP)-1] = 0;
			}
		else{
			memoire[(*pSP)-1] = 1;
			}
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 7){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On teste l'inégalité de %d et %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		if (memoire[(*pSP)-1] != memoire[(*pSP)]){
			memoire[(*pSP)-1] = 0;
			}
		else{
			memoire[(*pSP)-1] = 1;
			}
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 8){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On teste :  %d > %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		if (memoire[(*pSP)-1] > memoire[(*pSP)]){
			memoire[(*pSP)-1] = 0;
			}
		else{
			memoire[(*pSP)-1] = 1;
			}
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 9){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On teste :  %d >= %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		if (memoire[(*pSP)-1] >= memoire[(*pSP)]){
			memoire[(*pSP)-1] = 0;
			}
		else{
			memoire[(*pSP)-1] = 1;
			}
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 10){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On teste :  %d < %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		if (memoire[(*pSP)-1] < memoire[(*pSP)]){
			memoire[(*pSP)-1] = 0;
			}
		else{
			memoire[(*pSP)-1] = 1;
			}
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 11){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On teste :  %d <= %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		if (memoire[(*pSP)-1] <= memoire[(*pSP)]){
			memoire[(*pSP)-1] = 0;
			}
		else{
			memoire[(*pSP)-1] = 1;
			}
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 12){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On effectue le ""et logique"" bit à bit  %d et %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		memoire[(*pSP)-1] = memoire[(*pSP)-1]&memoire[(*pSP)];
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 13){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On effectue le ""ou logique"" bit à bit  %d et %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		memoire[(*pSP)-1] = memoire[(*pSP)-1]|memoire[(*pSP)];
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else if (valeur == 14){
		(*pSP)--;
		if ((*pSP) == 0){
			(*pSP)--;
			return;
			}
		printf("On effectue le ""ou-exclusif logique"" bit à bit  %d et %d et cela donne : ",memoire[(*pSP)-1],memoire[(*pSP)]);
		memoire[(*pSP)-1] = memoire[(*pSP)-1]^memoire[(*pSP)];
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	else {
		printf("On effectue le ""et logique"" bit à bit  de %d et cela donne : ",memoire[(*pSP)-1]);
		memoire[(*pSP)-1] = ~memoire[(*pSP)-1];
		printf("%d\n",memoire[(*pSP)-1]);
		printf("SP vaut maintenant %d\n",(*pSP));
		}
	}

void jmp (char* donnee,int* pPC){
	int saut = strtol(donnee,NULL,16);
	printf("Un saut de %d\n",saut);
	printf("Le registre PC pointe sur %d\n",(*pPC));
	(*pPC) = (*pPC) + saut;
	printf("On fait un jump à l'instruction %d\n",*pPC);
	}

void jpz(char* donnee, int memoire[],int* pSP,int* pPC){
	int saut = strtol(donnee,NULL,16);
	(*pSP)--;
	if (memoire[*pSP] == 0){
		(*pPC) = (*pPC) + saut;
		}
	}
	
void rnd(char* donnee,int memoire[],int* pSP){
	int borne = strtol(donnee,NULL,16);
	srand(time(NULL));
	int negatif = 0;
	if (borne < 0){
		negatif = 1;
		borne = -borne + 2;
		}
	int alea = rand()%borne;
	if (negatif) memoire[(*pSP)] = -alea;
	else memoire[(*pSP)] = alea;
	(*pSP)++;
	}

void read(char* donnee,int memoire[]){
	int adresse = strtol(donnee,NULL,16);
	int valeur;
	scanf("%d",&valeur);
	memoire[adresse] = valeur;
	}
	
void write(char* donnee,int memoire[]){
	int adresse = strtol(donnee,NULL,16);
	printf("On écrit le contenu de la case mémoire d'adresse %d\n",adresse);
	printf("%d\n",memoire[adresse]);
	}

void call(char* donnee,int memoire[],int* pSP,int* pPC){
	memoire[(*pSP)] = *pPC;
	(*pSP)++;
	jmp(donnee,pPC);
	}
	
void ret(int memoire[],int* pSP, int* pPC){
	printf("On rentre dans un retour de procédure et on trouve au sommet de la pile : %d et actuellement PC est sur la %d instruction",memoire[(*pSP)-1],*pPC);
	(*pPC) = memoire[--(*pSP)];
	}
	
void execution(instruction** tab3,int nbligne, int memoire[]){
	int SP = 0; /* On initialise notre pointeur de pile sa valeur est une adresse de la mémoire càd un nombre entre 0 et 4999 */
	int PC = 0; /* On initialise le registre PC à 0 (il pointe sur la première instruction du programme), il s'incrémente à chaque fin d'exécution d'une instruction et est modifiable par un certain nombre de fonctions */
	while (PC < nbligne){
		if(tab3[PC]->motclef[1] == '0'){
			PC++;
			push(tab3[PC-1]->donnee,memoire,&SP);
			}
		else if (tab3[PC]->motclef[1] == '1'){
			PC++;
			pushHashtag(tab3[PC-1]->donnee,memoire,&SP);
			}
		else if(tab3[PC]->motclef[1] == '2'){
			PC++;
			ipush(memoire,&SP);	
			}
		else if (tab3[PC]->motclef[1] == '3'){
			PC++;
			pop(tab3[PC-1]->donnee,memoire,&SP);
			}
		else if (tab3[PC]->motclef[1] == '4'){
			PC++;
			ipop(memoire,&SP);
			}
		else if (tab3[PC]->motclef[1] == '5'){
			PC++;
			dup(memoire,&SP);
			}
		else if (tab3[PC]->motclef[1] == '6'){
			PC++;
			op(tab3[PC-1]->donnee,memoire,&SP);	
			}
		else if (tab3[PC]->motclef[1] == '7'){
			PC++;
			jmp(tab3[PC-1]->donnee,&PC);
			}
		else if (tab3[PC]->motclef[1] == '8'){
			PC++;
			jpz(tab3[PC-1]->donnee,memoire,&SP,&PC);	
			}
		else if (tab3[PC]->motclef[1] == '9'){
			PC++;
			rnd(tab3[PC-1]->donnee,memoire,&SP);
			}
		else if (tab3[PC]->motclef[1] == 'a'){
			PC++;
			read(tab3[PC-1]->donnee,memoire);
			}
		else if(tab3[PC]->motclef[1] == 'b'){
			PC++;
			write(tab3[PC-1]->donnee,memoire);
			}
		else if (tab3[PC]->motclef[1] == 'c'){
			PC++;
			call(tab3[PC-1]->donnee,memoire,&SP,&PC);	
			}
		else if(tab3[PC]->motclef[1] == 'd'){
			ret(memoire,&SP,&PC);
			if (PC >= nbligne){
				annonceErreur();
				printf("Tentative d'accès à une instruction inexistante\n");
				return;				
				}
			}
		else {
			return;
			}
		if (SP == -100){
			annonceErreur();
			printf("Tentative de division par 0. Fin de l'exécution\n");
			return;
			}
		if ((SP < 0)||(SP > 4999)){
			annonceErreur();
			printf("Tentative d'accès mémoire interdite. Fin de l'exécution\n");
			return;			
			}
		}
	}

int main(int argc, char* argv[]){

/* Vérifier que le passage de fichier en argument est ok */

	if (argc == 1){
		annonceErreur();
		printf("Il n'y a pas de fichier en entrée\n");
		return -1;
		}
	FILE* fsrc = fopen(argv[1],"r");
	if (fsrc == NULL) {
		annonceErreur();
		printf("Le fichier n'existe pas\n");
		return -1;
		}
	fclose(fsrc);
	
/* Commencer la compilation */

	int condArret = 0; /* Cet entier va permettre de lister les erreurs sur le terminal avant d'indiquer un arrêt propre du programme. */
	int nbligne = nombreDeLigne(argv[1]);
	char**  Fichier = malloc(sizeof(char*)*nbligne); /* Servira à récupérer chaque ligne du fichier en Assembleur */
	if (Fichier == NULL){
		printf("L'allocation mémoire n'a pas pu être effectué \n");
		exit(1);
		}	
	etiq** ETI = malloc(sizeof(etiq*)*nbligne);
	if (ETI == NULL){
		printf("L'allocation mémoire n'a pas pu être effectué \n");
		exit(1);
		}	
	int nbrEtiq = recupEtiqLigne(argv[1],ETI,nbligne,Fichier,&condArret);  /* On récupére le nombre d'étiquette, on stocke les étiquettes dans un tableau et les instructions (mots-clefs + donnee) dans fichier sans récupérer les espaces/tabulations avant le première caractère de l'instruction. Si une ligne ne contient pas d'instruction ou qu'il y a une erreur de syntaxe dans une étiquette, l'erreur est signalé grâce à la variable condArret. */
	ETI = realloc(ETI,sizeof(etiq*)*nbrEtiq);
	if ((nbrEtiq != 0)&&(ETI == NULL)){
		printf("L'allocation mémoire n'a pas pu être effectué \n");
		exit(1);
		}
	doublonEtiq(ETI,nbrEtiq,&condArret,argv[1]); /* On vérifie les doublons des étiquettes, l'erreur est aussi signalé grâce à la variable condArret */
	if (condArret > 0){ /* Signale les erreurs d'identificateurs non-valides,les doublons et les instructions vides (ligne vide ou avec uniquement une étiquette) */
		condArret = -1;
		goto liberationMem; /* On ne libere que ce qui a été déclaré */
		} 
	instruction** tab = malloc(sizeof(instruction*)*nbligne); /* Nous allons récupérer chacunes des instructions dans ce tableau d'instruction*/
	if (tab == NULL){
		printf("L'allocation mémoire n'a pas pu être effectué \n");
		exit(1);
		}	
	creationInstruction(Fichier, nbligne, tab,&condArret,argv[1]); /* Cela crée un tableau d'instructions. On vérifie simplement que chaque ligne est de la forme bloc1 bloc2 avec bloc2 éventuellement vide. La cohérence des instructions n'est pas vérifiée ici. */
	instructionNumerique** tab2 = malloc(sizeof(instructionNumerique*)*nbligne); /* Nous déclarons ce tableau dans lequel nous allons mettre les traductions en instructions numériques du code assembleur */
	if (tab2 == NULL){
		printf("L'allocation mémoire n'a pas pu être effectué \n");
		exit(1);
		}
	coherenceInstructions(tab,tab2,ETI,nbligne,nbrEtiq,&condArret,Fichier); /* Nous vérifions cette fois-ci en utilisant les fonctions coherenceLigneType1 et coherenceLigneType2 que la syntaxe des mots-clefs est correcte et que les données associées sont cohérentes */
	for(int i = 0; i < nbligne; i++){
		libereInstruction(tab[i]);
		}
	free(tab);
	
	liberationMem : for(int i = 0; i < nbrEtiq; i ++){
		libereEtiquette(ETI[i]);
		}
	free(ETI);
	for(int i = 0; i < nbligne; i++){
		free(Fichier[i]);
		}
	free(Fichier);
	if (condArret == -1) exit(1); /* concerne la première catégorie d'erreur (étiquettes + lignes vides) */	
	else if (condArret > 0) goto liberationMem2; /* Si on a pas d'erreur de première catégorie mais des erreurs sur les données ou les mots-clefs on va un peu plus loin pour libérer tab2 avant de cloturer le programme */
	
	FILE* fdest = fopen("hexa.txt","w");
	if (fdest == NULL){
		printf("Erreur : il est impossible de créer un fichier machine");
		exit(1);
		}
	traduction(fdest,tab2,nbligne);
	
	liberationMem2 : for(int i = 0; i < nbligne; i ++){
		free(tab2[i]);
		}
	free(tab2);
	if (condArret > 0) exit(1);
	
	fclose(fdest); 
	
/* On vient de créer l'exécutable. Fin de l'étape de compilation */
	
/* L'objectif étant de simuler une machine à pile, on distingue les deux tâches de compilation et de simulation. Ainsi, on ne garde aucune donnée déjà défini ici y compris le nombre de ligne de l'hexa */
	nbligne = nombreDeLigne("hexa.txt");
	instruction** tab3 = malloc(sizeof(instruction*)*nbligne); /*On va récupèrer donc toutes les lignes du fichier hexa dans un tableau de pointeurs sur la structure instruction */
	if (tab3 == NULL){
		printf("Une allocation mémoire n'a pas pu être effectué \n");
		exit(1);
		}	
	recupCode(tab3,nbligne); 
	for(int i =0; i < nbligne; i++){
		AffichageInstruction(tab3[i]);
		}
	int memoire[5000]; /* Cette déclaration rend (plus que cela ne l'était déjà) nécessaire pour notre code de vérifier que le pointeur de pile ne vaut pas -1 car il est possible que l'adresse mémoire de tab3 se situe avant celle de mémoire (se succédant effectivement dans le code) et qu'on puisse donc perdre l'accès à ce dernier en sortant de la fonction */
	execution(tab3,nbligne,memoire); /* exécution finale du code */
	for(int i = 0; i < nbligne; i++){
		libereInstruction(tab3[i]);
		}
	free(tab3);
	}



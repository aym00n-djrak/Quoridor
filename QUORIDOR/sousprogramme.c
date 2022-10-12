#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct menu
{
    int score;
    int tour;
    int ordre;
    int nb_joueurs;
}t_menu;

typedef struct mapiece
{
    int x;
    int y;
}t_mapiece;

typedef struct joueur
{
 char pseudo[100];
 int barriere;
 int score;
 char jeton;
 char jetonbarriere;
 int tabx[100];
 int taby[100];
 t_mapiece position;
 t_mapiece bposition;
}t_joueur;

void plateau();
void gotoligcol( int lig, int col );
void Color(int couleurDuTexte,int couleurDeFond);

void tirageausort(t_menu *menu);
void deplacerpiece(t_joueur *player);
void poserpiece(int x, int y, char jeton);

void creerjoueur(t_joueur *player1,t_joueur *player2,t_joueur *player3,t_joueur *player4,t_joueur *player11,t_joueur *player22,t_joueur *player33,t_joueur *player44,t_menu *menu);
void creerjoueur2(t_joueur *player1,t_joueur *player2,t_joueur *player11,t_joueur *player22,t_menu *menu);
void creerjoueur4(t_joueur *player1,t_joueur *player2,t_joueur *player3,t_joueur *player4,t_joueur *player11,t_joueur *player22, t_joueur *player33, t_joueur *player44, t_menu *menu);

char jeton_alea(char jeton);
void menu();
void poserbarriere(t_joueur *player,t_menu *menu, char tab[17][17],int tabbarrierex1[100], int tabbarrierey1[100], int tabbarrierex2[100], int tabbarrierey2[100], int sens[100]);
void passerTour();
void annulerAction1(int *tabanulx, int *tabanuly, int tour, t_joueur *player);
void annulerAction2(int *tabanulx, int *tabanuly, int tour, t_joueur *player);
void annulerAction4(int *tabanulx, int *tabanuly, int tour, t_joueur *player);
void annuler1(t_joueur *player1);
void annuler2(t_joueur *player2);
void annuler3(t_joueur *player3);
void annuler4(t_joueur *player4);
void annulerBarriereH(t_joueur *player, t_menu *menu, int tabbarrierex[100], int tabbarrierey[100]);
void annulerBarriereV(t_joueur *player, t_menu *menu, int tabbarrierex[100], int tabbarrierey[100]);
void aide();

void oldscore2(t_joueur *player1,t_joueur *player2,t_joueur *player11,t_joueur *player22,t_menu *menu);
void oldscore4(t_joueur *player1,t_joueur *player2,t_joueur *player3,t_joueur *player4,t_joueur *player11,t_joueur *player22,t_joueur *player33,t_joueur *player44,t_menu *menu);
void reprise(t_joueur *player1, t_joueur *player2, t_joueur *player3, t_joueur *player4, t_menu *menu,int tabbarrierex1[100],int tabbarrierey1[100],int tabbarrierex2[100],int tabbarrierey2[100],int sens[100]);
void score(t_joueur *player1, t_joueur *player2, t_joueur *player3, t_joueur *player4);
void infoPartie(t_joueur *player,t_menu *menu);
void menujeu(t_joueur *player1, t_joueur *player2,t_joueur *player3, t_joueur *player4,t_menu *menu, char tab[17][17], int tabbarrierex1[100], int tabbarrierey1[100], int tabbarrierex2[100], int tabbarrierey2[100], int sens[100]);

void QUORIDOR();
void END();
void DE();
void TAUREAU();

void sauvegardeb(int tabbarrierex1[100],int tabbarrierey1[100], int tabbarrierex2[100],int tabbarrierey2[100], int sens[100]);
void sauvegarde2(t_joueur player1,t_joueur player2, t_menu menu);
void sauvegarde4(t_joueur player1,t_joueur player2,t_joueur player3,t_joueur player4, t_menu menu);
void sauvegardep(int tabx[100], int taby[100]);

void chargement();
void chargement2(t_joueur *player1,t_joueur *player2);
void chargement4(t_joueur *player1,t_joueur *player2, t_joueur *player3, t_joueur *player4);

void chargementb(int tabbarrierex1[100],int tabbarrierey1[100],int tabbarrierex2[100],int tabbarrierey2[100],int sens[100]);
void scoreaff(t_joueur *player1, t_joueur *player2, t_joueur *player3,t_joueur *player4, t_menu *menu);

char quijoue(t_joueur *player);
void limiteplateau(t_mapiece piece);
void tabcouleur(char tabcol[17][33], char tablig[16][35]);
void temps();

void gagner1(t_joueur *player1);
void gagner2(t_joueur *player2);
void gagner3(t_joueur *player3);
void gagner4(t_joueur *player4);

void bloquebarriere(t_joueur *player);

void sauterunpion2J(t_joueur*player1,t_joueur*player2,t_menu*menu);
void sauterunpion1p2(t_joueur*player1,t_joueur*player2,t_menu*menu);
void sauterunpion2p2(t_joueur*player1,t_joueur*player2,t_menu*menu);
void sauterunpion4J(t_joueur *player1, t_joueur *player2,t_joueur*player3, t_joueur*player4,t_menu*menu);
void sauterunpion1(t_joueur *player1, t_joueur *player2,t_joueur*player3, t_joueur*player4,t_menu*menu);
void sauterunpion2(t_joueur *player1, t_joueur *player2,t_joueur*player3, t_joueur*player4,t_menu*menu);
void sauterunpion3(t_joueur *player1, t_joueur *player2,t_joueur*player3, t_joueur*player4,t_menu*menu);
void sauterunpion4(t_joueur *player1, t_joueur *player2,t_joueur*player3, t_joueur*player4,t_menu*menu);


void sleep();
int getch();

void supprimerpiece(int x,int y);
void supp(int x, int y);
void aidejoueur(t_menu *menu);

//GENERATION DU TABLEAU
void plateau()
{
    //ON DEFINI 2 ENTIERS ET UN NUMERO
    int x, y, numero=0;

    //ON PARCOURS LA 1ERE LIGNE DU TABLEAU POUR AFFICHER LES COLONNES DE A a I
    for(x='A';x<='I';x++)
    {
        //ON ECRIT LA LETTRE EN ROUGE GRACE A COLOR ET PRINTF
        Color(12,0);
        printf("  %c ", x); //ON INCREMENTE DES ESPACES POUR BIEN SE SITUER DANS LE TABLEAU
    }
    printf("\n"); //ON SAUTE UNE LIGNE

    for(x=0;x<17;x++) //ON FAIT CIRCULER NOTRE X DE 0 A 17 POUR FORMER LES LIGNES DU TABLEAU
    {
        Color(15,0); // ON DEFINIT LA COULEUR SUR ECRITURE BLANC ET FOND NOIR

        for(y=0;y<17;y++) //ON FAIT CIRCULER NOTRE Y DE 0 A 17 POUR FORMER LES COLONNES DU TABLEAU
        {
            if((x%2==0)&&(y==0)) // LORSQUE LES LIGNES SONT PAIRES ON AFFICHE LE NUMERO DES LIGNES DE 1 A 9
                {
                numero++;
                Color(12,0);
                printf("%d ",numero); //AFFICHAGE DES NUMERO DE LIGNE
                Color(15,0);
                printf("  ");
                }
            else if((x%2==0)&&(y%2==0)) //ON AFFICHE LES CASES BLANCHES PAIRES
            {
                Color(15,0);
                printf("  ");
            }
            else
            {
                if((x%2!=0)&&(y==0))   //ON TRACE UN ESPACE SUR LA PREMIERE COLONNE POUR OBSERVER UN DECALAGE
                {
                    printf("  ");
                }
                Color(0,7); //ON TRACE LES CASES NOIRES
                printf("  ");
            }
        }   printf("\n"); //ON PASSE A LA LIGNE SUIVANTE
    }
}

//GENERATION ALEATOIRE DE L'ORDRE DE PASSAGE
void tirageausort(t_menu *menu)
{
    srand(time(NULL));

    if(menu->nb_joueurs==2)
    {
        menu->ordre=rand()%(2-1+1)+1;
        gotoligcol(13,35);
        Color(13,0);
        printf("Le joueur %d commence la partie !", menu->ordre);
        sleep(1);
        Color(15,0);
    }
    if(menu->nb_joueurs==4)
    {
        menu->ordre=rand()%(4-1+1)+1;
        gotoligcol(13,35);
        Color(13,0);
        sleep(1);
        printf("Le joueur %d commence la partie !", menu->ordre);
        Color(15,0);
    }
}

//DEPLACER LE CURSEUR SUR LECRAN
void gotoligcol( int lig, int col )
{
// ressources
COORD mycoord;

mycoord.X = col;
mycoord.Y = lig;
SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );

}


//MODIFIER LA COULEUR DE LAFFICHAGE
void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}


//DEPLACER UN JETON SUR LE PLATEAU
void deplacerpiece(t_joueur *player)
{
    int sortie=0;
    int compteur=4;
    int key;
    gotoligcol(27,0);
    printf("Deplacement avec ZQSD, pose du jeton avec ENTREE.");
    sleep(1);
    gotoligcol(27,0);
    printf("                                                   ");

    do
    {
        key= getch();

        switch(key)
        {
        case(122):         //Z  HAUT

            (player->position.x)--;
            gotoligcol(player->position.x,player->position.y);
            break;
        case(113):   //Q    GAUCHE
            (player->position.y)=(player->position.y)-2;
            gotoligcol(player->position.x,player->position.y);
            break;
        case(115):   //S    BAS
            (player->position.x)++;
            gotoligcol(player->position.x,player->position.y);
            break;
        case(100):    //D   DROITE
            (player->position.y)=(player->position.y)+2;
            gotoligcol(player->position.x,player->position.y);
            break;
        case(13):     // ENTREE JETON
            printf("%c",player->jeton);
            sortie=1;
            break;
        case(27):    //ECHAP
            sortie=1;
            break;
        default:
            gotoligcol(28,0);
            printf("Il y a une erreur dans le choix\n");
            sleep(1);
            gotoligcol(28,0);
            printf("                                     ");
            break;
        }
        compteur--;

        if(compteur<0)
        {
        gotoligcol(28,0);
        printf("Vous êtes alle trop loin, annule ta derniere action !");
        gotoligcol(28,0);
        sleep(2);
        printf("                                ");
        }
    }while((sortie==0)&&(player->position.x<18)&&(player->position.y<=36)&&((player->position.x>=0)&&(player->position.y>=0))&&compteur>0);
}

//POSER UNE PIECE
void poserpiece(int x, int y, char jeton)
{
    gotoligcol(x,y);
    printf("%c",jeton);
}

//SUPPRIMER UNE PIECE
void supprimerpiece(int x, int y)
{
    gotoligcol(x,y);
    Color(15,0);
    printf(" ");
}

//SUPPRIMER UNE PIECE SUR LE MAUVAIS EMPLACEMENT
void supp(int x, int y)
{
    gotoligcol(x,y);
    Color(0,7);
    printf(" ");
}

//MENU POUR LANCER UNE PARTIE ET INFO DE LA PARTIE
void menu()
{
    t_joueur player1,player2,player3,player4,player11,player22,player33,player44;
    t_menu menu;
    int menuchoix,i,j;
    char tab[17][17];
    int tabbarrierex1[100];
    int tabbarrierey1[100];
    int tabbarrierex2[100];
    int tabbarrierey2[100];
    int sens[100];

    int exit=0;

    for(i=0;i<100;i++)
    {
        tabbarrierex1[i]=0;
        tabbarrierey1[i]=0;
        tabbarrierex2[i]=0;
        tabbarrierey2[i]=0;
        sens[i]=3;
    }

    for(i=0;i<17;i++)
    {
        for(j=0;j<17;j++)
        {
            tab[i][j]=0;
        }
    }

    player1.position.x=17;
    player1.position.y=18;

    player2.position.x=1;
    player2.position.y=18;

    player3.position.x=9;
    player3.position.y=2;

    player4.position.x=9;
    player4.position.y=34;

    menu.tour=1;

do
    {
        QUORIDOR();
        sleep(2);
        system("cls");

    Color(9,0);
    gotoligcol(7,40);
    DE();
    gotoligcol(4,55);
    printf("QUORIDOR :\n");
    Color(15,0);
    gotoligcol(6,45);
    printf("1. Lancer une nouvelle partie\n");
    gotoligcol(7,45);
    printf("2. Reprendre une partie sauvegardee\n");
    gotoligcol(8,45);
    printf("3. Afficher l'aide\n");
    gotoligcol(9,45);
    printf("4. Afficher les scores des joueurs\n");
    gotoligcol(10,45);
    printf("5. Quitter le jeu\n");
    gotoligcol(11,45);

    gotoligcol(13,45);
    printf("Faites un choix :\n");


    do
    {
        gotoligcol(13,65);
        sleep(1);
        printf("     ");
         gotoligcol(13,65);
        fflush(stdin);
        scanf("%d",&menuchoix);
    }while((menuchoix<1)||(menuchoix>5));
   // Color(0,0);
    switch(menuchoix)
    {
    case 1:
        system("cls");
        creerjoueur(&player1,&player2,&player3,&player4,&player11,&player22,&player33,&player44,&menu);
        sleep(3);

        system("cls");
        tirageausort(&menu);
        sleep(1);
        system("cls");
        plateau();

        if(menu.nb_joueurs==2)
        {
        gotoligcol(player1.position.x,player1.position.y);
        printf("%c",player1.jeton);

        gotoligcol(player2.position.x,player2.position.y);
        printf("%c",player2.jeton);
        }

        if(menu.nb_joueurs==4)
        {
        gotoligcol(player1.position.x,player1.position.y);
        printf("%c",player1.jeton);

        gotoligcol(player2.position.x,player2.position.y);
        printf("%c",player2.jeton);

        gotoligcol(player3.position.x,player3.position.y);
        printf("%c",player3.jeton);

        gotoligcol(player4.position.x,player4.position.y);
        printf("%c",player4.jeton);
        }

        if(menu.ordre==4)
        {
            infoPartie(&player4,&menu);
        }
        if(menu.ordre==3)

        {
            infoPartie(&player3,&menu);
        }
        if(menu.ordre==2)
        {
            infoPartie(&player2,&menu);
        }
        if(menu.ordre==1)
        {
            infoPartie(&player1,&menu);
        }
        menujeu(&player1,&player2,&player3,&player4,&menu, tab, tabbarrierex1, tabbarrierey1, tabbarrierex2, tabbarrierey2, sens);
        break;
    case 2:
        system("cls");
        reprise(&player1,&player2,&player3,&player4,&menu,tabbarrierex1,tabbarrierey2 ,tabbarrierex2,tabbarrierey2,sens);
        menujeu(&player1,&player2,&player3,&player4,&menu, tab, tabbarrierex1,tabbarrierey2,tabbarrierex2,tabbarrierey2,sens);
        break;
    case 3:
        system("cls");
        aide();
        break;
    case 4:
        scoreaff(&player1, &player2, &player3,&player4, &menu);
        break;

    case 5:
        exit=1;
        printf("Quitter le jeu: toucher n'importe qu'elle touche de votre clavier.\n");
        break;
    default:
        printf("Erreur\n");
        break;
    }
    }while(exit==0);

}

//AFFICHER LE SCORE
void scoreaff(t_joueur *player1, t_joueur *player2, t_joueur *player3,t_joueur *player4, t_menu *menuu)
{
    //AFFICHAGE DU SCORE DANS LE MENU
        int choix;
        system("cls");
        chargement(player1,player2,player3,player4,menuu);

        Color(13,0);
        gotoligcol(1,45);
        printf("SCORE DES JOUEURS:\n");

        Color(2,0);
        //SELECTION DU NOMBRE DE JOUEURS ET AFFICHAGE DE LEURS SCORES
        if(menuu->nb_joueurs==2)
        {
        gotoligcol(3,30);
        printf("Player1:\t%s\t%d\t Player2:\t%s\t%d\t",player1->pseudo,player1->score,player2->pseudo, player2->score);
        }
        if(menuu->nb_joueurs==4)
        {
        gotoligcol(3,20);
        printf("Player1:\t%s\t%d\t Player2:\t%s\t%d\t Player3:\t%s\t%d\t Player4:\t%s\t%d\t",player1->pseudo,player1->score,player2->pseudo, player2->score,player3->pseudo, player3->score,player4->pseudo, player4->score);
        }
        Color(9,0);
                do
        {
            printf("\n");
            printf("\n");
            gotoligcol(28,0);
            printf("Voulez-vous retourner au menu ;) ? Tapez 0\n");
            scanf("%d",&choix);
            Color(15,0);
            menu();
        }while(choix!=0);
}

//CREER LES JOUEURS
void creerjoueur(t_joueur *player1,t_joueur *player2,t_joueur *player3,t_joueur *player4,t_joueur *player11,t_joueur *player22,t_joueur *player33,t_joueur *player44,t_menu *menu)
{
    //ON CREE LES JOUEURS
    gotoligcol(1,45);
    Color(13,0);
    printf("CREATION DES JOUEURS :");
    Color(15,0);

    //SAISIE DU NOMBRE DE JOUEURS
    gotoligcol(4,35);
    printf("Combien y a t'il de joueur, saisir 2 ou 4?\n");
    do
    {
        gotoligcol(5,55);
        sleep(1);
        printf("       ");
        gotoligcol(5,55);
        fflush(stdin);
        scanf("%d",&menu->nb_joueurs);

    }while(!((menu->nb_joueurs==2)||(menu->nb_joueurs==4)));

    gotoligcol(7,35);
    printf("Il y a %d joueurs\n",menu->nb_joueurs);
    creerjoueur2(player1,player2,player11,player22,menu);
    creerjoueur4(player1,player2,player3,player4,player11,player22,player33,player44,menu);
}

//CREATION DE 2 JOUEURS
void creerjoueur2(t_joueur *player1,t_joueur *player2,t_joueur *player11,t_joueur *player22,t_menu *menu)
{
        int i;
        if (menu->nb_joueurs==2)
    {
        menu->nb_joueurs=2;

        //SAISI DES PSEUDOS
    gotoligcol(9,35);
    printf("Saisir le pseudo du premier joueur:\n");
    fflush(stdin);
    gotoligcol(10,35);
    gets(player1->pseudo);
    gotoligcol(12,35);
    printf("Le pseudo est %s\n", player1->pseudo);
    gotoligcol(13,35);
    printf("Saisir le pseudo du deuxieme joueur:\n");
    gotoligcol(14,35);
    gets(player2->pseudo);
    gotoligcol(16,35);
    printf("Le pseudo est %s\n", player2->pseudo);

    for (i=0;i<100;i++)
    {
        player1->tabx[i]=0;
        player1->taby[i]=0;
        player2->tabx[i]=0;
        player2->taby[i]=0;
    }

    // ALLOCATION DES BARRIERES
    gotoligcol(18,35);
    printf("Chaque joueur possede 10 barrieres.\n");
    player1->barriere=10;
    player2->barriere=10;

    //GENERATION ALEATOIRE DES JETONS
    gotoligcol(20,35);
    printf("Choix aleatoire du jeton entre: @\t*\t#\t&\t%%\t?\t£\t$\n");

    do
    {
    player1->jeton = jeton_alea(player1->jeton);
    player2->jeton = jeton_alea(player2->jeton);
    }while(player1->jeton==player2->jeton);

    gotoligcol(22,35);
    printf("Le jeton choisi est %c\n",player1->jeton);
    gotoligcol(22,35);
    printf("Le jeton choisi est %c\n",player2->jeton);

    gotoligcol(24,35);
    printf("Le score est initialise a 0\n");
    player1->score=0;
    player2->score=0;

    //ON CHARGE LES ANCIENS SCORE SI ILS CORRESPONDENT A UN ANCIEN PSEUDO
    oldscore2(player1,player2,player11,player22,menu);

    //ON SAUVEGARDE LES INFOS POUR 2 JOUEURS
    sauvegarde2(*player1,*player2,*menu);
    }
}
//CREATION DE 4 JOUEURS
void creerjoueur4(t_joueur *player1,t_joueur *player2,t_joueur *player3,t_joueur *player4,t_joueur *player11,t_joueur *player22,t_joueur *player33,t_joueur *player44,t_menu *menu)
{
    int i;
    if(menu->nb_joueurs==4)
    {

        //SAISI DES PSEUDOS
    gotoligcol(9,35);
    printf("Saisir le pseudo du joueur:\n");
    fflush(stdin);
    gotoligcol(10,35);
    gets(player1->pseudo);
    gotoligcol(12,35);
    printf("Le pseudo est %s\n", player1->pseudo);

    gotoligcol(14,35);
    printf("Saisir le pseudo du deuxieme joueur:\n");

    gotoligcol(15,35);
    gets(player2->pseudo);
    gotoligcol(16,35);
    printf("Le pseudo est %s\n", player2->pseudo);

    gotoligcol(18,35);
    printf("Saisir le pseudo du troisieme joueur:\n");
    gotoligcol(19,35);
    gets(player3->pseudo);
    gotoligcol(20,35);
    printf("Le pseudo est %s\n", player3->pseudo);

    gotoligcol(22,35);
    printf("Saisir le pseudo du quatrieme joueur :\n");
    gotoligcol(23,35);
    gets(player4->pseudo);

    gotoligcol(24,35);
    printf("Le pseudo est %s\n", player4->pseudo);


    // ALLOCATION DES BARRIERES
    gotoligcol(26,35);
    printf("Chaque joueurs possede 5 barrieres.\n");
    player1->barriere=5;
    player2->barriere=5;
    player3->barriere=5;
    player4->barriere=5;

    for (i=0;i<100;i++)
    {
        player1->tabx[i]=0;
        player1->taby[i]=0;
        player2->tabx[i]=0;
        player2->taby[i]=0;
        player3->tabx[i]=0;
        player3->taby[i]=0;
        player4->tabx[i]=0;
        player4->taby[i]=0;
    }

    //GENERATION ALEATOIRE

    gotoligcol(28,35);
    printf("Choix aleatoire du jeton entre: @\t*\t#\t&\t%%\t?\t£\t$\n");
    do
    {
    player1->jeton = jeton_alea(player1->jeton);
    player2->jeton = jeton_alea(player2->jeton);
    player3->jeton = jeton_alea(player3->jeton);
    player4->jeton = jeton_alea(player4->jeton);
    }while((player1->jeton==player2->jeton)||(player1->jeton==player3->jeton)||(player3->jeton==player4->jeton)||(player4->jeton==player1->jeton)||(player4->jeton==player2->jeton));

    gotoligcol(30,35);
    printf("Le jeton choisi est %c\n",player1->jeton);
    gotoligcol(31,35);
    printf("Le jeton choisi est %c\n",player2->jeton);
    gotoligcol(32,35);
    printf("Le jeton choisi est %c\n",player3->jeton);
    gotoligcol(33,35);
    printf("Le jeton choisi est %c\n",player4->jeton);

    gotoligcol(35,35);
    printf("Le score commence a 0\n");
    player1->score=0;
    player2->score=0;
    player3->score=0;
    player4->score=0;

    //ON CHARGE LES ANCIENS SCORE SI ILS CORRESPONDENT A UN ANCIEN PSEUDO
    oldscore4(player1,player2,player3, player4,player11,player22,player33, player44, menu);

    //ON SAUVEGARDE LES INFOS POUR 4 JOUEURS
    sauvegarde4(*player1,*player2,*player3,*player4,*menu);
    }
}

//GENERATION JETON ALEATOIRE
char jeton_alea(char jeton)
{
    int choix=0;
    int alea=1;

    if (choix!=alea)
    {
    choix= rand()%(7-0+1)+0;
    alea=choix;

        if (choix>7)
    {
        printf("Le jeton n'existe pas\n");
    }
    else
    {
        switch(choix)
        {
        case 0:
            jeton='@';
            break;
        case 1:
            jeton='*';
            break;
        case 2:
            jeton='#';
            break;
        case 3:
            jeton='&';
            break;
        case 4:
            jeton='%';
            break;
        case 5:
            jeton='?';
            break;
        case 6:
            jeton='£';
            break;
        case 7:
            jeton='$';
            break;
        default:
            break;
        }
    }
}
return jeton;
}

//GAGNER 1ER JOUEUR
void gagner1(t_joueur *player1)
{
    int i;
    for(i=0;i<=36;i++)
    if(player1->position.x==1 && player1->position.y==i)
    {
        system("cls");
        printf("Le joueur 1 a gagne !");
        player1->score=player1->score+5;
        END();

            Color(15,0);
    gotoligcol(20,0);
    printf("                                      ");

    gotoligcol(21,0);
    printf("                                         ");

    gotoligcol(22,0);
    printf("                                            ");

    gotoligcol(23,0);
    printf("                                            ");

    gotoligcol(24,0);
    printf("                                            ");

    gotoligcol(25,0);
    printf(" Retour au menu\n");

    gotoligcol(26,0);
    printf("                                               ");
    gotoligcol(26,0);
    printf("Taper 5\n");
    }
}

//GAGNER 2EME JOUEUR
void gagner2(t_joueur *player2)
{
    int i;
    for(i=0;i<=36;i++)
    if(player2->position.x==17 && player2->position.y==i)
    {
        system("cls");
        printf("Le joueur 2 a gagne !");
        player2->score=player2->score+5;
        END();
                    Color(15,0);
    gotoligcol(20,0);
    printf("                                      ");

    gotoligcol(21,0);
    printf("                                         ");

    gotoligcol(22,0);
    printf("                                            ");

    gotoligcol(23,0);
    printf("                                            ");

    gotoligcol(24,0);
    printf("                                            ");

    gotoligcol(25,0);
    printf(" Retour au menu\n");

    gotoligcol(26,0);
    printf("                                               ");
    gotoligcol(26,0);
    printf("Taper 5\n");

    }
}

//GAGNER 3EME JOUEUR
void gagner3(t_joueur *player3)
{
    int i;
    for(i=0;i<=18;i++)
    if((player3->position.x==i && player3->position.y==35)||(player3->position.x==i && player3->position.y==35))
    {
        system("cls");
        printf("Le joueur 3 a gagne !");
        player3->score=player3->score+5;
        END();
                    Color(15,0);
    gotoligcol(20,0);
    printf("                                      ");

    gotoligcol(21,0);
    printf("                                         ");

    gotoligcol(22,0);
    printf("                                            ");

    gotoligcol(23,0);
    printf("                                            ");

    gotoligcol(24,0);
    printf("                                            ");

    gotoligcol(25,0);
    printf(" Retour au menu\n");

    gotoligcol(26,0);
    printf("                                               ");
    gotoligcol(26,0);
    printf("Taper 5\n");

    }
}

//GAGNER 4 EME JOUEUR
void gagner4(t_joueur *player4)
{
    int i;
    for(i=0;i<=18;i++)
    if((player4->position.x==i && player4->position.y==3)||(player4->position.x==i && player4->position.y==4))
    {
        system("cls");
        printf("Le joueur 4 a gagne !");
        player4->score=player4->score+5;
        END();
                    Color(15,0);
    gotoligcol(20,0);
    printf("                                      ");

    gotoligcol(21,0);
    printf("                                         ");

    gotoligcol(22,0);
    printf("                                            ");

    gotoligcol(23,0);
    printf("                                            ");

    gotoligcol(24,0);
    printf("                                            ");

    gotoligcol(25,0);
    printf(" Retour au menu\n");

    gotoligcol(26,0);
    printf("                                               ");
    gotoligcol(26,0);
    printf("Taper 5\n");

    }
}

//AFFICHAGE DES INFORMATIONS JOUEUR DE LA PARTIE
void infoPartie(t_joueur *player,t_menu *menu)
{
    //INFORMATION DU JOUEURS ET DE LA PARTIE
    Color(15,0);
    gotoligcol(0,40);
    printf("                               ");
    gotoligcol(0,40);
    printf("Tour : %d\n", menu->tour);

    gotoligcol(2,40);
    printf("Nombre de joueurs: %d\n", menu->nb_joueurs);

    gotoligcol(4,40);
    printf("                                            ");
    gotoligcol(4,40);
    printf("Joueurs: ");
    puts(player->pseudo);

    gotoligcol(6,40);
    printf("                                              ");
    gotoligcol(6,40);
    printf("Score partie: %d\n",player->score);

    gotoligcol(8,40);
    printf("Jeton: %c\n", player->jeton);

    gotoligcol(10,40);
    printf("                                              ");
    gotoligcol(10,40);
    printf("Barrieres restantes: %d\n",player->barriere);

    gotoligcol(15,40);
    printf("Aide / Astuce: \n");
    aidejoueur(menu);
}

//AIDE DU JOUEUR PENDANT LA PARTIE
void aidejoueur(t_menu *menu)
{
    int alea;
    //AIDE TOUS LES TOURS 2 TOURS

    if(menu->tour%2==0)
    {
        //GENERATION ALEATORIRE DE L'AFFICHAGE
        alea=rand()%(10-1+1)+1;

        if(alea==10)
        {
            gotoligcol(17,40);
            printf("En manque d'inspiration ?\n");
            sleep(1);
            gotoligcol(18,40);
            printf("Je te conseille de ne pas foncer dans les barrieres ;)\n");
            sleep(4);
            gotoligcol(17,40);
            printf("                                 ");
            gotoligcol(18,40);
            printf("                                                              ");
        }
        if(alea==9)
        {
            gotoligcol(17,40);
            printf("Alors on s'en sort?\n");
            sleep(1);
            gotoligcol(18,40);
            printf("Je te conseille de te rapprocher du joueur pour pouvoir lui sauter par dessus !\n");
            sleep(1);
            gotoligcol(19,40);
            printf("Depeche toi, s'il arrive avant toi, il te verra le coup !");
            sleep(4);
            gotoligcol(17,40);
            printf("                                 ");
            gotoligcol(18,40);
            printf("                                                                                         ");
            gotoligcol(19,40);
            printf("                                                                ");
        }

        if(alea==8)
        {
            gotoligcol(17,40);
            printf("Je sens que tu coinces ?\n");
            sleep(1);
            gotoligcol(18,40);
            printf("Si tu te trouves dans une impasse, pose une barriere pour bloquer ton adversaire\n");
            sleep(1);
            gotoligcol(19,40);
            printf("Depeche toi, s'il arrive avant toi, il te verra le coup !");
            sleep(4);
            gotoligcol(17,40);
            printf("                                 ");
            gotoligcol(18,40);
            printf("                                                                                        ");
            gotoligcol(19,40);
            printf("                                                              ");
        }

        if(alea==7)
        {
            gotoligcol(17,40);
            printf("Oh tu veux gagner ?\n");
            sleep(1);
            gotoligcol(18,40);
            printf("Essaie d'arriver le plus vite possible sur la ligne devant toi :) !\n");
            sleep(1);
            gotoligcol(19,40);
            printf(";)");
            sleep(4);
            gotoligcol(17,40);
            printf("                                 ");
            gotoligcol(18,40);
            printf("                                                                         ");
            gotoligcol(19,40);
            printf("                                                              ");
        }

        if(alea==6)
        {
            gotoligcol(17,40);
            printf("Coince ?\n");
            sleep(1);
            gotoligcol(18,40);
            printf("Marche vers la case la plus proche c'est la seule solution!\n");
            sleep(1);
            gotoligcol(19,40);
            printf("Tu verras tu peux le rattraper!");
            sleep(4);
            gotoligcol(17,40);
            printf("                                 ");
            gotoligcol(18,40);
            printf("                                                                  ");
            gotoligcol(19,40);
            printf("                                                              ");
        }

        if(alea==5)
        {
            gotoligcol(17,40);
            printf("HAHA, besoin d'un coup de main ?!!\n");
            sleep(1);
            gotoligcol(18,40);
            printf("Pose une barriere en face de ton adversaire pour le bloquer!\n");
            sleep(1);
            gotoligcol(19,40);
            printf("Attention, tu ne peux effectuer qu'une action par tour!");
            sleep(4);
            gotoligcol(17,40);
            printf("                                          ");
            gotoligcol(18,40);
            printf("                                                                  ");
            gotoligcol(19,40);
            printf("                                                              ");
        }

        if(alea==4)
        {
            gotoligcol(17,40);
            printf("Tu es perdu ?\n");
            sleep(1);
            gotoligcol(18,40);
            printf("Respire, reprend tes esprits et fonce !\n");
            sleep(1);
            gotoligcol(19,40);
            printf("Ne perd pas espoir, bloque ton adversaire !");
            sleep(4);
            gotoligcol(17,40);
            printf("                                 ");
            gotoligcol(18,40);
            printf("                                                              ");
            gotoligcol(19,40);
            printf("                                                              ");
        }

        if(alea==3)
        {
            gotoligcol(17,40);
            printf("Ne te rejouis pas trop vite, tu crois pouvoir gagner ?\n");
            sleep(1);
            gotoligcol(18,40);
            printf("Reste concentre !\n");
            sleep(1);
            gotoligcol(19,40);
            printf("Regarde chaque deplacement de ton adversaire et definis la meilleure strategie.");
            sleep(4);
            gotoligcol(17,40);
            printf("                                                                                            ");
            gotoligcol(18,40);
            printf("                                                                                                    ");
            gotoligcol(19,40);
            printf("                                                                                                    ");
        }

        if(alea==2)
        {
            gotoligcol(17,40);
            printf("Alors on s'en sort?\n");
            sleep(1);
            gotoligcol(18,40);
            printf("Plus tu es proche de ton adversaire et plus il y a de risques !\n");
            sleep(1);
            gotoligcol(19,40);
            printf("Depeche toi, bloque le pour qu'il ne t'atteigne pas !");
            sleep(4);
            gotoligcol(17,40);
            printf("                                 ");
            gotoligcol(18,40);
            printf("                                                                       ");
            gotoligcol(19,40);
            printf("                                                              ");
        }

        if(alea==1)
        {
            gotoligcol(17,40);
            printf("On y est presque !\n");
            sleep(1);
            gotoligcol(18,40);
            printf("Pose le plus de barrieres possibles pour rendre le chemin de ton adversaire le plus complique !\n");
            gotoligcol(19,40);
            sleep(1);
            printf("Depeche toi, s'il arrive avant toi, il te verra le coup !");
            sleep(4);
            gotoligcol(17,40);
            printf("                                 ");
            gotoligcol(18,40);
            printf("                                                                                                             ");
            gotoligcol(19,40);
            printf("                                                              ");
        }
    }
}

//AFFICHAGE DU MENU DU JEU ET MISE EN PLACE DU JEU
void menujeu(t_joueur *player1, t_joueur *player2,t_joueur *player3, t_joueur *player4,t_menu *menu, char tab[17][17], int tabbarrierex1[100], int tabbarrierey1[100], int tabbarrierex2[100], int tabbarrierey2[100], int sens[100])
{
    int choix, i=0;
    int retour=0;
    int mvpion=0;
    int mvbarriere=0;

    int tabjeton1x[100];
    int tabjeton1y[100];
    int tabjeton2x[100];
    int tabjeton2y[100];
    int tabjeton3x[100];
    int tabjeton3y[100];
    int tabjeton4x[100];
    int tabjeton4y[100];

    for (i=0;i<100;i++)
    {
        tabjeton1x[i]=0;
        tabjeton1y[i]=0;
        tabjeton2x[i]=0;
        tabjeton2y[i]=0;
        tabjeton3x[i]=0;
        tabjeton3y[i]=0;
        tabjeton4x[i]=0;
        tabjeton4y[i]=0;
    }

while (retour==0)
{
    if(menu->tour<0)
    {
        menu->tour=0;
    }

    if(menu->nb_joueurs==4)
    {
     if((menu->ordre>4)||(menu->ordre<1))
    {
        menu->ordre=1;
    }
    }
    if(menu->nb_joueurs==2)
    {
        if((menu->ordre>2)||(menu->ordre<1))
    {
        menu->ordre=1;
    }
    }

    //MENU DE JEU/ COMMANDE POSSIBLES
    Color(15,0);
    gotoligcol(20,0);
    printf("Actions possibles :\n");

    gotoligcol(21,0);
    printf("1 - Deplacer son pion\n");

    gotoligcol(22,0);
    printf("2 - Poser une barriere\n");

    gotoligcol(23,0);
    printf("3 - Passer son tour\n");

    gotoligcol(24,0);
    printf("4 - Annuler la derniere action\n");

    gotoligcol(25,0);
    printf("5 - Retour au menu\n");

    gotoligcol(26,0);
    printf("Faire un choix entre les propositions 1 a 5\n");

    scanf("%d",&choix);

    switch(choix)
    {
case 1: //DEPLACEMENT PION

                //SI QUE 4 JOUEURS
        if ((mvpion==0)&&(mvbarriere==0))
        {
            if(menu->nb_joueurs==4)
            {
            if(menu->ordre==4)
            {
                infoPartie(player4,menu);
                supprimerpiece(player4->position.x,player4->position.y);
                deplacerpiece(player4);

                //BLINDAGE DES POSITIONS DU PION
                if (((player4->position.x==2)&&((player4->position.y>=2)&&(player4->position.y<=35)))||((player4->position.x==4)&&((player4->position.y>=2)&&(player4->position.y<=35)))||((player4->position.x==6)&&((player4->position.y>=2)&&(player4->position.y<=35)))||((player4->position.x==8)&&((player4->position.y>=2)&&(player4->position.y<=35)))||((player4->position.x==10)&&((player4->position.y>=2)&&(player4->position.y<=35)))||((player4->position.x==12)&&((player4->position.y>=2)&&(player4->position.y<=35)))||((player4->position.x==14)&&((player4->position.y>=2)&&(player4->position.y<=35)))||((player4->position.x==16)&&((player4->position.y>=2)&&(player4->position.y<=35)))||((player4->position.y==4)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==5)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==8)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==9)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==12)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==13)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==16)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==17)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==20)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==21)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==24)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==25)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==28)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==29)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==32)&&((player4->position.x>=1)&&(player4->position.x<=17)))||((player4->position.y==33)&&((player4->position.x>=1)&&(player4->position.x<=17))))
                {
                    if ((menu->tour==1)||(menu->tour==2)||(menu->tour==3)||(menu->tour==4))
                    {
                        supp(player4->position.x,player4->position.y);
                        Color(15,0);
                        annuler4(player4);
                        mvpion=0;
                    }
                    else
                    {
                        tabjeton4x[menu->tour]=player4->position.x;
                        tabjeton4y[menu->tour]=player4->position.y;
                        supp(player4->position.x,player4->position.y);
                        Color(15,0);
                        annulerAction4(tabjeton4x, tabjeton4y, menu->tour, player4);
                        mvpion=0;
                        player4->position.x=tabjeton4x[(menu->tour)-4];
                        player4->position.y=tabjeton4y[(menu->tour)-4];
                    }
                    gotoligcol(28,0);
                    printf("Vous ne pouvez pas le placer la, Rappuyer sur 1 pour re-essayer 1\n");
                    sleep(3);
                    gotoligcol(28,0);
                    printf("                                                                     ");
                }
                else
                {
                tabjeton4x[menu->tour]=player4->position.x;
                tabjeton4y[menu->tour]=player4->position.y;
                player4->tabx[menu->tour]=player4->position.x;
                player4->taby[menu->tour]=player4->position.y;
                sauterunpion4J(player1,player2,player3,player4,menu);
                bloquebarriere(player4);

                gagner4(player4);
                mvpion=1;
                }

            }

            if(menu->ordre==3)
            {
                infoPartie(player3,menu);
                supprimerpiece(player3->position.x,player3->position.y);
                deplacerpiece(player3);
                //BLINDAGE DES POSITIONS DU PION
                if (((player3->position.x==2)&&((player3->position.y>=2)&&(player3->position.y<=35)))||((player3->position.x==4)&&((player3->position.y>=2)&&(player3->position.y<=35)))||((player3->position.x==6)&&((player3->position.y>=2)&&(player3->position.y<=35)))||((player3->position.x==8)&&((player3->position.y>=2)&&(player3->position.y<=35)))||((player3->position.x==10)&&((player3->position.y>=2)&&(player3->position.y<=35)))||((player3->position.x==12)&&((player3->position.y>=2)&&(player3->position.y<=35)))||((player3->position.x==14)&&((player3->position.y>=2)&&(player3->position.y<=35)))||((player3->position.x==16)&&((player3->position.y>=2)&&(player3->position.y<=35)))||((player3->position.y==4)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==5)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==8)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==9)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==12)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==13)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==16)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==17)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==20)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==21)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==24)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==25)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==28)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==29)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==32)&&((player3->position.x>=1)&&(player3->position.x<=17)))||((player3->position.y==33)&&((player3->position.x>=1)&&(player3->position.x<=17))))
                {
                    if ((menu->tour==1)||(menu->tour==2)||(menu->tour==3)||(menu->tour==4))
                    {
                        supp(player3->position.x,player3->position.y);
                        Color(15,0);
                        annuler3(player3);
                        mvpion=0;
                    }
                    else
                    {
                        tabjeton3x[menu->tour]=player3->position.x;
                        tabjeton3y[menu->tour]=player3->position.y;
                        supp(player3->position.x,player3->position.y);
                        Color(15,0);
                        annulerAction4(tabjeton3x, tabjeton3y, menu->tour, player3);
                        mvpion=0;
                        player3->position.x=tabjeton3x[(menu->tour)-4];
                        player3->position.y=tabjeton3y[(menu->tour)-4];
                    }
                    gotoligcol(28,0);
                    printf("Vous ne pouvez pas le placer la, Rappuyer sur 1 pour re-essayer 1\n");
                    sleep(3);
                    gotoligcol(28,0);
                    printf("                                                                     ");
                }
                else
                {
                tabjeton3x[menu->tour]=player3->position.x;
                tabjeton3y[menu->tour]=player3->position.y;
                player3->tabx[menu->tour]=player3->position.x;
                player3->taby[menu->tour]=player3->position.y;
                sauterunpion4J(player1,player2,player3,player4,menu);
                bloquebarriere(player3);
                gagner3(player3);
                mvpion=1;
                }

            }

            if(menu->ordre==2)
            {
                infoPartie(player2,menu);
                supprimerpiece(player2->position.x,player2->position.y);
                deplacerpiece(player2);
                //BLINDAGE DES POSITIONS DU PION
                if (((player2->position.x==2)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==4)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==6)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==8)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==10)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==12)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==14)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==16)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.y==4)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==5)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==8)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==9)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==12)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==13)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==16)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==17)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==20)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==21)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==24)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==25)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==28)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==29)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==32)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==33)&&((player2->position.x>=1)&&(player2->position.x<=17))))
                {
                    if ((menu->tour==1)||(menu->tour==2)||(menu->tour==3)||(menu->tour==4))
                    {
                        supp(player2->position.x,player2->position.y);
                        Color(15,0);
                        annuler2(player2);
                        mvpion=0;
                    }
                    else
                    {
                        tabjeton2x[menu->tour]=player2->position.x;
                        tabjeton2y[menu->tour]=player2->position.y;
                        supp(player2->position.x,player2->position.y);
                        Color(15,0);
                        annulerAction4(tabjeton2x, tabjeton2y, menu->tour, player2);
                        mvpion=0;
                        player2->position.x=tabjeton2x[(menu->tour)-4];
                        player2->position.y=tabjeton2y[(menu->tour)-4];
                    }
                    gotoligcol(28,0);
                    printf("Vous ne pouvez pas le placer la, Rappuyer sur 1 pour re-essayer 1\n");
                    sleep(3);
                    gotoligcol(28,0);
                    printf("                                                                     ");
                }
                else
                {
                tabjeton2x[menu->tour]=player2->position.x;
                tabjeton2y[menu->tour]=player2->position.y;
                player2->tabx[menu->tour]=player2->position.x;
                player2->taby[menu->tour]=player2->position.y;
                sauterunpion4J(player1,player2,player3,player4,menu);
                bloquebarriere(player2);
                gagner2(player2);
                mvpion=1;
                }

            }
            if(menu->ordre==1)
            {
                infoPartie(player1,menu);
                supprimerpiece(player1->position.x,player1->position.y);
                deplacerpiece(player1);
                //BLINDAGE DES POSITIONS DU PION
                if (((player1->position.x==2)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==4)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==6)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==8)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==10)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==12)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==14)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==16)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.y==4)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==5)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==8)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==9)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==12)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==13)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==16)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==17)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==20)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==21)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==24)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==25)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==28)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==29)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==32)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==33)&&((player1->position.x>=1)&&(player1->position.x<=17))))
                {
                    if ((menu->tour==1)||(menu->tour==2)||(menu->tour==3)||(menu->tour==4))
                    {
                        supp(player1->position.x,player1->position.y);
                        Color(15,0);
                        annuler1(player1);
                        mvpion=0;
                    }
                    else
                    {
                        tabjeton1x[menu->tour]=player1->position.x;
                        tabjeton1y[menu->tour]=player1->position.y;
                        supp(player1->position.x,player1->position.y);
                        Color(15,0);
                        annulerAction4(tabjeton1x, tabjeton1y, menu->tour, player1);
                        mvpion=0;
                        player1->position.x=tabjeton1x[(menu->tour)-4];
                        player1->position.y=tabjeton1y[(menu->tour)-4];
                    }
                    gotoligcol(28,0);
                    printf("Vous ne pouvez pas le placer la, Rappuyer sur 1 pour re-essayer 1\n");
                    sleep(3);
                    gotoligcol(28,0);
                    printf("                                                                     ");
                }
                else
                {
                tabjeton1x[menu->tour]=player1->position.x;
                tabjeton1y[menu->tour]=player1->position.y;
                player1->tabx[menu->tour]=player1->position.x;
                player1->taby[menu->tour]=player1->position.y;
                sauterunpion4J(player1,player2,player3,player4,menu);
                bloquebarriere(player1);
                gagner1(player1);
                mvpion=1;
                }

            }
            }

           //SI QUE 2 JOUEURS

            if(menu->nb_joueurs==2)
            {
                if(menu->ordre==2)
            {
                infoPartie(player2,menu);
                supprimerpiece(player2->position.x,player2->position.y);
                deplacerpiece(player2);
                //BLINDAGE DES POSITIONS DU PION
                if (((player2->position.x==2)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==4)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==6)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==8)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==10)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==12)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==14)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.x==16)&&((player2->position.y>=2)&&(player2->position.y<=35)))||((player2->position.y==4)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==5)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==8)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==9)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==12)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==13)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==16)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==17)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==20)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==21)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==24)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==25)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==28)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==29)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==32)&&((player2->position.x>=1)&&(player2->position.x<=17)))||((player2->position.y==33)&&((player2->position.x>=1)&&(player2->position.x<=17))))
                {
                    if ((menu->tour==1)||(menu->tour==2))
                    {
                        supp(player2->position.x,player2->position.y);
                        Color(15,0);
                        annuler2(player2);
                        mvpion=0;
                    }
                    else
                    {
                        tabjeton2x[menu->tour]=player2->position.x;
                        tabjeton2y[menu->tour]=player2->position.y;
                        supp(player2->position.x,player2->position.y);
                        Color(15,0);
                        annulerAction2(tabjeton2x, tabjeton2y, menu->tour, player2);
                        mvpion=0;
                        player2->position.x=tabjeton2x[(menu->tour)-2];
                        player2->position.y=tabjeton2y[(menu->tour)-2];
                    }
                    gotoligcol(28,0);
                    printf("Vous ne pouvez pas le placer la, Rappuyer sur 1 pour re-essayer 1\n");
                    sleep(3);
                    gotoligcol(28,0);
                    printf("                                                                     ");
                }
                else
                {
                tabjeton2x[menu->tour]=player2->position.x;
                tabjeton2y[menu->tour]=player2->position.y;
                player2->tabx[menu->tour]=player2->position.x;
                player2->taby[menu->tour]=player2->position.y;
                sauterunpion2J(player1,player2,menu);

                gagner2(player2);
                mvpion=1;
                }

            }
                if(menu->ordre==1)
            {
                infoPartie(player1,menu);
                supprimerpiece(player1->position.x,player1->position.y);
                deplacerpiece(player1);
                //BLINDAGE DES POSITIONS DU PION
                if (((player1->position.x==2)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==4)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==6)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==8)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==10)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==12)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==14)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==16)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.y==4)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==5)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==8)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==9)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==12)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==13)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==16)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==17)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==20)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==21)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==24)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==25)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==28)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==29)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==32)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==33)&&((player1->position.x>=1)&&(player1->position.x<=17))))
                {
                    if ((menu->tour==1)||(menu->tour==2))
                    {
                        supp(player1->position.x,player1->position.y);
                        Color(15,0);
                        annuler1(player1);
                        mvpion=0;
                    }
                    else
                    {
                        tabjeton1x[menu->tour]=player1->position.x;
                        tabjeton1y[menu->tour]=player1->position.y;
                        supp(player1->position.x,player1->position.y);
                        Color(15,0);
                        annulerAction2(tabjeton1x, tabjeton1y, menu->tour, player1);
                        mvpion=0;
                        player1->position.x=tabjeton1x[(menu->tour)-2];
                        player1->position.y=tabjeton1y[(menu->tour)-2];
                    }

                    gotoligcol(28,0);
                    printf("Vous ne pouvez pas le placer la, Rappuyer sur 1 pour re-essayer 1\n");
                    sleep(3);
                    gotoligcol(28,0);
                    printf("                                                                     ");
                }
                else
                {
                tabjeton1x[menu->tour]=player1->position.x;
                tabjeton1y[menu->tour]=player1->position.y;
                player1->tabx[menu->tour]=player1->position.x;
                player1->taby[menu->tour]=player1->position.y;
                sauterunpion2J(player1,player2,menu);

                gagner1(player1);
                mvpion=1;
                }
            }
            }
        }
        break;

case 2: //POSE BARRIERE

        if ((mvbarriere==0)&&(mvpion==0))
        {
            if(menu->ordre==4)
            {
            poserbarriere(player4,menu,tab,tabbarrierex1,tabbarrierey1,tabbarrierex2,tabbarrierey2,sens);
            if (!(((player1->position.x==2)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==4)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==6)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==8)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==10)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==12)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==14)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.x==16)&&((player1->position.y>=2)&&(player1->position.y<=35)))||((player1->position.y==4)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==5)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==8)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==9)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==12)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==13)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==16)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==17)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==20)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==21)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==24)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==25)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==28)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==29)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==32)&&((player1->position.x>=1)&&(player1->position.x<=17)))||((player1->position.y==33)&&((player1->position.x>=1)&&(player1->position.x<=17)))))
            {
                if (sens[menu->tour]==1)
                {
                    ///A continuer
                }
            }
            infoPartie(player4,menu);
            }

            if(menu->ordre==3)
            {
            poserbarriere(player3,menu,tab,tabbarrierex1,tabbarrierey1,tabbarrierex2,tabbarrierey2,sens);
            infoPartie(player3,menu);
            }

            if(menu->ordre==2)
            {
            poserbarriere(player2,menu,tab,tabbarrierex1,tabbarrierey1,tabbarrierex2,tabbarrierey2, sens);
            infoPartie(player2,menu);
            }
            if(menu->ordre==1)
            {
            poserbarriere(player1,menu,tab,tabbarrierex1,tabbarrierey1,tabbarrierex2,tabbarrierey2,sens);
            infoPartie(player1,menu);
            }
        }
        mvbarriere=1;
            break;

case 3:     //PASSER TOUR
            passerTour();
            menu->tour = (menu->tour) +1;
            (menu->ordre)++;
            mvpion=0;
            mvbarriere=0;
            if(menu->ordre==4)
            {
            infoPartie(player4,menu);
            }
            if(menu->ordre==3)
            {
            infoPartie(player3,menu);
            }
            if(menu->ordre==2)
            {
            infoPartie(player2,menu);
            }
            if(menu->ordre==1)
            {
            infoPartie(player1,menu);
            }
            break;

case 4:     //ANNULER ACTION
    ///S'il y a 2 joueurs
    if ((mvpion==1)&&(mvbarriere==0))
    {
        if (menu->nb_joueurs==2)
        {
            if ((menu->tour==1) || (menu->tour==2))
            {
                if(menu->ordre==2)
                {
                supprimerpiece(player2->position.x,player2->position.y);
                annuler2(player2);
                infoPartie(player2,menu);
                }
                if(menu->ordre==1)
                {
                supprimerpiece(player1->position.x,player1->position.y);
                annuler1(player1);
                infoPartie(player1,menu);
                }
            }
            else
            {
                if(menu->ordre==2)
                {
                supprimerpiece(player2->position.x,player2->position.y);
                annulerAction2(tabjeton2x, tabjeton2y, menu->tour, player2);
                infoPartie(player2,menu);
                }
                if(menu->ordre==1)
                {
                supprimerpiece(player1->position.x,player1->position.y);
                annulerAction2(tabjeton1x, tabjeton1y, menu->tour, player1);
                infoPartie(player1,menu);
                }
            }
        }
        else if (menu->nb_joueurs==4)
        {
            if ((menu->tour==1) || (menu->tour==2) || (menu->tour==3) || (menu->tour==4))
            {
                if(menu->ordre==4)
                {
                supprimerpiece(player4->position.x,player4->position.y);
                annuler4(player4);
                infoPartie(player4,menu);
                }
                if(menu->ordre==3)
                {
                supprimerpiece(player3->position.x,player3->position.y);
                annuler3(player3);
                infoPartie(player3,menu);
                }
                if(menu->ordre==2)
                {
                supprimerpiece(player2->position.x,player2->position.y);
                annuler2(player2);
                infoPartie(player2,menu);
                }
                if(menu->ordre==1)
                {
                supprimerpiece(player1->position.x,player1->position.y);
                annuler1(player1);
                infoPartie(player1,menu);
                }
            }
            else
            {
                if(menu->ordre==4)
                {
                supprimerpiece(player4->position.x,player4->position.y);
                annulerAction4(tabjeton4x, tabjeton4y, menu->tour, player4);
                infoPartie(player4,menu);
                }
                if(menu->ordre==3)
                {
                supprimerpiece(player3->position.x,player3->position.y);
                annulerAction4(tabjeton3x,tabjeton3y, menu->tour, player3);
                infoPartie(player3,menu);
                }
                if(menu->ordre==2)
                {
                supprimerpiece(player2->position.x,player2->position.y);
                annulerAction4(tabjeton2x, tabjeton2y, menu->tour, player2);
                infoPartie(player2,menu);
                }
                if(menu->ordre==1)
                {
                supprimerpiece(player1->position.x,player1->position.y);
                annulerAction4(tabjeton1x, tabjeton1y, menu->tour, player1);
                infoPartie(player1,menu);
                }
            }
        }
        mvpion=0;
    }
    else if ((mvbarriere==1)&&(mvpion==0))
    {
        Color(0,7);
        ///Horizontal
        if (sens[menu->tour]==1)
        {
            if(menu->ordre==4)
            {
                annulerBarriereH(player4,menu,tabbarrierex1,tabbarrierey1);
                infoPartie(player4,menu);
            }
            else if(menu->ordre==3)
            {
                annulerBarriereH(player3,menu,tabbarrierex1,tabbarrierey1);
                infoPartie(player3,menu);
            }
            else if(menu->ordre==2)
            {
                annulerBarriereH(player2,menu,tabbarrierex1,tabbarrierey1);
                infoPartie(player2,menu);
            }
            else if(menu->ordre==1)
            {
                annulerBarriereH(player1,menu,tabbarrierex1,tabbarrierey1);
                infoPartie(player1,menu);
            }
        }
        ///vertical
        else if (sens[menu->tour]==0)
        {
            if(menu->ordre==4)
            {
                annulerBarriereV(player4,menu,tabbarrierex1,tabbarrierey1);
                infoPartie(player4,menu);
            }
            else if(menu->ordre==3)
            {
                annulerBarriereV(player3,menu,tabbarrierex1,tabbarrierey1);
                infoPartie(player3,menu);
            }
            else if(menu->ordre==2)
            {
                annulerBarriereV(player2,menu,tabbarrierex1,tabbarrierey1);
                infoPartie(player2,menu);
            }
            else if(menu->ordre==1)
            {
                annulerBarriereV(player1,menu,tabbarrierex1,tabbarrierey1);
                infoPartie(player1,menu);
            }
        }
        mvbarriere=0;
    }
    else
    {
        gotoligcol(28, 0);
        printf("Vous ne pouvez pas annuler la derniere action");
        sleep(1);
        gotoligcol(28,0);
        printf("                                                ");
    }
        break;

case 5:     //QUITTER SAUVEGARDER
            retour=1;
            Color(12,0);
            if(menu->nb_joueurs==2)
            {
                sauvegardeb(tabbarrierex1,tabbarrierey1,tabbarrierex2,tabbarrierey2,sens);
                sauvegarde2(*player1,*player2,*menu);
                printf("Sauvegarde\n");
                for(i=0;i<5;i++)
                {
                printf("...");
                sleep(1);
                printf("......");
                }
            }

            else if(menu->nb_joueurs==4)
            {
                sauvegardeb(tabbarrierex1,tabbarrierey1,tabbarrierex2,tabbarrierey2,sens);
                sauvegarde4(*player1,*player2,*player3,*player4,*menu);
                printf("Sauvegarde\n");
                for(i=0;i<5;i++)
                {
                printf("...");
                sleep(1);
                printf("......");
                }
            }
            Color(15,0);
            break;

default:
        gotoligcol(28,0);
        printf("Il y a une erreur dans le choix\n");
        sleep(1);
        gotoligcol(28,0);
        printf("                                      ");
        break;
    }
}
}

//CHARGEMENT DES ANCIENS SCORE POUR 2 JOUEURS
void oldscore2(t_joueur *player1,t_joueur *player2,t_joueur *player11,t_joueur *player22,t_menu *menu)
{
    chargement2(player11,player22);

        //COMPARAISON SCORE 2 JOUEURS
        if(menu->nb_joueurs==2)
        {
                    //SCORE JOUEUR 1

            if(strcmp(player1->pseudo,player11->pseudo)==0)
        {
                                    gotoligcol(26,35);
            printf("Un score a ete trouve pour le joueur 1\n");
            player1->score=player11->score;
                                    gotoligcol(27,35);

            printf("Score Player1: %d\n", player1->score);
        }

         else if(strcmp(player1->pseudo,player22->pseudo)==0)
        {
                                    gotoligcol(26,35);

            printf("Un score a ete trouve pour le joueur 1\n");
            player1->score=player22->score;
                        gotoligcol(27,35);

            printf("Score Player1: %d\n", player1->score);
        }
        else
        {
                        gotoligcol(26,35);
                        printf("Aucun joueur de la base de donnees ne correspond au joueur 1 !\n");

        }
                    //SCORE JOUEUR 2

        if(strcmp(player2->pseudo,player11->pseudo)==0)
        {
                                    gotoligcol(26,35);

            printf("Un score a ete trouve pour le joueur 2\n");
            player2->score=player11->score;
                        gotoligcol(27,35);

            printf("Score Player2: %d\n", player2->score);
        }
         else if(strcmp(player2->pseudo,player22->pseudo)==0)
        {
                                    gotoligcol(26,35);

            printf("Un score a ete trouve pour le joueur 2\n");
            player2->score=player22->score;
                        gotoligcol(27,35);

            printf("Score Player2: %d\n", player2->score);
        }
        else
        {
            gotoligcol(27,35);
                        printf("Aucun joueur de la base de donnees ne correspond au joueur 2 !\n");
        }
        }
}

//CHARGEMENT DES ANCIENS SCORE POUR 4 JOUEURS
void oldscore4(t_joueur *player1,t_joueur *player2,t_joueur *player3,t_joueur *player4,t_joueur *player11,t_joueur *player22,t_joueur *player33,t_joueur *player44,t_menu *menu)
{
        chargement4(player11,player22,player33,player44);

        //COMPARAISON SCORE 4 JOUEURS
        if(menu->nb_joueurs==4)
        {
                    //SCORE JOUEUR 1

            if(strcmp(player1->pseudo,player11->pseudo)==0)
        {                        gotoligcol(26,35);

            printf("Un score a ete trouve pour le joueur 1\n");
            player1->score=player11->score;
                        gotoligcol(27,35);

            printf("Score Player1: %d", player1->score);
        }
         else if(strcmp(player1->pseudo,player22->pseudo)==0)
        {                        gotoligcol(26,35);

            printf("Un score a ete trouve pour le joueur 1\n");
 player1->score=player22->score;
                        gotoligcol(27,35);
            printf("Score Player1: %d", player1->score);
        }
         else if(strcmp(player1->pseudo,player33->pseudo)==0)
        {
                                    gotoligcol(26,35);

            printf("Un score a ete trouve pour le joueur 1\n");
            player1->score=player33->score;
                        gotoligcol(27,35);

            printf("Score Player1: %d", player1->score);
        }
         else if(strcmp(player1->pseudo,player44->pseudo)==0)
        {                        gotoligcol(26,35);

            printf("Un score a ete trouve pour le joueur 1\n");
            player1->score=player44->score;
                        gotoligcol(27,35);

            printf("Score Player1: %d", player1->score);
        }
         else
        {               gotoligcol(37,35);
                        printf("Aucun joueur de la base de donnees ne correspond au joueur 1 !\n");
        }


                    //SCORE JOUEUR 2

        if(strcmp(player2->pseudo,player11->pseudo)==0)
        {                        gotoligcol(28,35);

            printf("Un score a ete trouve pour le joueur 2\n");
            player2->score=player11->score;
gotoligcol(29,35);
            printf("Score Player2: %d", player2->score);
        }
         else if(strcmp(player2->pseudo,player22->pseudo)==0)
        {gotoligcol(28,35);
            printf("Un score a ete trouve pour le joueur 2\n");
            player2->score=player22->score;
gotoligcol(29,35);
            printf("Score Player2: %d", player2->score);
        }
         else if(strcmp(player2->pseudo,player33->pseudo)==0)
        {gotoligcol(28,35);
            printf("Un score a ete trouve pour le joueur 2\n");
            player2->score=player33->score;
            gotoligcol(29,35);

            printf("Score Player2: %d", player2->score);
        }
         else if(strcmp(player2->pseudo,player44->pseudo)==0)
        {            gotoligcol(28,35);

            printf("Un score a ete trouve pour le joueur 2\n");
            player2->score=player44->score;
            gotoligcol(29,35);

            printf("Score Player2: %d", player2->score);
        }
         else
        {
                        gotoligcol(38,35);
                        printf("Aucun joueur de la base de donnees ne correspond au joueur 2 !\n");
        }

                    //SCORE JOUEUR 3

        if(strcmp(player3->pseudo,player11->pseudo)==0)
        {
                        gotoligcol(30,35);

            printf("Un score a ete trouve pour le joueur 3\n");
            player3->score=player11->score;

            gotoligcol(31,35);

            printf("Score Player3: %d", player3->score);
        }
         else if(strcmp(player3->pseudo,player22->pseudo)==0)
        {
                        gotoligcol(30,35);

            printf("Un score a ete trouve pour le joueur 3\n");
            player3->score=player22->score;

            gotoligcol(31,35);
            printf("Score Player3: %d", player3->score);
        }
         else if(strcmp(player3->pseudo,player33->pseudo)==0)
        {            gotoligcol(30,35);
            printf("Un score a ete trouve pour le joueur 3\n");
            player3->score=player33->score;
            gotoligcol(31,35);
            printf("Score Player3: %d", player3->score);
        }
         else if(strcmp(player3->pseudo,player44->pseudo)==0)
        {
                        gotoligcol(30,35);

            printf("Un score a ete trouve pour le joueur 3\n");
            player3->score=player44->score;
            gotoligcol(31,35);

            printf("Score Player3: %d", player3->score);

        }
         else
        {
                        gotoligcol(39,35);
                        printf("Aucun joueur de la base de donnees ne correspond au joueur 3 !\n");
        }

                    //SCORE JOUEUR 4

        if(strcmp(player4->pseudo,player11->pseudo)==0)
        {            gotoligcol(32,35);

            printf("Un score a ete trouve pour le joueur 4\n");
            player4->score=player11->score;
gotoligcol(33,35);

            printf("Score Player4: %d", player4->score);

        }
         else if(strcmp(player4->pseudo,player22->pseudo)==0)
        {gotoligcol(32,35);

            printf("Un score a ete trouve pour le joueur 4\n");
            player2->score=player22->score;
gotoligcol(33,35);

            printf("Score Player4: %d", player4->score);
        }
         else if(strcmp(player2->pseudo,player33->pseudo)==0)
        {gotoligcol(32,35);

            printf("Un score a ete trouve pour le joueur 4\n");
            player4->score=player33->score;
gotoligcol(33,35);

            printf("Score Player4: %d", player4->score);
        }
         else if(strcmp(player4->pseudo,player44->pseudo)==0)
        {gotoligcol(32,35);

            printf("Un score a ete trouve pour le joueur 4\n");
            player4->score=player44->score;
gotoligcol(33,35);

            printf("Score Player4: %d", player4->score);
        }
         else
        {
                        gotoligcol(40,35);
                        printf("Aucun joueur de la base de donnees ne correspond au joueur 4 !\n");
        }
        }
}

//POSER UNE BARRIERE DANS LE TABLEAU
void poserbarriere(t_joueur *player,t_menu *menu, char tab[17][17],int tabbarrierex1[100], int tabbarrierey1[100], int tabbarrierex2[100], int tabbarrierey2[100], int sens[100])
{
    player->jetonbarriere='B';
    player->barriere--;

    if(player->barriere>0)
    {
    int sortie=0;
    int key;
    int reponse;
    int i;
    gotoligcol(27,0);
    Color(15,0);

    player->bposition.x=18;
    player->bposition.y=18;

    printf("Deplacement avec ZQSD, pose de la barriere avec ENTREE.");
    gotoligcol(28,0);
    do
    {
        printf("Voulez-vous une barriere horizontale ou verticale ? 1 ou 0\n");
        scanf("%d",&reponse);
    }while ((reponse!=0)&&(reponse!=1));


    //ON RECUPERE LE SENS DES BARRIERES
    sens[menu->tour]=reponse;

    sleep(1);
    gotoligcol(27,0);
    printf("                                                          ");
    gotoligcol(28,0);
    printf("                                                               ");
    gotoligcol(29,0);
    printf(" ");

    do
    {
        key= getch();

        switch(key)
        {
        case(122):         //Z  HAUT
            (player->bposition.x)--;
            gotoligcol(player->bposition.x,player->bposition.y);
            break;
        case(113):   //Q    GAUCHE
            (player->bposition.y)--;
            gotoligcol(player->bposition.x,player->bposition.y);
            break;
        case(115):   //S    BAS
            (player->bposition.x)++;
            gotoligcol(player->bposition.x,player->bposition.y);
            break;
        case(100):    //D   DROITE
            (player->bposition.y)++;
            gotoligcol(player->bposition.x,player->bposition.y);
            break;
        case(13):     //JETON
                Color(12,7);
            if(reponse==0)
            {
            fflush(stdin);
            tabbarrierex1[menu->tour]=player->bposition.x;
            tabbarrierey1[menu->tour]=player->bposition.y;
            tabbarrierex2[menu->tour]=player->bposition.x;
            tabbarrierey2[menu->tour]=(player->bposition.y);

            printf("%c\n",player->jetonbarriere);
            gotoligcol(player->bposition.x+1,player->bposition.y);
            printf("%c",player->jetonbarriere);
            gotoligcol(player->bposition.x-1,player->bposition.y);
            printf("%c",player->jetonbarriere);

            gotoligcol(player->bposition.x,player->bposition.y-1);
            printf("%c\n",player->jetonbarriere);
            gotoligcol(player->bposition.x+1,player->bposition.y-1);
            printf("%c",player->jetonbarriere);
            gotoligcol(player->bposition.x-1,player->bposition.y-1);
            printf("%c",player->jetonbarriere);
            }

            else if(reponse==1)
            {
            tabbarrierex1[menu->tour]=player->bposition.x;
            tabbarrierey1[menu->tour]=player->bposition.y;
            tabbarrierex2[menu->tour]=player->bposition.x;
            tabbarrierey2[menu->tour]=(player->bposition.y);
            for(i=0;i<6;i++)
            {
            gotoligcol(player->bposition.x,(player->bposition.y)+i);
            printf("%c",player->jetonbarriere);
            }
            }
            sortie=1;
            break;

        case(27):    //ECHAP
            sortie=1;
            break;

        default:
            gotoligcol(28,0);
            printf("Il y a une erreur dans le choix\n");
            sleep(1);
            gotoligcol(28,0);
            printf("                                     ");
            break;
        }
    }while((sortie==0)&&(player->bposition.x<18)&&(player->bposition.y<=36)&&((player->bposition.x>0)&&(player->bposition.y>0)));
    Color(15,0);
    }
    else
    {
        player->barriere=0;
        gotoligcol(28,0);
        printf("Vous n'avez plus de barrieres !\n");
        sleep(1);
        gotoligcol(28,0);
        printf("                                   ");
    }
}

//BLOQUER UNE BARRIERE DU TABLEAU
void bloquebarriere(t_joueur *player)
{
    if(((player->position.x)==(player->bposition.x))||((player->position.y)==(player->bposition.y)))
    {
        gotoligcol(28,0);
        printf("Vous ne pouvez pas poser de pion sur une barriere");
        gotoligcol(28,0);
        printf("                                                       ");
    }
}

//PASSER SON TOUR
void passerTour()
{
    gotoligcol(28,0);
    printf("Je passe mon tour");
    sleep(1);
    gotoligcol(28,0);
    printf("                          ");
}

//SAUTER UN PION POUR 2 JOUEURS
void sauterunpion2J(t_joueur*player1, t_joueur*player2,t_menu*menu)
{
    sauterunpion1p2(player1,player2,menu);
    sauterunpion2p2(player1,player2,menu);
}

//SAUTER UN PION J1 POUR J2
void sauterunpion1p2(t_joueur *player1, t_joueur *player2,t_menu*menu)
{

    if(menu->ordre==1)
    {

        if((player1->position.x==player2->position.x)&&(player1->position.y==player2->position.y)) //joueurs 1 et 2
        {
            if(((player1->tabx[menu->tour-2])-(player1->tabx[menu->tour]))>0) //joueur monte
            {
                (player1->position.x)-=2;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }

            if(((player1->tabx[menu->tour-2])-(player1->tabx[menu->tour]))<0) //joueur descend
            {
                (player1->position.x)+=2;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }

            if(((player1->taby[menu->tour-2])-(player1->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player1->position.y)-=4;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }


            if(((player1->taby[menu->tour-2])-(player1->taby[menu->tour]))<0) //joueur va a droite
            {
                (player1->position.y)+=4;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }
        }
    }
}

//SAUTER UN PION J2 POUR J2
void sauterunpion2p2(t_joueur*player1,t_joueur*player2,t_menu*menu)
{

    if(menu->ordre==2)
    {

        if((player1->position.x==player2->position.x)&&(player1->position.y==player2->position.y))
        {


            if(((player2->tabx[menu->tour-2])-(player2->tabx[menu->tour]))>0) //joueur monte
            {
                (player2->position.x)-=2;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }

            if(((player2->tabx[menu->tour-2])-(player2->tabx[menu->tour]))<0) //joueur descend
            {
                (player2->position.x)+=2;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }

            if(((player2->taby[menu->tour-2])-(player2->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player2->position.y)-=4;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }


            if(((player2->taby[menu->tour-2])-(player2->taby[menu->tour]))<0) //joueur va a droite
            {
                (player2->position.y)+=4;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }
        }
    }

}

//SAUTER UN PION POUR 4 JOUEURS
void sauterunpion4J(t_joueur *player1, t_joueur *player2,t_joueur*player3, t_joueur*player4,t_menu*menu)
{
    sauterunpion1(player1,player2,player3,player4,menu);
    sauterunpion2(player1,player2,player3,player4,menu);
    sauterunpion3(player1,player2,player3,player4,menu);
    sauterunpion4(player1,player2,player3,player4,menu);
}

//SAUTER UN PION POUR LE J1
void sauterunpion1(t_joueur *player1, t_joueur *player2,t_joueur*player3, t_joueur*player4,t_menu*menu)
{

    if(menu->ordre==1)
    {

        if((player1->position.x==player2->position.x)&&(player1->position.y==player2->position.y)) //joueurs 1 et 2
        {
            if(((player1->tabx[menu->tour-4])-(player1->tabx[menu->tour]))>0) //joueur monte
            {
                (player1->position.x)-=2;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }

            if(((player1->tabx[menu->tour-4])-(player1->tabx[menu->tour]))<0) //joueur descend
            {
                (player1->position.x)+=2;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }

            if(((player1->taby[menu->tour-4])-(player1->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player1->position.y)-=4;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }


            if(((player1->taby[menu->tour-4])-(player1->taby[menu->tour]))<0) //joueur va a droite
            {
                (player1->position.y)+=4;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }
        }

        if((player1->position.x==player3->position.x)&&(player1->position.y==player3->position.y)) //joueurs 1 et 3
        {
            if(((player1->tabx[menu->tour-4])-(player1->tabx[menu->tour]))>0) //joueur monte
            {
                (player1->position.x)-=2;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
            }

            if(((player1->tabx[menu->tour-4])-(player1->tabx[menu->tour]))<0) //joueur descend
            {
                (player1->position.x)+=2;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
            }

            if(((player1->taby[menu->tour-4])-(player1->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player1->position.y)-=4;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
            }


            if(((player1->taby[menu->tour-4])-(player1->taby[menu->tour]))<0) //joueur va a droite
            {
                (player1->position.y)+=4;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player3->position.x,player2->position.y);
                printf("%c",player3->jeton);
            }
        }


        if((player1->position.x==player4->position.x)&&(player1->position.y==player4->position.y)) //joueurs 1 et 4
        {
            if(((player1->tabx[menu->tour-4])-(player1->tabx[menu->tour]))>0) //joueur monte
            {
                (player1->position.x)-=2;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }

            if(((player1->tabx[menu->tour-4])-(player1->tabx[menu->tour]))<0) //joueur descend
            {
                (player1->position.x)+=2;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }

            if(((player1->taby[menu->tour-4])-(player1->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player1->position.y)-=4;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }


            if(((player1->taby[menu->tour-4])-(player1->taby[menu->tour]))<0) //joueur va a droite
            {
                (player1->position.y)+=4;
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }
        }
    }




}

//SAUTER UN PION POUR LE J2
void sauterunpion2(t_joueur *player1, t_joueur *player2,t_joueur*player3, t_joueur*player4,t_menu*menu)
{

    if(menu->ordre==2)
    {

        if((player1->position.x==player2->position.x)&&(player1->position.y==player2->position.y))
        {


            if(((player2->tabx[menu->tour-4])-(player2->tabx[menu->tour]))>0) //joueur monte
            {
                (player2->position.x)-=2;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }

            if(((player2->tabx[menu->tour-4])-(player2->tabx[menu->tour]))<0) //joueur descend
            {
                (player2->position.x)+=2;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }

            if(((player2->taby[menu->tour-4])-(player2->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player2->position.y)-=4;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }


            if(((player2->taby[menu->tour-4])-(player2->taby[menu->tour]))<0) //joueur va a droite
            {
                (player2->position.y)+=4;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }
        }

        if((player2->position.x==player3->position.x)&&(player2->position.y==player3->position.y)) //joueurs 1 et 3
        {
            if(((player2->tabx[menu->tour-4])-(player2->tabx[menu->tour]))>0) //joueur monte
            {
                (player2->position.x)-=2;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
            }

            if(((player2->tabx[menu->tour-4])-(player2->tabx[menu->tour]))<0) //joueur descend
            {
                (player2->position.x)+=2;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
            }

            if(((player2->taby[menu->tour-4])-(player2->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player2->position.y)-=4;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
            }


            if(((player2->taby[menu->tour-4])-(player2->taby[menu->tour]))<0) //joueur va a droite
            {
                (player2->position.y)+=4;
                gotoligcol(player2->position.x,player1->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player3->position.x,player2->position.y);
                printf("%c",player3->jeton);
            }
        }


        if((player2->position.x==player4->position.x)&&(player2->position.y==player4->position.y)) //joueurs 1 et 4
        {
            if(((player2->tabx[(menu->tour)-4])-(player2->tabx[menu->tour]))>0) //joueur monte
            {
                (player2->position.x)-=2;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }

            if(((player2->tabx[menu->tour-4])-(player2->tabx[menu->tour]))<0) //joueur descend
            {
                (player2->position.x)+=2;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }

            if(((player2->taby[menu->tour-4])-(player2->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player2->position.y)-=4;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }


            if(((player2->taby[menu->tour-4])-(player2->taby[menu->tour]))<0) //joueur va a droite
            {
                (player2->position.y)+=4;
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }

        }
    }




}

//SAUTER UN PION POUR LE J3
void sauterunpion3(t_joueur *player1, t_joueur *player2,t_joueur*player3, t_joueur*player4,t_menu*menu)
{

    if(menu->ordre==3)
    {

        if((player3->position.x==player1->position.x)&&(player3->position.y==player1->position.y))
        {


            if(((player3->tabx[menu->tour-4])-(player3->tabx[menu->tour]))>0) //joueur monte
            {
                (player3->position.x)-=2;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }

            if(((player3->tabx[menu->tour-4])-(player3->tabx[menu->tour]))<0) //joueur descend
            {
                (player3->position.x)+=2;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }

            if(((player3->taby[menu->tour-4])-(player3->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player3->position.y)-=4;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }


            if(((player3->taby[menu->tour-4])-(player3->taby[menu->tour]))<0) //joueur va a droite
            {
                (player3->position.y)+=4;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }
        }

        if((player2->position.x==player3->position.x)&&(player2->position.y==player3->position.y)) //joueurs 1 et 3
        {
            if(((player3->tabx[menu->tour-4])-(player3->tabx[menu->tour]))>0) //joueur monte
            {
                (player3->position.x)-=2;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }

            if(((player3->tabx[menu->tour-4])-(player3->tabx[menu->tour]))<0) //joueur descend
            {
                (player3->position.x)+=2;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }

            if(((player3->taby[menu->tour-4])-(player3->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player3->position.y)-=4;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }


            if(((player3->taby[menu->tour-4])-(player3->taby[menu->tour]))<0) //joueur va a droite
            {
                (player3->position.y)+=4;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }
        }


        if((player3->position.x==player4->position.x)&&(player3->position.y==player4->position.y)) //joueurs 1 et 4
        {
            if(((player3->tabx[menu->tour-4])-(player3->tabx[menu->tour]))>0) //joueur monte
            {
                (player3->position.x)-=2;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }

            if(((player3->tabx[menu->tour-4])-(player3->tabx[menu->tour]))<0) //joueur descend
            {
                (player3->position.x)+=2;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }

            if(((player3->taby[menu->tour-4])-(player3->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player3->position.y)-=4;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }


            if(((player3->taby[menu->tour-4])-(player3->taby[menu->tour]))<0) //joueur va a droite
            {
                (player3->position.y)+=4;
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
            }
        }
    }




}

//SAUTER UN PION POUR LE J4
void sauterunpion4(t_joueur *player1, t_joueur *player2,t_joueur*player3, t_joueur*player4,t_menu*menu)
{

    if(menu->ordre==4)
    {

        if((player4->position.x==player1->position.x)&&(player4->position.y==player1->position.y))
        {



            if(((player4->tabx[menu->tour-4])-(player4->tabx[menu->tour]))>0) //joueur monte
            {
                (player4->position.x)-=2;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }

            if(((player4->tabx[menu->tour-4])-(player4->tabx[menu->tour]))<0) //joueur descend
            {
                (player4->position.x)+=2;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }

            if(((player4->taby[menu->tour-4])-(player4->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player4->position.y)-=4;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }


            if(((player4->taby[menu->tour-4])-(player4->taby[menu->tour]))<0) //joueur va a droite
            {
                (player4->position.y)+=4;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player1->position.x,player1->position.y);
                printf("%c",player1->jeton);
            }
        }

        if((player4->position.x==player3->position.x)&&(player4->position.y==player3->position.y)) //joueurs 1 et 3
        {
            if(((player4->tabx[menu->tour-4])-(player4->tabx[menu->tour]))>0) //joueur monte
            {
                (player4->position.x)-=2;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
            }

            if(((player4->tabx[menu->tour-4])-(player4->tabx[menu->tour]))<0) //joueur descend
            {
                (player4->position.x)+=2;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
            }

            if(((player4->taby[menu->tour-4])-(player4->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player4->position.y)-=4;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
            }


            if(((player4->taby[menu->tour-4])-(player4->taby[menu->tour]))<0) //joueur va a droite
            {
                (player4->position.y)+=4;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player3->position.x,player3->position.y);
                printf("%c",player3->jeton);
            }
        }


        if((player2->position.x==player4->position.x)&&(player2->position.y==player4->position.y)) //joueurs 1 et 4
        {
            if(((player4->tabx[menu->tour-4])-(player4->tabx[menu->tour]))>0) //joueur monte
            {
                (player4->position.x)-=2;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }

            if(((player4->tabx[menu->tour-4])-(player4->tabx[menu->tour]))<0) //joueur descend
            {
                (player4->position.x)+=2;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }

            if(((player4->taby[menu->tour-4])-(player4->taby[menu->tour]))>0) //joueur va a gauche
            {
                (player4->position.y)-=4;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }


            if(((player4->taby[menu->tour-4])-(player4->taby[menu->tour]))<0) //joueur va a droite
            {
                (player4->position.y)+=4;
                gotoligcol(player4->position.x,player4->position.y);
                printf("%c",player4->jeton);
                gotoligcol(player2->position.x,player2->position.y);
                printf("%c",player2->jeton);
            }
        }
    }
}

//ANNULER LACTION POUR 2 JOUEURS
void annulerAction2(int *tabanulx, int *tabanuly, int tour, t_joueur *player)
{
    gotoligcol(tabanulx[tour-2], tabanuly[tour-2]);
    printf("%c",player->jeton);

    gotoligcol(28,0);
    printf("L'action a ete annulee");
    sleep(1);
    gotoligcol(28,0);
    printf("                          ");
}

//ANNULER LACTION POUR 4 JOUEURS
void annulerAction4(int *tabanulx, int *tabanuly, int tour, t_joueur *player)
{
    gotoligcol(tabanulx[tour-4], tabanuly[tour-4]);
    printf("%c",player->jeton);

    gotoligcol(28,0);
    printf("L'action a ete annulee");
    sleep(1);
    gotoligcol(28,0);
    printf("                          ");
}

//ANNULER LACTION POUR J1
void annuler1(t_joueur *player1)
{
    player1->position.x=17;
    player1->position.y=18;

    gotoligcol(player1->position.x, player1->position.y);
    printf("%c", player1->jeton);
}

//ANNULER LACTION POUR J2
void annuler2(t_joueur *player2)
{
    player2->position.x=1;
    player2->position.y=18;

    gotoligcol(player2->position.x, player2->position.y);
    printf("%c", player2->jeton);
}

//ANNULER LACTION POUR J3
void annuler3(t_joueur *player3)
{
    player3->position.x=9;
    player3->position.y=2;

    gotoligcol(player3->position.x, player3->position.y);
    printf("%c", player3->jeton);
}


//ANNULER LACTION POUR J4
void annuler4(t_joueur *player4)
{
    player4->position.x=9;
    player4->position.y=34;

    gotoligcol(player4->position.x, player4->position.y);
    printf("%c", player4->jeton);
}

//ANNULER BARRIERE HORIZONTALE
void annulerBarriereH(t_joueur *player, t_menu *menu, int tabbarrierex[100], int tabbarrierey[100])
{
    int i;

    tabbarrierex[menu->tour]=player->bposition.x;
    tabbarrierey[menu->tour]=player->bposition.y;

    for(i=0;i<6;i++)
    {
        gotoligcol(player->bposition.x,(player->bposition.y)+i);
        printf(" ");
    }

    player->barriere++;
}

//ANNULER BARRIERE VERTICALE
void annulerBarriereV(t_joueur *player, t_menu *menu, int tabbarrierex[100], int tabbarrierey[100])
{
    tabbarrierex[menu->tour]=player->bposition.x;
    tabbarrierey[menu->tour]=player->bposition.y;

    gotoligcol(player->bposition.x,player->bposition.y);
    printf(" ");
    gotoligcol(player->bposition.x+1,player->bposition.y);
    printf(" ");
    gotoligcol(player->bposition.x-1,player->bposition.y);
    printf(" ");

    gotoligcol(player->bposition.x,player->bposition.y-1);
    printf(" ");
    gotoligcol(player->bposition.x+1,player->bposition.y-1);
    printf(" ");
    gotoligcol(player->bposition.x-1,player->bposition.y-1);
    printf(" ");

    player->barriere++;
}

//AFFICHER L'AIDE
void aide()
{
    Color(13,0);
    gotoligcol(2,45);
    printf("AIDE DU JEU QUORIDOR\n");
    Color(15,0);
    printf("\n");

    FILE *fp=NULL;
    char c;
    int choix;
    fp=fopen("aide.txt","rt");

    if (fp==NULL)
    {
        printf("Il y a une erreur d'ouverture de fichier\n");
    }
    else
    {
    while((c=fgetc(fp))!=EOF)
    {
        printf("%c",c);
    }
        fclose(fp);
    }
        do
        {
            printf("\n");
            printf("\n");
            Color(9,0);
            printf("Voulez-vous retourner au menu ;) ? Tapez 0\n");
            scanf("%d",&choix);
            Color(15,0);
            menu();
        }while(choix!=0);
}

//CHARGER LES DONNEES JOUEURS SAUVEGARDE
void chargement(t_joueur *player1,t_joueur *player2, t_joueur *player3, t_joueur *player4, t_menu *menu)
{
        FILE *fp;
        fp=fopen("save.txt", "r");

        if(fp==(NULL))
        {
            printf("Erreur lors de l'ouverture du fichier");
            exit(1);
        }

        fscanf(fp,"Nombre de joueurs: %d\n",&menu->nb_joueurs);
        fscanf(fp,"Ordre: %d\n",&menu->ordre);
        fscanf(fp,"Tour: %d\n",&menu->tour);
        fscanf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player1->pseudo, &player1->score, &player1->jeton, &player1->barriere,&player1->position.x,&player1->position.y);
        fscanf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player2->pseudo, &player2->score, &player2->jeton, &player2->barriere,&player2->position.x,&player2->position.y);
        fscanf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player3->pseudo, &player3->score, &player3->jeton, &player3->barriere,&player3->position.x,&player3->position.y);
        fscanf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player4->pseudo, &player4->score, &player4->jeton, &player4->barriere,&player4->position.x,&player4->position.y);

        fclose(fp);
}

//CHARGER LES DONNEES DE 4 JOUEURS SAUVEGARDE
void chargement4(t_joueur *player1,t_joueur *player2, t_joueur *player3, t_joueur *player4)
{
        FILE *fp;
        fp=fopen("save.txt", "r");

        if(fp==(NULL))
        {
            printf("Erreur lors de l'ouverture du fichier");
            exit(1);
        }
        fscanf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player1->pseudo, &player1->score, &player1->jeton, &player1->barriere,&player1->position.x,&player1->position.y);
        fscanf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player2->pseudo, &player2->score, &player2->jeton, &player2->barriere,&player2->position.x,&player2->position.y);
        fscanf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player3->pseudo, &player3->score, &player3->jeton, &player3->barriere,&player3->position.x,&player3->position.y);
        fscanf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player4->pseudo, &player4->score, &player4->jeton, &player4->barriere,&player4->position.x,&player4->position.y);

        fclose(fp);
}

//CHARGER LES DONNEES DE 2 JOUEURS SAUVEGARDE
void chargement2(t_joueur *player1,t_joueur *player2)
{
        FILE *fp;
        fp=fopen("save.txt", "r");

        if(fp==(NULL))
        {
            printf("Erreur lors de l'ouverture du fichier");
            exit(1);
        }
        fscanf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player1->pseudo, &player1->score, &player1->jeton, &player1->barriere,&player1->position.x,&player1->position.y);
        fscanf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player2->pseudo, &player2->score, &player2->jeton, &player2->barriere,&player2->position.x,&player2->position.y);
        fclose(fp);
}

//CHARGER LES BARRIERES SAUVEGARDE
void chargementb(int tabbarrierex1[100],int tabbarrierey1[100],int tabbarrierex2[100],int tabbarrierey2[100],int sens[100])
{
    FILE*fp=NULL;
    int i;
    fp=fopen("saveb.txt","r");

    if(fp==NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    else
    {
        for(i=0;i<100;i++)
        {
        fscanf(fp,"Positionx1: %d\tPositiony1: %d\tPositionx2: %d\tPositiony2: %d\t: Sens: %d\n",&tabbarrierex1[i],&tabbarrierey1[i],&tabbarrierex2[i],&tabbarrierey2[i],&sens[i]);
        }
    }
    fclose(fp);
}

//SAUVEGARDE DES BARRIERES
void sauvegardeb(int tabbarrierex1[100],int tabbarrierey1[100], int tabbarrierex2[100],int tabbarrierey2[100], int sens[100])
{
    FILE *fp=NULL;
    fp=fopen("saveb.txt","w");
    int i;
    if(fp==NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    else
    {
    for(i=0;i<100;i++)
    {
        fprintf(fp,"Positionx1: %d\tPositiony1: %d\tPositionx2: %d\tPositiony2: %d\t: Sens: %d\n",tabbarrierex1[i],tabbarrierey1[i],tabbarrierex2[i],tabbarrierey2[i],sens[i]);
    }
    }
    fclose(fp);
}

//SAUVEGARDE DES DEPLACEMENTS JOUEURS
void sauvegardep(int tabx[100], int taby[100])
{
    FILE *fp=NULL;
    fp=fopen("savep.txt","w");
    int i;
    if(fp==NULL)
    {
        printf("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    else
    {
    for(i=0;i<100;i++)
    {
        fprintf(fp,"Positionx: %d\tPositiony: %d",tabx[i],taby[i]);
    }
    }
    fclose(fp);
}

//SAUVEGARDE 4 JOUEURS
void sauvegarde4(t_joueur player1, t_joueur player2, t_joueur player3, t_joueur player4, t_menu menu)
{
    FILE *fp=NULL;
    fp=fopen("save.txt","w");

    if (fp==NULL)
    {
        printf("Il y a une erreur d'ouverture de fichier\n");
    }
    else
    {
            fprintf(fp,"Nombre de joueurs: %d\n",menu.nb_joueurs);
            fprintf(fp,"Ordre: %d\n",menu.ordre);
            fprintf(fp,"Tour: %d\n",menu.tour);
            fprintf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player1.pseudo, player1.score, player1.jeton, player1.barriere,player1.position.x,player1.position.y);
            fprintf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player2.pseudo, player2.score, player2.jeton, player2.barriere,player2.position.x,player2.position.y);
            fprintf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player3.pseudo, player3.score, player3.jeton, player3.barriere,player3.position.x,player3.position.y);
            fprintf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player4.pseudo, player4.score, player4.jeton, player4.barriere,player4.position.x,player4.position.y);
    }
        fclose(fp);
}

//SAUVEGARDE 2 JOUEURS
void sauvegarde2(t_joueur player1,t_joueur player2, t_menu menu)
{
    FILE *fp=NULL;
    fp=fopen("save.txt","w");

    if (fp==NULL)
    {
        printf("Il y a une erreur d'ouverture de fichier\n");
    }
    else
    {
            fprintf(fp,"Nombre de joueurs: %d\n",menu.nb_joueurs);
            fprintf(fp,"Ordre: %d\n",menu.ordre);
            fprintf(fp,"Tour: %d\n",menu.tour);
            fprintf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player1.pseudo, player1.score, player1.jeton, player1.barriere,player1.position.x,player1.position.y);
            fprintf(fp,"Pseudo: %s\tScore: %d\tJeton: %c\tBarrieres: %d\tPositionX: %d\tPositionY: %d\n",player2.pseudo, player2.score, player2.jeton, player2.barriere,player2.position.x,player2.position.y);
    }
        fclose(fp);
}

//AFFICHAGE DU QUORIDOR GRAPHIQUE
void QUORIDOR()
{
    Color(9,0);
    FILE *fp=NULL;
    char c;
    fp=fopen("quoridor.txt","rt");

    if (fp==NULL)
    {
        printf("Il y a une erreur d'ouverture de fichier\n");
    }
    else
    {
    while((c=fgetc(fp))!=EOF)
    {
        printf("%c",c);
    }
        fclose(fp);
    }
    Color(15,0);
}

//AFFICHAGE DU MESSAGE DE FIN GRAPHIQUE
void END()
{
    FILE *fp=NULL;
    char c;
    fp=fopen("end.txt","rt");

    if (fp==NULL)
    {
        printf("Il y a une erreur d'ouverture de fichier\n");
    }
    else
    {
    while((c=fgetc(fp))!=EOF)
    {
        printf("%c",c);
    }
        fclose(fp);
    }
}

//AFFICHAGE DU DE GRAPHIQUE
void DE()
{
     FILE *fp=NULL;
    char c;
    fp=fopen("de.txt","rt");

    if (fp==NULL)
    {
        printf("Il y a une erreur d'ouverture de fichier\n");
    }
    else
    {
    while((c=fgetc(fp))!=EOF)
    {
        printf("%c",c);
    }
        fclose(fp);
    }
}

//REPRISE DE LA PARTIE
void reprise(t_joueur *player1, t_joueur *player2, t_joueur *player3, t_joueur *player4, t_menu *menuu,int tabbarrierex1[100],int tabbarrierey1[100],int tabbarrierex2[100],int tabbarrierey2[100],int sens[100])
{
        char tab[17][17];
        int i,j;
        int choix;

        chargement(player1,player2,player3,player4,menuu);
        chargementb(tabbarrierex1, tabbarrierey1, tabbarrierex2, tabbarrierey2, sens);

        system("cls");
        plateau();

        if(menuu->nb_joueurs==2)
        {
        gotoligcol(player1->position.x,player1->position.y);
        printf("%c",player1->jeton);

        gotoligcol(player2->position.x,player2->position.y);
        printf("%c",player2->jeton);
        }

        if(menuu->nb_joueurs==4)
        {
        gotoligcol(player1->position.x,player1->position.y);
        printf("%c",player1->jeton);

        gotoligcol(player2->position.x,player2->position.y);
        printf("%c",player2->jeton);

        gotoligcol(player3->position.x,player3->position.y);
        printf("%c",player3->jeton);

        gotoligcol(player4->position.x,player4->position.y);
        printf("%c",player4->jeton);
        }

        for(i=0;i<100;i++)
        {
                Color(12,7);

            if(sens[i]==0)
            {
            gotoligcol(tabbarrierex1[i],tabbarrierey1[i]);
            printf("B");
            gotoligcol(tabbarrierex1[i]+1,tabbarrierey1[i]);
            printf("B");
            gotoligcol(tabbarrierex1[i]-1,tabbarrierey1[i]);
            printf("B");

            gotoligcol(tabbarrierex1[i],tabbarrierey1[i]-1);
            printf("B");
            gotoligcol(tabbarrierex1[i]+1,tabbarrierey1[i]-1);
            printf("B");
            gotoligcol(tabbarrierex1[i]-1,tabbarrierey1[i]-1);
            printf("B");
            }

            if(sens[i]==1)
            {
            for(j=0;j<6;j++)
            {
            gotoligcol(tabbarrierex1[i],tabbarrierey1[i]+j);
            printf("B");
            }
            }
        }
        Color(15,0);

        if(menuu->ordre==4)
        {
            infoPartie(player4,menuu);
        }
        if(menuu->ordre==3)
        {
            infoPartie(player3,menuu);
        }
        if(menuu->ordre==2)
        {
            infoPartie(player2,menuu);
        }
        if(menuu->ordre==1)
        {
            infoPartie(player1,menuu);
        }
        menujeu(player1,player2,player3,player4,menuu,tab, tabbarrierex1,tabbarrierey1,tabbarrierex2,tabbarrierey2,sens);


        do
        {
            printf("Voulez-vous vraiment retourner au menu ;) ? Tapez 0\n");
            scanf("%d",&choix);
            menu();
        }while(choix!=0);

}

//ENREGISTREMENT DU SCORE A PEAUFINER
void score(t_joueur *player1, t_joueur *player2, t_joueur *player3, t_joueur *player4)
{
    FILE *fp=NULL;
    char c;
    fp=fopen("score.txt","r+");

    if (fp==NULL)
    {
        printf("Il y a une erreur d'ouverture de fichier\n");
    }
    else
    {
    while((c=fgetc(fp))!=EOF)
    {
        fscanf(fp,"%s",player1->pseudo);
        fscanf(fp,"%s",player2->pseudo);
        fscanf(fp,"%s",player3->pseudo);
        fscanf(fp,"%s",player4->pseudo);

        fscanf(fp,"%d",&(player1->score));
        fscanf(fp,"%d",&(player2->score));
        fscanf(fp,"%d",&(player3->score));
        fscanf(fp,"%d",&(player4->score));

        printf("%c\n",c);
        printf("Joueurs: %s Scores: %d \n",player1->pseudo,player1->score);
        printf("Joueurs: %s Scores: %d \n",player2->pseudo,player2->score);
        printf("Joueurs: %s Scores: %d \n",player3->pseudo,player3->score);
        printf("Joueurs: %s Scores: %d \n",player4->pseudo,player4->score);
    }
        fclose(fp);
    }
}

//CHRONOMETRE
void temps()
{
    int sec=99;

    while(sec>0)
    {
        gotoligcol(20,50);
        printf("Timer : %d",sec);
        sec--;
        sleep(1);
    }
}

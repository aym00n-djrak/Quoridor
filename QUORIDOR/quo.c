#include <windows.h>
void placer(int x, int y);

typedef struct joueur
{
 char pseudo;
 int barriere;
 int score;
 char jeton;
}t_joueur;

typedef struct menu
{
    char titre;
    char aide;
    int score[100];
    int nb_joueurs;
}t_menu;

typedef struct mapiece
{
    char x;
    char y;
 t_joueur typepiece;
}t_mapiece;

typedef struct monplateau
{
    int nbcase;
    char couleur;
    char barriere;
    char unecase;
}t_monplateau;


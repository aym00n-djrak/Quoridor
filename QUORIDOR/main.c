#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
void menu();


int main()
{
    int gagner=0;
    do
    {
    srand(time(NULL));
    menu();
    }while(gagner==1);
return 0;
}


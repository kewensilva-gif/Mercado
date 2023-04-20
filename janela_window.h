#include "gconio.h"
#include <iostream>
using namespace std;
void borda1(int x, int y,int xVezes, int yVezes, int cor)
{
    int i,j;
    textcolor(cor);

      gotoxy(x,y);
        printf("%c",201);

    for (i=0; i<xVezes; i++)
        printf("%c",205);
    printf("%c",187);

    xVezes+=x + 1;
    y++;
    gotoxy(x,y);
    j = 2;

    for (i=y; j<yVezes; i++,j++)
    {
        gotoxy(x,i);
        printf("%c",186);
        gotoxy(xVezes,i);
        printf("%c",186);
    }

    gotoxy(x,i);
    printf("%c",200);
    gotoxy(xVezes,i);
    printf("%c",188);
    gotoxy(x+1,i);

    xVezes = xVezes - x - 1;

    for (i=0; i<xVezes; i++)
        printf("%c",205);
}

void Animacao_Loading()
{
    gotoxy(80,30);
    printf("CARREGANDO ");
    textbackground(DARKGRAY);
    gotoxy(91,30);
    printf("     ");
    gotoxy(91,30);
    gotoxy(91,50);

}


void exibir_mercadoUFS()
{
    textbackground(DARKGRAY);
    system("CLS");

    gotoxy(15,1); cout<<" ##   ##  #######  ######     ####     ##     #####     #####                              ##   ##  #######   #####                  ";
    gotoxy(15,2); cout<<" ### ###   ##   #   ##  ##   ##  ##   ####     ## ##   ##   ##                             ##   ##   ##   #  ##   ##                 ";
    gotoxy(15,3); cout<<" #######   ## #     ##  ##  ##       ##  ##    ##  ##  ##   ##                             ##   ##   ## #    #                       ";
    gotoxy(15,4); cout<<" #######   ####     #####   ##       ##  ##    ##  ##  ##   ##           ######            ##   ##   ####     #####            ######";
    gotoxy(15,5); cout<<" ## # ##   ## #     ## ##   ##       ######    ##  ##  ##   ##                             ##   ##   ## #         ##                 ";
    gotoxy(15,6); cout<<" ##   ##   ##   #   ##  ##   ##  ##  ##  ##    ## ##   ##   ##                             ##   ##   ##      ##   ##                 ";
    gotoxy(15,7); cout<<" ##   ##  #######  #### ##    ####   ##  ##   #####     #####                               #####   ####      #####                  ";

   getch();
   Animacao_Loading();

}


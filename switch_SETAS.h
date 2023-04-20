int arrow(int &op, int &INICIO_DE_LINHA, int &FIM_DE_LINHA)
{

    int coluna = 62;
    int linha  = INICIO_DE_LINHA;
    int Enter  = 1;
    int joystick;

    do
    {
        ///seta cima = 72
        ///direita = 77
        ///esqueda = 75
        ///baixo = 80
        ///ESC   = 27

        /// abaixo aparece "|-|" inicialmente no programa;
        gotoxy(coluna,linha);
        textbackground(BLACK);
        textcolor(WHITE);
        printf("|");
        ///-------------------///
        gotoxy(coluna+46,linha);
        printf("|");
        joystick = getch();

        if(joystick == 13)
        {
            ///printf("%d",Enter);
            fflush(stdin);
            gotoxy(69,30);
            return Enter;
        }
        /// abaixo desaparece "|-|"

        if(joystick = 224)
        {
            joystick = getch();
            if(joystick == 72 && linha > INICIO_DE_LINHA)
            {
                gotoxy(coluna,linha);
                textbackground(DARKGRAY);
                printf(" ");
                ///--------------------///
                gotoxy(coluna+46,linha);
                printf(" ");
                linha--;
                /// abaixo aparece "|-|"
                gotoxy(coluna,linha);
                textbackground(BLACK);
                textcolor(WHITE);
                printf("|");
                ///-------------------///
                gotoxy(coluna+46,linha);
                printf("|");
                Enter--;
            }
                ///abaixo desaparece "|-|"

            else if(joystick == 80 && linha < FIM_DE_LINHA)
            {
                gotoxy(coluna,linha);
                textbackground(DARKGRAY);
                printf(" ");
                ///-----------------------///
                gotoxy(coluna+46,linha);
                printf(" ");
                linha++;
                /// abaixo aparece "|-|"
                gotoxy(coluna,linha);
                textbackground(BLACK);
                textcolor(WHITE);
                printf("|");
                ///-------------------///
                gotoxy(coluna+46,linha);
                printf("|");
                Enter++;
            }
        }
    }
    while(joystick != 27);
    return NULL;
}

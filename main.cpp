#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>

#include "janela_window.h"
#include "switch_SETAS.h"

#include "libMain.h"
#include "Cliente.h"
#include "libArquivos.h"
#include "libJSON.h"
#include "libTXT.h"
#include "libCaixa.h"
#include "libCases.h"

#include "gconio.h"


using namespace std;

int main()
{
    system("MODE con cols=180 lines=60");

    int COR_FUNDO=BLUE;
    int COR_LETRA=WHITE;

    int *INICIO_DE_LINHA = new(int);
    int *FIM_DE_LINHA    = new(int);
    int * fim3 = new(int);
    *INICIO_DE_LINHA = 22;
    *FIM_DE_LINHA    = 26;

    int opMain, opEst, opCad, opCaixa;

    struct estoque produtos;
    struct notaFiscal dados;

    do{
        bordaFunction();
        menuPrincipal(opMain);
        opMain = arrow(opMain,*INICIO_DE_LINHA,*FIM_DE_LINHA);

        switch(opMain){
        case 1:
            do{
                bordaFunction();
                float debito;

                menuCadastro(opCad);
                opCad = arrow(opCad,*INICIO_DE_LINHA,*FIM_DE_LINHA);

                switch(opCad){
                case 1:
                    bordaFunction();
                    cadastrarCliente();
                    break;
                case 2:
                    visualizarClientes();
                    break;
                case 3:
                    excluir();
                    break;
                case 4:
                    excluir(&debito);;
                }
            } while(opCad != 5);

            break;
        case 2:
            do{
                *INICIO_DE_LINHA = 21;
                *FIM_DE_LINHA    = 26;
                menuEstoque(opEst);
                opEst = arrow(opEst,*INICIO_DE_LINHA,*FIM_DE_LINHA);
                *INICIO_DE_LINHA = 22;
                *FIM_DE_LINHA = 25;

                switch(opEst){

                case 1:
                    criarListaCase(produtos);
                    break;

                case 2:
                    inserirProdutoCase(produtos);
                    break;

                case 3:
                    removerItemCase(produtos);
                    break;
                case 4:
                    adicionarQuantCase(produtos);
                    break;

                case 5:
                    visualizarEstoqueCase(produtos);
                    break;
                }
            } while(opEst != 6);

            break;
        case 3:
            do{
                bordaFunction();

                *FIM_DE_LINHA  = 24;
                menuCaixa(opCaixa);
                opCaixa = arrow(opCaixa,*INICIO_DE_LINHA,*FIM_DE_LINHA);
                *FIM_DE_LINHA = 25;

                switch(opCaixa){
                case 1:
                    passarProdutoCase(produtos, dados);
                    break;
                case 2:
                    exibeFluxoDeCaixaCase();
                    break;
                }
            } while(opCaixa != 3);
            break;
        }
    } while(opMain != 4);

    return 0;
}






#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>
#include <windows.h>
#include "libMain.h"
#include "libArquivos.h"
#include "libJSON.h"
#include "libTXT.h"
#include "Cliente.h"
#include "libCaixa.h"
#include "libCases.h"


using namespace std;


int main()
{
    setlocale(LC_ALL, "");
    int opMain, opEst, opCad, opCaixa, pos, quant;
    char opcao;
    char continuar;
    bool checkQuant;

    struct estoque produtos;
    struct notaFiscal dados;

    do{
        menuPrincipal(opMain);

        switch(opMain){
        case 1:
            do{
                menuCadastro(opCad);
                switch(opCad){
                case 1:
                    cin.ignore(); // Ignorar o caractere de quebra de linha deixado pelo cin anterior
                    cadastrarCliente();
                    break;
                case 2:
                    visualizarClientes();
                    break;
                case 3:
                    excluirClientePorNome();
                    break;
                case 0:
                    saindo();
                    break;
                default:
                    cout << "Opcao invalida!" << endl;
                }
            } while(opCad);
            break;
        case 2:
            do{
                menuEstoque(opEst);

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
                case 0:
                    saindo();
                    break;
                default:
                    cout << "Opção inválida. Tente novamente!" << endl;
                }
            } while(opEst);

            break;
        case 3:
            do{
                menuCaixa(opCaixa);

                switch(opCaixa){
                case 1:
                    passarProdutoCase(produtos, dados);
                    break;
                case 2:
                    exibeFluxoDeCaixaCase();
                    break;
                case 0:
                    saindo();
                    break;
                }
            } while(opCaixa);
            break;
        case 0:
            saindo();
            break;
        default:
            cout << "Opção inválida!" << endl;
        }
    } while(opMain);


    return 0;
}







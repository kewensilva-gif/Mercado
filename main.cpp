#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>
#include "libMain.h"
#include "libArquivos.h"
#include "libJSON.h"
#include "libTXT.h"


using namespace std;


int main()
{
    setlocale(LC_ALL, "Portuguese");
    int op, pos, quant;
    char opcao;
    char continuar;

    struct estoque produtos;

    do{
        menu(op);

        switch(op){

        case 1:
            system("cls");
            produtos.id = 0;

            cout << "Essa fun��o ir� sobrescrever tudo que h� no arquivo.\nDeseja continuar? <s - n> ";
            cin >> continuar;
            if(continuar == 's' || continuar == 'S'){
                pegaDados(produtos);
                json::criarLista(produtos);
                txt::criarLista(produtos);

                cout << "Deseja continuar? <s - n> ";
                cin >> opcao;
                if(opcao == 's' || opcao == 'S'){
                    system("cls");
                    do{
                        pegaDados(produtos);
                        produtos.id = converteId();
                        json::inserirProduto(produtos);
                        txt::inserirProduto(produtos);
                        cout << "Deseja continuar? <s - n> ";
                        cin >> opcao;
                    } while(opcao != 'n' && opcao != 'N');
                }
            }

            break;

        case 2:
            system("cls");
            do{
                pegaDados(produtos);
                produtos.id = converteId();
                json::inserirProduto(produtos);
                txt::inserirProduto(produtos);
                cout << "Deseja continuar? <s - n> ";
                cin >> opcao;
            } while(opcao != 'n' && opcao != 'N');

            break;

        case 3:
            system("cls");
            cout << "Digite o id do produto: ";
            cin >> pos;
            json::removerProduto(pos);
            txt::removerProduto(pos);
            break;

        case 4:
            system("cls");
            cout << "Digite o id do produto: ";
            cin >> pos;
            cout << "Digite a quantidade a ser inserida: ";
            cin >> quant;
            json::modificaQuantidade(pos, quant);
            txt::modificaQuantidade(pos, quant);
            break;
        case 5:
            system("cls");
            break;
        case 0:
            cout << "saindo..." << endl;
            break;
        default:
            cout << "Op��o inv�lida. Tente novamente!" << endl;
        }
    } while(op);

    return 0;
}







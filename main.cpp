#include <iostream>
#include "biblioteca.h"
#include "arquivoLib.h"
#include <fstream>
#include <string.h>
#include <locale>


using namespace std;


int main()
{
    setlocale(LC_ALL, "Portuguese");
    int op, pos, quant, id;
    float valor;
    string nome, marca;
    char opcao;
    char continuar;

    do{
        menu(op);

        switch(op){

        case 1:
            system("cls");
            id = 0;

            cout << "Essa função irá sobrescrever tudo que há no arquivo.\nDeseja continuar? <s - n> ";
            cin >> continuar;
            if(continuar == 's' || continuar == 'S'){
                pegaDados(nome, quant, marca, valor);
                criarListaJson(nome, quant, marca, valor, id);
                criarListaTxt(nome, quant, marca, valor, id);

                cout << "Deseja continuar? <s - n> ";
                cin >> opcao;
                if(opcao == 's' || opcao == 'S'){
                    system("cls");
                    do{
                        pegaDados(nome, quant, marca, valor);
                        id = converteId();
                        inserirProdutoJson(nome, quant, marca, valor, id);
                        inserirProdutoTxt(nome, quant, marca, valor, id);
                        cout << "Deseja continuar? <s - n> ";
                        cin >> opcao;
                    } while(opcao != 'n' && opcao != 'N');
                }
            }

            break;

        case 2:
            system("cls");
            do{
                pegaDados(nome, quant, marca, valor);
                id = converteId();
                inserirProdutoJson(nome, quant, marca, valor, id);
                inserirProdutoTxt(nome, quant, marca, valor, id);
                cout << "Deseja continuar? <s - n> ";
                cin >> opcao;
            } while(opcao != 'n' && opcao != 'N');

            break;

        case 3:
            system("cls");
            cout << "Digite o id do produto: ";
            cin >> pos;
            removerProdutoJson(pos);
            removerProdutoTxt(pos);
            break;

        case 4:
            system("cls");
            cout << "Digite o id do produto: ";
            cin >> pos;

            break;
        case 5:
            system("cls");
            break;
        case 0:
            cout << "saindo..." << endl;
            break;
        default:
            cout << "Opção inválida. Tente novamente!" << endl;
        }
    } while(op);

    return 0;
}







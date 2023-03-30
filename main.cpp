#include <iostream>
#include "biblioteca.h"
#include "arquivoLib.h"
#include <fstream>;
#include <string.h>
#include <locale>
using namespace std;


int main()
{
    setlocale(LC_ALL, "Portuguese");
    int op, pos, quant, id;
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
                pegaDados(nome, quant, marca);
                criarListaJson(nome, quant, marca, id);
                criarListaTxt(nome, quant, marca, id);

                cout << "Digite S para continuar ou N para sair: ";
                cin >> opcao;
                if(opcao == 's' || opcao == 'S'){
                    do{
                        pegaDados(nome, quant, marca);
                        id = pegaId();
                        inserirProdutoJson(nome, quant, marca, id);
                        inserirProdutoTxt(nome, quant, marca, id);
                        cout << "Digite S para continuar ou N para sair: ";
                        cin >> opcao;
                    } while(opcao != 'n' && opcao != 'N');
                } else {

                }
            }
            //insereProduto();
            //cadastrarProduto(produtos, posicao);
            break;

        case 2:
            system("cls");
            do{
                pegaDados(nome, quant, marca);
                id = pegaId();
                inserirProdutoJson(nome, quant, marca, id);
                inserirProdutoTxt(nome, quant, marca, id);
                cout << "Digite S para continuar ou N para sair: ";
                cin >> opcao;
            } while(opcao != 'n' && opcao != 'N');

            //lerProduto();
            //listarProdutos(produtos, posicao);
            break;

        case 3:
            system("cls");
            //cout << "Digite o id do produto: ";
            //cin >> pos;
            removerProdutoJson(pegaId());

            break;

        case 4:
            system("cls");
            cout << "Digite o id do produto: ";
            cin >> pos;

            break;
        case 5:
            system("cls");
            produtoJson();
            break;
        }
    } while(op);

    return 0;
}







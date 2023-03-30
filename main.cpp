#include <iostream>
#include "biblioteca.h"
#include <fstream>;
#include <string.h>
#include <locale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int op, posicao = 0, pos, quant;
    string nome, marca;


    do{
        menu(op);

        switch(op){

        case 1:
            system("cls");
            //insereProduto();
            criarListaJson(nome, quant, marca);\
            //cadastrarProduto(produtos, posicao);
            break;

        case 2:
            system("cls");

            inserirNovoProduto(nome, quant, marca, pegaId());

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







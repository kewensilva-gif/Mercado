#include <iostream>
#include "biblioteca.h"
#include <fstream>;
using namespace std;

void insereProduto(){
    char nome[30];
    int quant;
    char marca[30];
    int id;
    char opcao;

    ofstream produtos;
    produtos.open("produtos.txt", ios::app);

     do{
        cout << "Digite o nome do produto: ";
        cin >> nome;
        cout << "Digite a quantidade: ";
        cin >> quant;
        cout << "Digite a marca: ";
        cin >> marca;
        cout << "Digite o id: ";
        cin >> id;

        produtos << "**Produto**" << endl;
        produtos << "Nome: " << nome << endl;
        produtos << "Quantidade: " << quant << endl;
        produtos << "Marca: " << marca << endl;
        produtos << "id: " << id << endl;

        cout << "Digite S para continuar ou N para sair: ";
        cin >> opcao;
    } while(opcao != 'n' && opcao != 'N');

    produtos.close();
}

void lerProduto(){
    fstream produtos;
    string arquivo;
    string linha;
    produtos.open("produtos.txt", ios::in);

    if(produtos.is_open()){
        while(getline(produtos, linha)){
            if(linha == "id: 3"){
                continue;
            } else
                arquivo += (linha + "\n");
        }
        cout << arquivo << endl;
    } else {
        cout << "Não foi possivel abrir o arquivo" << endl;
    }

    produtos.close();

    produtos.open("produtos.txt", ios::out);

    produtos << arquivo;

    produtos.close();

}
int main()
{
    int op, posicao = 0, pos;

    struct estoque produtos[100];

    do{
        menu(op);

        switch(op){

        case 1:
            insereProduto();
            //cadastrarProduto(produtos, posicao);
            break;

        case 2:
            lerProduto();
            //listarProdutos(produtos, posicao);
            break;

        case 3:
            cout << "Digite o id do produto: ";
            cin >> pos;
            removerProduto(produtos, pos);
            break;

        case 4:
            cout << "Digite o id do produto: ";
            cin >> pos;
            adicionarQuant(produtos, pos);
            break;
        }
    } while(op);

    return 0;
}







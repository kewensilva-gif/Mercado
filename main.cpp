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



void produtoJson(){
    fstream produtos;
    string arquivo;
    string linha;
    produtos.open("produtos.json", ios::in);

    if(produtos.is_open()){
        while(getline(produtos, linha)){
            if(linha == "\t]"){
                continue;
            } else
                arquivo += (linha + "\n");
        }
    cout << arquivo << endl;
    } else {
        cout << "Não foi possivel abrir o arquivo" << endl;
    }

    produtos.close();

    produtos.open("produtos.json", ios::out);

    produtos << arquivo;

    produtos.close();

}

void criarListaJson(){
    char nome[30];
    int quant;
    char marca[30];
    int id;
    int sair;

    fstream produtos;
    produtos.open("produtos.json", ios::app);
    produtos << "{\n\t\"produtos\": [ " << endl;
     do{
        cout << "Digite o nome do produto: ";
        cin >> nome;
        cout << "Digite a quantidade: ";
        cin >> quant;
        cout << "Digite a marca: ";
        cin >> marca;
        cout << "Digite o id: ";
        cin >> id;

        produtos << "\t\t{" << endl;
        produtos << "\t\t\t\"Nome\": \"" << nome << "\","<< endl;
        produtos << "\t\t\t\"Quantidade\": " << quant << ","<< endl;
        produtos << "\t\t\t\"Marca\": \"" << marca << "\","<< endl;
        produtos << "\t\t\t\"id\": " << id << endl;
        produtos << "\t\t}\t" << endl;

        cout << "Digite 0 para sair: ";
        cin >> sair;
    } while(sair);

    produtos << "\t]\n}" << endl;
    produtos.close();
}

insereNovoProduto(){
    char nome[30];
    int quant;
    char marca[30];
    int id;
    fstream produtos;
    string arquivo;
    string linha;
    produtos.open("produtos.json", ios::in);

    if(produtos.is_open()){
        while(getline(produtos, linha)){
            if(linha == "\t\t}\t"){
                break;
            } else
                arquivo += (linha + "\n");
        }
    cout << arquivo << endl;
    } else {
        cout << "Não foi possivel abrir o arquivo" << endl;
    }

    produtos.close();

    produtos.open("produtos.json", ios::out);

    produtos << arquivo;
    produtos << "\t\t},\t" << endl;
    produtos << "\t\t{" << endl;
    cout << "Digite o nome do produto: ";
    cin >> nome;
    cout << "Digite a quantidade: ";
    cin >> quant;
    cout << "Digite a marca: ";
    cin >> marca;
    cout << "Digite o id: ";
    cin >> id;
    produtos << "\t\t\t\"Nome\": \"" << nome << "\","<< endl;
    produtos << "\t\t\t\"Quantidade\": " << quant << ","<< endl;
    produtos << "\t\t\t\"Marca\": \"" << marca << "\","<< endl;
    produtos << "\t\t\t\"id\": " << id << endl;
    produtos << "\t\t}\t" << endl;
    produtos << "\t]\n}" << endl;

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
            //insereProduto();
            criarListaJson();
            //cadastrarProduto(produtos, posicao);
            break;

        case 2:
            produtoJson();
            //lerProduto();
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
        case 5:
            insereNovoProduto();
            break;
        }
    } while(op);

    return 0;
}







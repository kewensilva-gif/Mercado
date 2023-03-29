#include <iostream>
#include "biblioteca.h"
#include <fstream>;
using namespace std;

void pegaDados(string& nome, int& quant, string& marca, int& id){
    cout << "Digite o nome do produto: ";
    cin >> nome;
    cout << "Digite a quantidade: ";
    cin >> quant;
    cout << "Digite a marca: ";
    cin >> marca;
    cout << "Digite o id: ";
    cin >> id;
}

void insereProduto(string& nome, int& quant, string& marca, int& id){
    char opcao;
    ofstream produtos;
    produtos.open("produtos.txt", ios::app);

     do{
        pegaDados(nome, quant, marca, id);

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
        cout << "N�o foi possivel abrir o arquivo" << endl;
    }

    produtos.close();

    produtos.open("produtos.json", ios::out);

    produtos << arquivo;

    produtos.close();

}

void criarListaJson(string nome, int quant, string marca, int id){
    int sair;
    char continuar;

    cout << "Essa fun��o ir� sobrescrever tudo que h� no arquivo.\nDeseja continuar? <s - n> ";
    cin >> continuar;

    if(continuar == 's' || continuar == 'S'){
        fstream produtos;
        produtos.open("produtos.json", ios::out);
        produtos << "{\n\t\"produtos\": [ " << endl;
         do{
            pegaDados(nome, quant, marca, id);

            produtos << "\t\t{" << endl;
            produtos << "\t\t\t\"Nome\": \"" << nome << "\","<< endl;
            produtos << "\t\t\t\"Quantidade\": " << quant << ","<< endl;
            produtos << "\t\t\t\"Marca\": \"" << marca << "\","<< endl;
            produtos << "\t\t\t\"id\": " << id << endl;


            cout << "Digite 0 para sair: ";
            cin >> sair;


            if(!sair){
                produtos << "\t\t}\t" << endl;
            } else {
                produtos << "\t\t}," << endl;
            }
        } while(sair);

        produtos << "\t]\n}" << endl;
        produtos.close();
    }
}

inserirNovoProduto(string nome, int quant, string marca, int id){

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
    } else {
        cout << "N�o foi possivel abrir o arquivo" << endl;
    }

    produtos.close();

    produtos.open("produtos.json", ios::out);

    produtos << arquivo;
    produtos << "\t\t},\t" << endl;
    produtos << "\t\t{" << endl;
    pegaDados(nome, quant, marca, id);
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
    int op, posicao = 0, pos, quant, id;
    string nome, marca;

    struct estoque produtos[100];

    do{
        menu(op);

        switch(op){

        case 1:
            //insereProduto();
            criarListaJson(nome, quant, marca, id);
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
            inserirNovoProduto(nome, quant, marca, id);
            break;
        }
    } while(op);

    return 0;
}







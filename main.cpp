#include <iostream>
#include "biblioteca.h"
#include <fstream>;
#include <string.h>
#include <locale>
using namespace std;

void pegaDados(string& nome, int& quant, string& marca){
    cout << "Digite o nome do produto: ";
    cin >> nome;
    cout << "Digite a quantidade: ";
    cin >> quant;
    cout << "Digite a marca: ";
    cin >> marca;
}

void insereProduto(string& nome, int& quant, string& marca, int id){
    char opcao;
    ofstream produtos;
    produtos.open("produtos.txt", ios::app);

     do{
        pegaDados(nome, quant, marca);

        produtos << "**Produto**" << endl;
        produtos << "Nome: " << nome << endl;
        produtos << "Quantidade: " << quant << endl;
        produtos << "Marca: " << marca << endl;
        produtos << "id: " << ++id << endl;

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

void criarListaJson(string nome, int quant, string marca){
    int sair, id;
    char continuar;

    cout << "Essa função irá sobrescrever tudo que há no arquivo.\nDeseja continuar? <s - n> ";
    cin >> continuar;

    if(continuar == 's' || continuar == 'S'){
        fstream produtos;
        produtos.open("produtos.json", ios::out);
        produtos << "{\n\t\"produtos\": [ " << endl;
         do{
            pegaDados(nome, quant, marca);

            produtos << "\t\t{" << endl;
            produtos << "\t\t\t\"Nome\": \"" << nome << "\","<< endl;
            produtos << "\t\t\t\"Quantidade\": " << quant << ","<< endl;
            produtos << "\t\t\t\"Marca\": \"" << marca << "\","<< endl;
            produtos << "\t\t\t\"id\": " << id++ << endl;


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

void inserirNovoProduto(string nome, int quant, string marca, int id){

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
        cout << "Não foi possivel abrir o arquivo" << endl;
    }

    produtos.close();

    produtos.open("produtos.json", ios::out);

    produtos << arquivo;
    produtos << "\t\t},\t" << endl;
    produtos << "\t\t{" << endl;
    pegaDados(nome, quant, marca);
    produtos << "\t\t\t\"Nome\": \"" << nome << "\","<< endl;
    produtos << "\t\t\t\"Quantidade\": " << quant << ","<< endl;
    produtos << "\t\t\t\"Marca\": \"" << marca << "\","<< endl;
    produtos << "\t\t\t\"id\": " << ++id << endl;
    produtos << "\t\t}\t" << endl;
    produtos << "\t]\n}" << endl;

    produtos.close();

}

// Função que pega o id do objeto
int pegaId(){
    fstream produtos;

    string linha, aux, aux2;
    int cont = 0, cont2 = 0, len, id;

    produtos.open("produtos.json", ios::in);

    if(produtos.is_open()){
        while(getline(produtos, linha)){
            cont++;
        }
    } else {
        cout << "Não foi possível abri o arquivo" << endl;
    }

    produtos.close();

    produtos.open("produtos.json", ios::in);

    if(produtos.is_open()){
        while(getline(produtos, linha)){
            cont2++;
            if(cont-3 == cont2){
                aux = linha;
                len = strlen(linha.c_str());
            }
        }

    } else {
        cout << "Não foi possível abri o arquivo" << endl;
    }

    for(int i = 0; i < len; i++){
        if(i == len-2 || i == len-1){
            aux2 += aux[i];
        }
    }

    id = stoi(aux2);
    return id;
}

void removerProdutoJson(int id){
    cout << "Id: " << id << endl;
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int op, posicao = 0, pos, quant;
    string nome, marca;

    struct estoque produtos[100];

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
            pos = pegaId();
            inserirNovoProduto(nome, quant, marca, pos);

            //lerProduto();
            //listarProdutos(produtos, posicao);
            break;

        case 3:
            system("cls");
            //cout << "Digite o id do produto: ";
            //cin >> pos;
            removerProdutoJson(pegaId());
            //removerProduto(produtos, pos);
            break;

        case 4:
            system("cls");
            cout << "Digite o id do produto: ";
            cin >> pos;
            adicionarQuant(produtos, pos);
            break;
        case 5:
            system("cls");
            produtoJson();
            break;
        }
    } while(op);

    return 0;
}







#include <iostream>

using namespace std;

struct estoque{
    char nome[30];
    int quant;
    char marca[30];
    int id;
};

void menu(int& op){
    cout << "1 - Cadastrar produto" << endl;
    cout << "2 - Listar produtos" << endl;
    cout << "3 - Remover produto" << endl;
    cout << "4 - Adicionar quantidade ao estoque" << endl;
    cout << "0 - Sair" << endl;
    cout << "Digite a opção desejada: ";

    cin >> op;
}

void cadastrarProduto(struct estoque produtos[], int& posicao){
    char opcao;

    do{
        cout << "Digite o nome do produto: ";
        cin >> produtos[posicao].nome;
        cout << "Digite a quantidade: ";
        cin >> produtos[posicao].quant;
        cout << "Digite a marca: ";
        cin >> produtos[posicao].marca;
        produtos[posicao].id;
        posicao++;

        cout << "Digite S para continuar ou N para sair: ";
        cin >> opcao;
    } while(opcao != 'n' && opcao != 'N');

}

void removerProduto(struct estoque produtos[], int posicao){
    produtos[posicao].id = 2000;
}

void listarProdutos(struct estoque produtos[], int posicao){
    cout << "***Lista de Produtos***" << endl;
    for(int i = 0; i < posicao; i++){
        if(produtos[i].id == 2000){
            continue;
        } else {
            cout << "Nome: " << produtos[i].nome << endl;
            cout << "Quantidade em estoque: " << produtos[i].quant << endl;
            cout << "Marca: " << produtos[i].marca << endl;
            cout << "id: " << produtos[i].id << endl;
        }
    }
}







void adicionarQuant(struct estoque produtos[], int posicao){
    int quantidade;
    cout << "Digite a quantidade inserida no estoque: ";
    cin >> quantidade;
    produtos[posicao].quant += quantidade;
}


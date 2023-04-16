#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

struct estoque {
    string nome;
    int quant;
    string marca;
    float custo;
    float valor;
    int id;
};

void menuPrincipal(int& op){
    system("cls");
    cout << "MENU" << endl;
    cout << "1 - Cadastrar cliente / Visualizar clientes" << endl;
    cout << "2 - Cadastrar produtos / Visualizar produto" << endl;
    cout << "3 - Caixa" << endl;
    cout << "0 - Sair" << endl;
    cout << "Digite a opção desejada: ";

    cin >> op;
}


void menuEstoque(int& op){
    system("cls");
    cout << "1 - Criar lista" << endl;
    cout << "2 - Inserir novo produto" << endl;
    cout << "3 - Remover produto" << endl;
    cout << "4 - Adicionar quantidade ao estoque" << endl;
    cout << "5 - Editar item" << endl;
    cout << "0 - Voltar ao menu inicial" << endl;
    cout << "Digite a opção desejada: ";

    cin >> op;
}

void menuCadastro(int& op){
    system("cls");
    cout << "1 - Cadastrar novo cliente" << endl;
    cout << "2 - Visualizar clientes cadastrados" << endl;
    cout << "3 - Remove clientes cadastrados" << endl;
    cout << "0 - Voltar ao menu inicial" << endl;
    cout << "Digite uma opcao: ";

    cin >> op;
}

void menuCaixa(int& op){
    system("cls");
    cout << "1 - Passar compra" << endl;
    cout << "2 - Verificar entradas e saídas" << endl;
    cout << "0 - Voltar ao menu inicial" << endl;
    cout << "Digite uma opcao: ";

    cin >> op;
}






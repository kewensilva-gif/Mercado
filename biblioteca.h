#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

struct estoque {
    string nome;
    int quant;
    string marca;
    float valor;
    int id;
};

void menu(int& op){
    system("cls");
    cout << "1 - Criar lista" << endl;
    cout << "2 - Inserir novo produto" << endl;
    cout << "3 - Remover produto" << endl;
    cout << "4 - Adicionar quantidade ao estoque" << endl;
    cout << "0 - Sair" << endl;
    cout << "Digite a opção desejada: ";

    cin >> op;
}









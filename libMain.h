
//#include "libArquivos.h"
using namespace std;

//Assinaturas
void bordaFunction();
void menuPrincipal(int& op);
void menuEstoque(int& op);
void menuCadastro(int& op);
void menuCaixa(int& op);

void bordaFunction(){
    textbackground(DARKGRAY);
    system("cls");
    textcolor(WHITE);
    borda1(59,16,51,15,15);
}

struct estoque {
    string nome;
    int quant;
    string marca;
    float custo;
    float venda;
    int id;
};

void menuPrincipal(int& op){
    system("CLS");
    borda1(59,16,51,15,15);
    gotoxy(63,18);cout << "MENU PRINCIPAL" << endl;
    gotoxy(63,22);cout << "<1> - Menu de cadastros" << endl;
    gotoxy(63,23);cout << "<2> - Menu de estoque" << endl;
    gotoxy(63,24);cout << "<3> - Menu de caixa" << endl;
    gotoxy(63,25);cout << "<4> - Sair" << endl;
}


void menuEstoque(int& op){
    bordaFunction();

    gotoxy(63,18);
    cout << "MENU DE ESTOQUE" << endl;
    gotoxy(63,21);
    cout << "<1> - Criar lista" << endl;
    gotoxy(63,22);
    cout << "<2> - Inserir novo produto" << endl;
    gotoxy(63,23);
    cout << "<3> - Remover produto" << endl;
    gotoxy(63,24);
    cout << "<4> - Adicionar quantidade ao estoque" << endl;
    gotoxy(63,25);
    cout << "<5> - Visualizar estoque" << endl;
    gotoxy(63,26);
    cout << "<6> - Voltar ao menu inicial" << endl;
}

void menuCadastro(int& op){
    bordaFunction();

    gotoxy(63,18); cout << "MENU DE CADASTRO" << endl;
    gotoxy(63,22); cout << "<1> - Cadastrar novo cliente" << endl;
    gotoxy(63,23); cout << "<2> - Visualizar clientes cadastrados" << endl;
    gotoxy(63,24); cout << "<3> - Remover clientes cadastrados" << endl;
    gotoxy(63,25); cout << "<4> - Atualizar debito" << endl;
    gotoxy(63,26); cout << "<5> - Voltar ao menu inicial" << endl;
}

void menuCaixa(int& op){
    bordaFunction();

    gotoxy(63,18); cout << "MENU DE CAIXA" << endl;
    gotoxy(63,22); cout << "<1> - Cadastrar compra" << endl;
    gotoxy(63,23); cout << "<2> - Verificar entradas e saidas" << endl;
    gotoxy(63,24); cout << "<3> - Voltar ao menu inicial" << endl;
}

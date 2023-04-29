#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // Para usar setw() e left()
#include <limits> // Para usar numeric_limits
#include "gconio.h"

using namespace std;

// Definição da classe Cliente
class Cliente
{
public:
    string nome;
    int id;
    float debito;
};

//Assinaturas
void cadastrarCliente();
void visualizarClientes();
void excluir();
void excluir(float* debito);


void cadastrarCliente()
{
    // Declaração e inicialização do objeto Cliente

    Cliente novoCliente;
    // Solicitar nome do novo cliente

    //gotoxy(63,24);cin.ignore();
    gotoxy(63,22);cout << "Digite o nome do novo cliente: ";
    gotoxy(63,24);getline(cin, novoCliente.nome);

    // Solicitar ID do novo cliente
    bordaFunction();
    gotoxy(63,22);cout << "Digite o ID do novo cliente: ";
    gotoxy(63,24);cin >> novoCliente.id;

      // Solicitar ID do novo cliente
    bordaFunction();
    gotoxy(63,22);cout << "Digite o debito do novo cliente: ";
    gotoxy(63,24);cin >> novoCliente.debito;

    // Ignorar o caractere de nova linha (\n) deixado no buffer após a leitura do ID
    //cin.ignore();

    // Abrir arquivo de clientes em modo de escrita
    ofstream arquivoClientes("clientes.txt", ios::app);

    // Salvar informações do cliente no arquivo em formato TXT com formatação

    arquivoClientes << "Nome do Cliente: " << setw(30) << left << novoCliente.nome << "ID: " << novoCliente.id << " Debito: R$ " << novoCliente.debito << endl;

    // Fechar arquivo de clientes
    arquivoClientes.close();

    // Exibir mensagem de sucesso
    bordaFunction();
    gotoxy(63,22);cout << "Cliente cadastrado com sucesso!" << endl;
    Sleep(2000);
}


void visualizarClientes()
{
    system("cls");
    textbackground(DARKGRAY);
    system("cls");
    textcolor(WHITE);

    // Abrir arquivo de clientes em modo de leitura
    ifstream arquivoClientes("clientes.txt");

    // Variáveis para armazenar informações do cliente
    string linha;
    gotoxy(72,0);
    cout << "Lista de clientes:" << endl;

   int num = 3;
    // Ler informações de cada cliente no arquivo e imprimir na tela
    while (getline(arquivoClientes, linha))
    {
        // Exibir informações com formatação na tela
        gotoxy(47,num);num ++;
        cout << linha << endl;
    }

    //gotoxy(72,num + 50);
    cout<<"\n";
    gotoxy(47,num+5);system("Pause");
    // Fechar arquivo de clientes
    arquivoClientes.close();

}

void excluir()
{
    string nomeClienteExcluir;

    bordaFunction();
    gotoxy(63,22);
    cout << "Digite o nome do cliente a ser excluido: ";
    gotoxy(63,24);
    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar o buffer do teclado

    getline(cin, nomeClienteExcluir); // Ler o nome do cliente

    // Abrir arquivo de clientes em modo de leitura
    ifstream arquivoClientes("clientes.txt");

    // Abrir arquivo temporário para escrita
    ofstream arquivoTemp("temp.txt");

    // Variáveis para armazenar informações do cliente
    string linha;

    bool clienteEncontrado = false;

    // Ler informações de cada cliente no arquivo
    while (getline(arquivoClientes, linha))
    {
        // Verificar se a linha contém o nome do cliente a ser excluído
        if (linha.find(nomeClienteExcluir) == string::npos)
        {
            // Se não contém o nome, escrever a linha no arquivo temporário
            arquivoTemp << linha << endl;
        }
        else
        {
            // Se contém o nome, marcar o cliente como encontrado
            clienteEncontrado = true;
        }
    }

    // Fechar arquivos
    arquivoClientes.close();
    arquivoTemp.close();

    // Remover arquivo original de clientes
    remove("clientes.txt");

    // Renomear arquivo temporário para o nome original de clientes
    rename("temp.txt", "clientes.txt");



    if (clienteEncontrado)
    {
        bordaFunction();
        gotoxy(63,22);cout << "Cliente excluido com sucesso!" << endl;
    }
    else
    {
        bordaFunction();
        gotoxy(63,22);cout << "Cliente nao encontrado." << endl;
    }
    Sleep(2000);
}


void excluir(float* debito)

{
    bordaFunction();
    string nomeClienteAtualizar;
    int idClienteAtualizar; // Adicionar variável para o ID do cliente
    gotoxy(63,22);cout << "Informe o ID do cliente a ser atualizado: "; // Solicitar também o ID do cliente
    gotoxy(63,23);cin >> idClienteAtualizar; // Ler o ID do cliente
    //cin.ignore(); // Limpar o buffer do teclado
    bordaFunction();
    gotoxy(63,22);cout << "Informe o nome do cliente para atualizar o débito: ";
    gotoxy(63,23);getline(cin, nomeClienteAtualizar);

    // Abrir arquivo de clientes em modo de leitura
    ifstream arquivoClientes("clientes.txt");

    // Abrir arquivo temporário para escrita
    ofstream arquivoTemp("temp.txt");

    // Variáveis para armazenar informações do cliente
    string linha;
    // Flag para encontrar o Cliente
    bool clienteEncontrado = false;

    // Ler informações de cada cliente no arquivo
    while (getline(arquivoClientes, linha))
    {
        // Verificar se a linha contém o nome do cliente a ser atualizado
        if (linha.find(nomeClienteAtualizar) == string::npos)
        {
            // Se não contém o nome, escrever a linha no arquivo temporário
            arquivoTemp << linha << endl;
        }
        else
        {
            // Se contém o nome, atualizar o débito
            clienteEncontrado = true;

            // Solicitar ao usuário a quantidade a ser atualizada
            float valorAtualizar;
            cout << "Informe a quantidade a ser atualizada para o cliente " << nomeClienteAtualizar << ": ";
            cin >> valorAtualizar;

            // Atualizar o débito
            *debito += valorAtualizar;
            // Formatação no arquivo txt e na tela to console
            std::ostringstream ss;
            ss << std::fixed << std::setprecision(2) << *debito;
            string linhaAtualizada = "Nome do Cliente: " + nomeClienteAtualizar + "       ID do Cliente: " + to_string(idClienteAtualizar) + "     Debito: R$ " + ss.str();

            // Escrever a linha atualizada no arquivo temporário
            arquivoTemp << linhaAtualizada << endl;
        }
    }

    // Fechar arquivos
    arquivoClientes.close();
    arquivoTemp.close();

    // Remover arquivo original de clientes
    remove("clientes.txt");

    // Renomear arquivo temporário para o nome original de clientes
    rename("temp.txt", "clientes.txt");

    if (clienteEncontrado)
    {
        bordaFunction();
        gotoxy(63,22);cout << "Débito do cliente atualizado com sucesso!" << endl;
        Sleep(1000);
    }
    else
    {
        bordaFunction();
        gotoxy(63,22);cout << "Cliente não encontrado." << endl;
        Sleep(1000);
    }
}


#endif // CLIENTE_H_INCLUDED

#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // Para usar setw() e left()
#include <limits> // Para usar numeric_limits

using namespace std;

// Definição da classe Cliente
class Cliente
{
public:
    string nome;
    int id;
    float debito;
};

void cadastrarCliente()
{
    // Declaração e inicialização do objeto Cliente
    Cliente novoCliente;

    // Solicitar nome do novo cliente
    cout << "Digite o nome do novo cliente: ";
    getline(cin, novoCliente.nome);

    // Solicitar ID do novo cliente
    cout << "Digite o ID do novo cliente: ";
    cin >> novoCliente.id;

      // Solicitar ID do novo cliente
    cout << "Digite o debito do novo cliente: ";
    cin >> novoCliente.debito;

    // Ignorar o caractere de nova linha (\n) deixado no buffer após a leitura do ID
    cin.ignore();

    // Abrir arquivo de clientes em modo de escrita
    ofstream arquivoClientes("clientes.txt", ios::app);

    // Salvar informações do cliente no arquivo em formato TXT com formatação
    arquivoClientes << "Nome do Cliente: " << setw(30) << left << novoCliente.nome << "ID: " << novoCliente.id << " Débito: R$ " << novoCliente.debito << endl;

    // Fechar arquivo de clientes
    arquivoClientes.close();

    // Exibir mensagem de sucesso
    cout << "Cliente cadastrado com sucesso!" << endl;
}


void visualizarClientes()
{
    // Abrir arquivo de clientes em modo de leitura
    ifstream arquivoClientes("clientes.txt");

    // Variáveis para armazenar informações do cliente
    string linha;

    cout << "Lista de clientes:" << endl;

    // Ler informações de cada cliente no arquivo e imprimir na tela
    while (getline(arquivoClientes, linha))
    {
        // Exibir informações com formatação na tela
        cout << linha << endl;
    }

    // Fechar arquivo de clientes
    arquivoClientes.close();
}

void excluirClientePorNome()
{
    string nomeClienteExcluir;
    cout << "Digite o nome do cliente a ser excluído: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignorar o buffer do teclado
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
        cout << "Cliente excluído com sucesso!" << endl;
    }
    else
    {
        cout << "Cliente não encontrado." << endl;
    }
}


#endif // CLIENTE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>
#include <windows.h>
#include "libMain.h"
#include "libArquivos.h"
#include "libJSON.h"
#include "libTXT.h"
#include "Cliente.h"
#include "libCaixa.h"
#include "libCases.h"


using namespace std;


int main()
{
    setlocale(LC_ALL, "");
    int opMain, opEst, opCad, opCaixa, pos, quant;
    char opcao;
    char continuar;
    bool checkQuant;

    struct estoque produtos;
    struct notaFiscal dados;

    do{
        menuPrincipal(opMain);

        switch(opMain){
        case 1:
            do{
                menuCadastro(opCad);
                switch(opCad){
                case 1:
                    cin.ignore(); // Ignorar o caractere de quebra de linha deixado pelo cin anterior
                    cadastrarCliente();
                    break;
                case 2:
                    visualizarClientes();
                    break;
                case 3:
                    excluirClientePorNome();
                    break;
                case 0:
                    cout << "Opção inválida!" << endl;
                    break;
                default:
                    cout << "Opcao invalida!" << endl;
                }
            } while(opCad);
            break;
        case 2:
            do{
                menuEstoque(opEst);

                switch(opEst){

                case 1:
                    /*system("cls");
                    cout << "CRIAR LISTA" << endl;
                    produtos.id = 0;

                    cout << "Essa função irá sobrescrever tudo que há no arquivo.\nDeseja continuar? <s - n> ";
                    cin >> continuar;
                    if(continuar == 's' || continuar == 'S'){
                        pegaDados(produtos);
                        json::criarLista(produtos);
                        txt::criarLista(produtos);

                        cout << "Deseja continuar? <s - n> ";
                        cin >> opcao;
                        if(opcao == 's' || opcao == 'S'){
                            system("cls");
                            do{
                                pegaDados(produtos);
                                produtos.id = converteId();
                                json::inserirProduto(produtos);
                                txt::inserirProduto(produtos);

                                cout << "Deseja continuar? <s - n> ";
                                cin >> opcao;
                            } while(opcao != 'n' && opcao != 'N');
                        }
                    }
                    fluxoDeCaixa();*/
                    criarListaCase(produtos);
                    break;

                case 2:
                    system("cls");
                    cout << "INSERIR NOVO PRODUTO" << endl;
                    do{
                        pegaDados(produtos);
                        produtos.id = converteId();
                        json::inserirProduto(produtos);
                        txt::inserirProduto(produtos);
                        cout << "Deseja continuar? <s - n> ";
                        cin >> opcao;
                    } while(opcao != 'n' && opcao != 'N');

                    break;

                case 3:
                    system("cls");
                    cout << "REMOVER PRODUTO" << endl;
                    cout << "Digite o ID do produto: ";
                    cin >> pos;
                    json::removerProduto(pos);
                    txt::removerProduto(pos);
                    break;

                case 4:
                    system("cls");
                    cout << "ADICIONAR QUANTIDADE AO ESTOQUE" << endl;
                    cout << "Digite o ID do produto: ";
                    cin >> pos;

                    while(true){
                        cout << "Digite a quantidade a ser inserida: ";
                        cin >> quant;
                        if(quant <= 0){
                            cout << "Quantidade inválida!\nInsira uma quantidade superior a zero." << endl;
                        } else {
                            break;
                        }
                    }
                    json::modificaQuantidade(pos, quant);
                    txt::modificaQuantidade(pos, quant, checkQuant);
                    if(checkQuant){
                        cout << "Quantidade alterada com sucesso!" << endl;
                        Sleep(1000);
                    }
                    break;

                case 5:
                    system("cls");
                    cout << "VISUALIZAR ESTOQUE" << endl;
                    visualizarEstoque();

                    cout << "Voltar ao menu? <s>";
                    cin >> opcao;
                    break;
                case 0:
                    system("cls");
                    cout << "saindo..." << endl;
                    Sleep(2000);
                    break;
                default:
                    cout << "Opção inválida. Tente novamente!" << endl;
                }
            } while(opEst);

            break;
        case 3:
            do{

                menuCaixa(opCaixa);
                switch(opCaixa){
                case 1:
                iniciaArquivo();
                    float total, pagamento, totalProduto;
                    int quantidadeItens;
                    quantidadeItens = 0;
                    do{
                        system("cls");
                        cout << "Digite o id do produto: ";
                        cin >> produtos.id;
                        while(true){
                            cout << "Digite a quantidade: ";
                            cin >> produtos.quant;
                            if(produtos.quant <= 0){
                                cout << "Quantidade inválida!\nInsira uma quantidade superior a zero." << endl;
                            } else {
                                break;
                            }
                        }
                        quantidadeItens += produtos.quant;

                        pegaDadosProduto(produtos.id, dados);

                        quant = -produtos.quant;

                        txt::modificaQuantidade(produtos.id, quant, checkQuant);
                        json::modificaQuantidade(produtos.id, quant);
                        cout << "Deseja continuar? <s - n> ";
                        cin >> opcao;
                        totalProduto = pegaValor(produtos.id);
                        total += (produtos.quant * totalProduto);

                        dadosCaixaProdutos(dados, produtos, opcao, total);


                    } while(opcao != 'n' && opcao != 'N');

                    cout << "R$" << total << endl;
                    cout << "Insira o valor pago: ";
                    cin >> pagamento;
                    cout << "Troco: R$" << pagamento - total << endl;
                    insereContaNaNota(total, pagamento, quantidadeItens);
                    cout << "Voltar ao menu de caixa? <s> ";
                    cin >> opcao;
                    break;
                case 2:
                system("cls");
                exibeFluxoDeCaixa();
                cout << "Voltar ao menu? <s>";
                cin >> opcao;
                    break;
                case 0:
                    cout << "saindo..." << endl;
                    break;
                }
            } while(opCaixa);
            break;
        case 0:
            cout << "saindo..." << endl;
            break;
        default:
            cout << "Opção inválida!" << endl;
        }
    } while(opMain);


    return 0;
}







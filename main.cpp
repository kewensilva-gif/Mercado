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


using namespace std;


int main()
{
    setlocale(LC_ALL, "");
    int opMain, opEst, opCad, opCaixa, pos, quant;
    char opcao;
    char continuar;

    struct estoque produtos;

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
                    cout << "Op��o inv�lida!" << endl;
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
                    system("cls");
                    produtos.id = 0;

                    cout << "Essa fun��o ir� sobrescrever tudo que h� no arquivo.\nDeseja continuar? <s - n> ";
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
                    fluxoDeCaixa();
                    break;

                case 2:
                    system("cls");
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
                    cout << "Digite o id do produto: ";
                    cin >> pos;
                    json::removerProduto(pos);
                    txt::removerProduto(pos);
                    break;

                case 4:
                    system("cls");
                    cout << "Digite o id do produto: ";
                    cin >> pos;
                    cout << "Digite a quantidade a ser inserida: ";
                    cin >> quant;
                    json::modificaQuantidade(pos, quant);
                    txt::modificaQuantidade(pos, quant);
                    break;
                case 5:
                    system("cls");
                    break;
                case 0:
                    cout << "saindo..." << endl;
                    break;
                default:
                    cout << "Op��o inv�lida. Tente novamente!" << endl;
                }
            } while(opEst);

            break;
        case 3:
            do{
                menuCaixa(opCaixa);
                switch(opCaixa){
                case 1:
                    float total, pagamento;

                    do{
                        system("cls");
                        cout << "Digite o id do produto: ";
                        cin >> produtos.id;
                        cout << "Digite a quantidade: ";
                        cin >> produtos.quant;
                        quant = -produtos.quant;
                        txt::modificaQuantidade(produtos.id, quant);
                        json::modificaQuantidade(produtos.id, quant);
                        cout << "Deseja continuar? <s - n> ";
                        cin >> opcao;

                        total += (produtos.quant * pegaValor(produtos.id));

                    } while(opcao != 'n' && opcao != 'N');

                    cout << "R$" << total << endl;
                    cout << "Insira o valor pago: ";
                    cin >> pagamento;
                    cout << "Troco: R$" << pagamento - total << endl;
                    Sleep(3000);
                    break;
                case 2:
                fluxoDeCaixa();
                Sleep(3000);
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
            cout << "Op��o inv�lida!" << endl;
        }
    } while(opMain);


    return 0;
}







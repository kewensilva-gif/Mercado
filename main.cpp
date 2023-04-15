#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>
#include "libMain.h"
#include "libArquivos.h"
#include "libJSON.h"
#include "libTXT.h"
#include "Cliente.h"


using namespace std;


int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opMain, opEst, opCad, pos, quant;
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
                    system("cls");
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
                    cout << "Opção inválida. Tente novamente!" << endl;
                }
            } while(opEst);

            break;
        case 3:
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







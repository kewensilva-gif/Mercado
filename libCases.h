//Assinaturas
void criarListaCase(struct estoque produtos);
void inserirProdutoCase(struct estoque produtos);
void removerItemCase(struct estoque produtos);
void adicionarQuantCase(struct estoque produtos);
void visualizarEstoqueCase(struct estoque produtos);
void passarProdutoCase(struct estoque produtos, struct notaFiscal dados);
void exibeFluxoDeCaixaCase();



void criarListaCase(struct estoque produtos){
    char opcao, continuar;

    bordaFunction();

    gotoxy(63,18);cout << "CRIAR LISTA" << endl;
    gotoxy(63,22);cout << "Essa funcao sobrescrevera todo arquivo";
    gotoxy(63,23);cout <<"Deseja continuar? <s - n> ";
    gotoxy(63,25);cin >> continuar;

    produtos.id = 0;

    if(continuar == 's' || continuar == 'S'){
        pegaDados(produtos);
        json::criarLista(produtos);
        txt::criarLista(produtos);
        bordaFunction();
        gotoxy(63,22);cout << "Deseja continuar? <s - n> ";
        gotoxy(63,24);cin >> opcao;
        if(opcao == 's' || opcao == 'S'){
            system("cls");
            do{
                pegaDados(produtos);
                produtos.id = converteId();
                json::inserirProduto(produtos);
                txt::inserirProduto(produtos);

                bordaFunction();
                gotoxy(63,22);cout << "Deseja continuar? <s - n> ";
                gotoxy(63,24);cin >> opcao;
            } while(opcao != 'n' && opcao != 'N');
        }
    }
    fluxoDeCaixa();
}

void inserirProdutoCase(struct estoque produtos){
    char opcao;

    gotoxy(63,18);
    cout << "INSERIR NOVO PRODUTO" << endl;
    do{
        pegaDados(produtos);
        produtos.id = converteId();
        json::inserirProduto(produtos);
        txt::inserirProduto(produtos);

        bordaFunction();

        gotoxy(63,22);
        cout << "Deseja continuar? <s - n> ";
        gotoxy(63,24);
        cin >> opcao;
    } while(opcao != 'n' && opcao != 'N');
}

void removerItemCase(struct estoque produtos){
    int pos;
    bordaFunction();
    gotoxy(63,18);cout << "REMOVER PRODUTO" << endl;
    gotoxy(63,22);cout << "Digite o ID do produto: ";
    gotoxy(63,24);cin >> pos;
    json::removerProduto(pos);
    txt::removerProduto(pos);
}

void adicionarQuantCase(struct estoque produtos){
    int pos, quant;
    bool checkQuant, check;

    bordaFunction();
    gotoxy(63,18);cout << "ADICIONAR QUANTIDADE AO ESTOQUE" << endl;
    gotoxy(63,22);cout << "Digite o ID do produto: ";
    gotoxy(63,24);cin >> pos;

    while(true){
        bordaFunction();
        gotoxy(63,18);cout << "ADICIONAR QUANTIDADE AO ESTOQUE" << endl;
        gotoxy(63,22);cout << "Digite a quantidade a ser inserida: ";
        gotoxy(63,24);cin >> quant;
       if(quant <= 0){
            bordaFunction();
            gotoxy(63,22);cout << "Quantidade invalida!\nInsira uma quantidade superior a zero." << endl;
            Sleep(1000);
       } else {
           break;
       }
    }
    json::modificaQuantidade(pos, quant);
    txt::modificaQuantidade(pos, quant, checkQuant, true, check);

    if(!checkQuant){
        bordaFunction();
        gotoxy(63,22);cout << "Quantidade alterada com sucesso!" << endl;
        Sleep(1000);
    }

}

void visualizarEstoqueCase(struct estoque produtos){
    char opcao;
    system("cls");
    textbackground(DARKGRAY);
    system("cls");
    textcolor(WHITE);
    gotoxy(2,0);cout << "VISUALIZAR ESTOQUE" << endl;
    visualizarEstoque();
}

// switch cases caixa

void passarProdutoCase(struct estoque produtos, struct notaFiscal dados){
    char opcao;
    int quant;
    bool checkQuant, validQuant;
    iniciaArquivo();
    float totalVendaProduto, pagamento, totalCustoProduto, venda, custo;
    totalCustoProduto = totalVendaProduto = 0;
    int quantidadeItens;
    quantidadeItens = 0;
    do{
        validQuant = false;
        bordaFunction();
        gotoxy(63,21);cout << "Digite o ID do produto: ";
        gotoxy(63,22);cin >> produtos.id;
        while(true){
            bordaFunction();
            gotoxy(63,21);cout << "Digite a quantidade: ";
            gotoxy(63,22);cin >> produtos.quant;
            if(produtos.quant <= 0){
                bordaFunction();
                gotoxy(63,22);cout << "Quantidade invalida!\nInsira uma quantidade superior a zero." << endl;
                Sleep(1000);
            } else {
                break;
            }
        }
        quantidadeItens += produtos.quant;

        pegaDadosProduto(produtos.id, dados);

        quant = -produtos.quant;

        txt::modificaQuantidade(produtos.id, quant, checkQuant, false, validQuant);
        json::modificaQuantidade(produtos.id, quant);
        bordaFunction();
        gotoxy(63,21);cout << "Deseja continuar? <s - n> ";
        gotoxy(63,22);cin >> opcao;
        pegaValor(produtos.id, venda, custo);

        if(validQuant){
            totalVendaProduto += (produtos.quant * venda);
            totalCustoProduto += (produtos.quant * custo);

            dadosCaixaProdutos(dados, produtos, opcao, totalVendaProduto);
        }

    } while(opcao != 'n' && opcao != 'N');
    if(validQuant){
        cout << fixed << setprecision(2);
        alteraValoresCaixaParcial(totalVendaProduto, totalCustoProduto);
        while(true){
            bordaFunction();
            gotoxy(63,21);cout << "Total a pagar R$" << totalVendaProduto << endl;
            gotoxy(63,22);cout << "Insira o valor pago: ";
            gotoxy(63,23);cin >> pagamento;
            if(pagamento < totalVendaProduto){
                bordaFunction();
                gotoxy(63,24);cout << "O pagamento nao pode ser" << endl;
                gotoxy(63,25);cout << "menor que o total da compra!" << endl;
                Sleep(1000);
            } else {
                break;
            }
        }
        gotoxy(63,24);cout << "Troco: R$" << pagamento - totalVendaProduto << endl;
        insereContaNaNota(totalVendaProduto, pagamento, quantidadeItens);
        gotoxy(63,26);system("pause");
    }
}

void exibeFluxoDeCaixaCase(){
    char opcao;
    bordaFunction();
    exibeFluxoDeCaixa();
    gotoxy(63,26);system("pause");
}


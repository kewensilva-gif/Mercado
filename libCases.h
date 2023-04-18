// switch cases estoque

void criarListaCase(struct estoque produtos){
    char opcao, continuar;
    system("cls");
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
    fluxoDeCaixa();
}

void inserirProdutoCase(struct estoque produtos){
    char opcao;
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
}

void removerItemCase(struct estoque produtos){
    int pos;
    system("cls");
    cout << "REMOVER PRODUTO" << endl;
    cout << "Digite o ID do produto: ";
    cin >> pos;
    json::removerProduto(pos);
    txt::removerProduto(pos);
}

void adicionarQuantCase(struct estoque produtos){
    int pos, quant;
    bool checkQuant;

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

}

void visualizarEstoqueCase(struct estoque produtos){
    char opcao;
    system("cls");
    cout << "VISUALIZAR ESTOQUE" << endl;
    visualizarEstoque();

    cout << "Voltar ao menu? <s>";
    cin >> opcao;
}

// switch cases caixa

void passarProdutoCase(struct estoque produtos, struct notaFiscal dados){
    char opcao;
    int quant;
    bool checkQuant;
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
    while(true){
        cout << "Insira o valor pago: ";
        cin >> pagamento;
        if(pagamento < total){
            cout << "O pagamento não pode ser menor que o total da compra!" << endl;
        } else {
            break;
        }
    }
    cout << "Troco: R$" << pagamento - total << endl;
    insereContaNaNota(total, pagamento, quantidadeItens);
    cout << "Voltar ao menu de caixa? <s> ";
    cin >> opcao;
}

void exibeFluxoDeCaixaCase(){
    char opcao;
    system("cls");
    exibeFluxoDeCaixa();
    cout << "Voltar ao menu? <s>";
    cin >> opcao;
}

void saindo(){
    system("cls");
    cout << "saindo..." << endl;
    Sleep(2000);
}

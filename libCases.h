// switch cases estoque

void criarListaCase(struct estoque produtos){
    char opcao;
    char continuar;
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

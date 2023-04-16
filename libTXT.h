namespace txt{
    void dados(ofstream& produtosOut, struct estoque produtos){
        produtosOut << "**Produto**" << endl;
        produtosOut << "Nome: " << produtos.nome << endl;
        produtosOut << "Quantidade: " << produtos.quant << endl;
        produtosOut << "Marca: " << produtos.marca << endl;
        produtosOut << "Custo: " << produtos.custo << endl;
        produtosOut << "Valor: " << produtos.valor << endl;
        produtosOut << "id: " << ++produtos.id << endl;
    }

    void criarLista(struct estoque produtos){
        produtos.id = produtos.id - 1;
        ofstream produtosOut;
        produtosOut.open("produtos.txt");

        dados(produtosOut, produtos);

        produtosOut.close();
    }

    void inserirProduto(struct estoque produtos){
        ofstream produtosOut;
        produtosOut.open("produtos.txt", ios::app);

        dados(produtosOut, produtos);

        produtosOut.close();
    }

    void removerProduto(int id){
        string pesquisa, linha, arquivo;
        int cont, cont2;
        bool checkId = false;
        cont = cont2 = 0;
        pesquisa = "id: " + to_string(id);

        pegaQuantLinhas(cont, pesquisa, "produtos.txt", checkId);

        if(checkId){
            fstream produtosInOut;
            produtosInOut.open("produtos.txt", ios::in);

            if(produtosInOut.is_open()){
                while(getline(produtosInOut, linha)){
                    cont2++;
                    if(cont2 >= cont-TAM && cont2 <= cont){
                        continue;
                    } else {
                        arquivo += linha + "\n";
                    }
                }
            }

            produtosInOut.close();

            produtosInOut.open("produtos.txt", ios::out);
            produtosInOut << arquivo;
            produtosInOut.close();
        }
    }

    void modificaQuantidade(int id, int quant){
        string pesquisa, linha, strQuant, strAcum, arquivo, str;
        bool checkId = false;
        int cont, cont2;
        cont = cont2 = 0;

        pesquisa = "id: " + to_string(id);

        pegaQuantLinhas(cont, pesquisa, "produtos.txt", checkId);
          if(checkId){
            fstream produtosInOut;
            produtosInOut.open("produtos.txt", ios::in);
            if(produtosInOut.is_open()){
                while(getline(produtosInOut, linha)){
                    cont2++;
                    if(cont2 == cont + 2 - TAM){
                        strQuant = linha;
                        break;
                    }
                }
            }

            produtosInOut.close();

            for(int i = 0; i < strlen(strQuant.c_str()); i++){
                if(strQuant[i] == ':'){
                    i += 2;
                    strAcum = strQuant[i++];

                    while(true){
                        if(strQuant[i] != '\n'){
                            strAcum += strQuant[i++];
                        } else {
                            break;
                        }
                    }
                }
            }
            quant += stoi(strAcum);
            str = "Quantidade: " + to_string(quant);

            produtosInOut.open("produtos.txt", ios::in);

            if(produtosInOut.is_open()){
                cont2 = 0;

                while(getline(produtosInOut, linha)){
                    cont2++;
                    if(cont2 == cont + 2 - TAM){
                        arquivo += str + "\n";
                    } else {
                        arquivo += linha + "\n";
                    }
                }
            }

            produtosInOut.close();

            produtosInOut.open("produtos.txt", ios::out);
            produtosInOut << arquivo;
            produtosInOut.close();

        } else {
            cout << "O ID não existe!" << endl;
        }
    }
}

namespace txt{
    void dados(ofstream& produtosOut, struct estoque produtos){
        produtosOut << "**Produto**" << endl;
        produtosOut << "Nome: " << produtos.nome << endl;
        produtosOut << "Quantidade: " << produtos.quant << endl;
        produtosOut << "Marca: " << produtos.marca << endl;
        produtosOut << "Custo: " << produtos.custo << endl;
        produtosOut << "Venda: " << produtos.venda << endl;
        produtosOut << "id: " << ++produtos.id << endl;
    }

    void criarLista(struct estoque produtos){
        produtos.id = produtos.id - 1;
        ofstream produtosOut;
        produtosOut.open("produtos.txt");

        dados(produtosOut, produtos);

        produtosOut.close();
    }

    void inserirProduto(struct estoque &produtos){
        ofstream produtosOut;
        produtosOut.open("produtos.txt", ios::app);

        dados(produtosOut, produtos);

        produtosOut.close();

        alteraValoresCaixa(produtos);
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
                    if(cont2 >= cont-TAM-1 && cont2 <= cont){
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
            bordaFunction();
            gotoxy(63,22);cout << "Item removido com sucesso!" << endl;
            Sleep(1000);
        } else {
            bordaFunction();
            gotoxy(63,22);cout << "O ID nao existe!" << endl;
            Sleep(1000);
        }
    }

    void modificaQuantidade(int id, int quant, bool &checkQuant, bool check, bool &validQuant){
        struct estoque produtos;
        produtos.quant = quant;
        string pesquisa, linha, strQuant, strAcum, strVenda, strCusto, arquivo, str;
        bool checkId = false;
        checkQuant = false;
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
                    if(cont2 == cont + 1 - TAM){
                        strQuant = linha;
                    }
                    if(cont2 == cont + 3 - TAM){
                        strCusto = linha;
                    }
                    if(cont2 == cont + 4 - TAM){
                        strVenda = linha;
                        break;
                    }
                }
            }

            produtosInOut.close();


            pegaCustoEVenda(strCusto, strVenda, produtos, check);

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
            if(quant >= 0){
                validQuant = true;
                checkQuant = true;
                str = "Quantidade: " + to_string(quant);

                produtosInOut.open("produtos.txt", ios::in);

                if(produtosInOut.is_open()){
                    cont2 = 0;

                    while(getline(produtosInOut, linha)){
                        cont2++;
                        if(cont2 == cont + 1 - TAM){
                            arquivo += str + "\n";
                        } else {
                            arquivo += linha + "\n";
                        }
                    }


                produtosInOut.close();

                produtosInOut.open("produtos.txt", ios::out);
                produtosInOut << arquivo;
                produtosInOut.close();
                validQuant = true;
                } else {
                    bordaFunction();
                    gotoxy(63,22);cout << "O ID nao existe!" << endl;
                    validQuant = false;
                    Sleep(1000);
                }

            } else {
                bordaFunction();
                gotoxy(63,22);cout << "Nao ha produtos suficientes em estoque!" << endl;
                gotoxy(63,23);cout << "Insira outra quantidade." << endl;
                validQuant = false;
                Sleep(1000);
            }
        }
    }
}

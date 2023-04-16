namespace json{
    // função que agrupa os dados que serão inseridos nos arquivos
    void dados(ofstream& produtosOut, struct estoque produtos){
        produtosOut << "\t\t\t\"Nome\": \"" << produtos.nome << "\","<< endl;
        produtosOut << "\t\t\t\"Quantidade\": " << produtos.quant << ","<< endl;
        produtosOut << "\t\t\t\"Marca\": \"" << produtos.marca << "\","<< endl;
        produtosOut << "\t\t\t\"Custo\": " << produtos.custo << "," << endl;
        produtosOut << "\t\t\t\"Venda\": " << produtos.venda << "," << endl;
        produtosOut << "\t\t\t\"id\": " << ++produtos.id << endl;
    }
    // Esta função cria o arquivo json caso ele não exista e se existir ela o sobrescreve
    void criarLista(struct estoque produtos){
            produtos.id = produtos.id - 1;
            ofstream produtosOut;
            produtosOut.open("produtos.json");
            produtosOut << "{\n\t\"produtos\": [ " << endl;

            produtosOut << "\t\t{" << endl;

            dados(produtosOut, produtos);

            produtosOut << "\t\t}" << endl;

            produtosOut << "\t]\n}" << endl;
            produtosOut.close();
    }


    /* Esta função insere um objeto json da seguinte forma
    1 - Abre o arquivo para leitura, verifica linha por linha até chegar
    da chave de fechamento do ultimo objeto já existente e guarda tudo isso em uma string.
    Aí então, o arquivo é fechado.
    2 - Depois o arquivo é aberto para saida de dados, onde é inserido o novo objeto, aplicando
    a sintaxe de json.
    */
    void inserirProduto(struct estoque produtos){
        string arquivo;
        string linha;

        ifstream produtosIn;
        produtosIn.open("produtos.json");
        if(produtosIn.is_open()){
            while(getline(produtosIn, linha)){
                if(linha == "\t\t}"){
                    break;
                } else
                    arquivo += (linha + "\n");
            }
        } else {
            cout << "Não foi possivel abrir o arquivo" << endl;
        }

        produtosIn.close();

        ofstream produtosOut;
        produtosOut.open("produtos.json");

        produtosOut << arquivo;
        produtosOut << "\t\t}," << endl;
        produtosOut << "\t\t{" << endl;

        dados(produtosOut, produtos);

        produtosOut << "\t\t}" << endl;
        produtosOut << "\t]\n}" << endl;

        produtosOut.close();
    }


    /*Esta função remove um objeto json
     1 - chama a função pegaQuantLinhas
     2 - com um segundo contador verifica as linha que serão removidas
     3 - guarda as linha que não foram removidas na string arquivo
     4 - fecha o arquivo e agora abre para saída
     5 - insere a string arquivo no arquivo "produtos"
     6 - fecha o arquivo
    */
    void removerProduto(int id){
        string strId, pesquisa, linha, arquivo;
        int cont, cont2;
        bool ehUltimo, checkId;

        cont = cont2 = 0;
        ehUltimo = checkId = false;
        pesquisa = "\t\t\t\"id\": " + to_string(id);
        strId = pegaStringUltimoId();

        if(strId == pesquisa){
            ehUltimo = true;
        }

        pegaQuantLinhas(cont, pesquisa, "produtos.json", checkId);

        if(checkId){
            fstream produtosInOut;
            produtosInOut.open("produtos.json", ios::in);
            if(produtosInOut.is_open()){
                while(getline(produtosInOut, linha)){
                    cont2++;
                    if(cont2 >= cont-TAM-1 && cont2 <= cont+1){
                        continue;
                    } else if("\t\t}," == linha && ehUltimo){
                        arquivo += "\t\t}\n";
                    } else {
                        arquivo += linha + "\n";
                    }
                }
            }

            produtosInOut.close();

            produtosInOut.open("produtos.json", ios::out);
            produtosInOut << arquivo;
            produtosInOut.close();

            cout << "Produto removido com sucesso!" << endl;
            Sleep(2000);
        } else {
            cout << "O ID não existe!" << endl;
            Sleep(2000);
        }
    }

    void modificaQuantidade(int id, int quant){
        string pesquisa, linha, strQuant, strAcum, arquivo, str;
        bool checkId = false;
        int cont, cont2;
        cont = cont2 = 0;

        pesquisa = "\t\t\t\"id\": " + to_string(id);

        pegaQuantLinhas(cont, pesquisa, "produtos.json", checkId);
          if(checkId){
            fstream produtosInOut;
            produtosInOut.open("produtos.json", ios::in);
            if(produtosInOut.is_open()){
                while(getline(produtosInOut, linha)){
                    cont2++;
                    if(cont2 == cont + 1 - TAM){
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
                        if(strQuant[i] != ','){
                            strAcum += strQuant[i++];
                        } else {
                            break;
                        }
                    }
                }
            }
            quant += stoi(strAcum);
            str = "\t\t\t\"Quantidade\": " + to_string(quant);

            produtosInOut.open("produtos.json", ios::in);

            if(produtosInOut.is_open()){
                cont2 = 0;

                while(getline(produtosInOut, linha)){
                    cont2++;
                    if(cont2 == cont + 1 - TAM){
                        arquivo += str + ",\n";
                    } else {
                        arquivo += linha + "\n";
                    }
                }
            }

            produtosInOut.close();

            produtosInOut.open("produtos.json", ios::out);
            produtosInOut << arquivo;
            produtosInOut.close();

            cout << "Quantidade alterada com sucesso!" << endl;
            Sleep(3000);
        } else {
            cout << "O ID não existe!" << endl;
        }
    }
}

#define TAM 5

// fun��o que agrupa os dados que ser�o inseridos nos arquivos
void dadosTxt(ofstream& produtosOut, struct estoque produtos){
    produtosOut << "**Produto**" << endl;
    produtosOut << "Nome: " << produtos.nome << endl;
    produtosOut << "Quantidade: " << produtos.quant << endl;
    produtosOut << "Marca: " << produtos.marca << endl;
    produtosOut << "Valor: " << produtos.valor << endl;
    produtosOut << "id: " << ++produtos.id << endl;
}

void dadosJson(ofstream& produtosOut, struct estoque produtos){
    produtosOut << "\t\t\t\"Nome\": \"" << produtos.nome << "\","<< endl;
    produtosOut << "\t\t\t\"Quantidade\": " << produtos.quant << ","<< endl;
    produtosOut << "\t\t\t\"Marca\": \"" << produtos.marca << "\","<< endl;
    produtosOut << "\t\t\t\"Valor\": " << produtos.valor << "," << endl;
    produtosOut << "\t\t\t\"id\": " << ++produtos.id << endl;
}

/*Esta fun��o utiliza sobrecarga e o seu objetivo � trazer a quantidade de linhas do arquivo
1 - abre o arquivo e com o auxilio de um contador pega a quantidade de linha
*/
void pegaQuantLinhas(int& cont, string arquivo){
    string linha;
    ifstream produtosIn;

    produtosIn.open(arquivo);

    if(produtosIn.is_open()){
        while(getline(produtosIn, linha)){
            cont++;
        }
    } else {
        cout << "N�o foi poss�vel abrir o arquivo!" << endl;
    }


    produtosIn.close();
}

/* Aqui ela tem um breakpoint personalisado
1 - � passado no segundo par�metro a string que vai servir de breakpoint
2 - caso ela seja encontrada o programa sai do loop e o contador s� � somado at� aquela linha
3 - O terceiro parametro � para verificar se o id exite
*/

void pegaQuantLinhas(int& cont, string condicao, string arquivo, bool& check){
    check = false;
    string linha;
    ifstream produtosIn;

    produtosIn.open(arquivo, ios::in);

    if(produtosIn.is_open()){
        while(getline(produtosIn, linha)){
            cont++;
            if(condicao == linha){
                check = true;
                break;
            }
        }
    } else {
        cout << "N�o foi poss�vel abrir o arquivo!" << endl;
    }


    produtosIn.close();
}

// Esta fun��o pega os dados do produto
void pegaDados(struct estoque &produtos){
    cout << "Digite o nome do produto: ";
    cin >> produtos.nome;
    cout << "Digite a quantidade: ";
    cin >> produtos.quant;
    cout << "Digite a marca: ";
    cin >> produtos.marca;
    cout << "Digite o valor: ";
    cin >> produtos.valor;
}

/* Esta fun��o pega o id do �ltimo objeto inserido no json da seguinte forma:
1 - pega a quantidade de linhas com a fun��o pegaQauntLinhas que retorna um contador
2 - Depois ele utiliza outro contador e quando este tiver o valor do primeiro subtraido 3 � guardada a linha
referente a posi��o.
4 - Assim � possivel pegar a linha onde est� o id do �ltimo objeto
*/
string pegaStringUltimoId(){
    string linha, aux;
    int cont, cont2 = 0;

    pegaQuantLinhas(cont, "produtos.json");

    ifstream produtosIn;
    produtosIn.open("produtos.json");

    if(produtosIn.is_open()){
        while(getline(produtosIn, linha)){
            cont2++;
            if(cont-3 == cont2){
                aux = linha;
            }
        }

    } else {
        cout << "N�o foi poss�vel abrir o arquivo" << endl;
    }

    produtosIn.close();
    return aux;
}

/*Esta fun��o utiliza a fun��o pegaStringUltimo id e converte em inteiro
1 - guarda a string retornada
2 - Depois � feito um loop pra pegar apenas a parte num�rica dessa string
3 - E ent�o � utilizada a fun��o stoi para converter em inteiro;
*/
int converteId(){
    string aux, aux2;
    int len, id;

    aux = pegaStringUltimoId();
    len = len = strlen(aux.c_str());

    for(int i = 0; i < len; i++){
        if(i == len-2 || i == len-1){
            aux2 += aux[i];
        }
    }

    id = stoi(aux2);
    return id;
}

// Esta fun��o cria o arquivo json caso ele n�o exista e se existir ela o sobrescreve
void criarListaJson(struct estoque produtos){
        produtos.id = produtos.id - 1;
        ofstream produtosOut;
        produtosOut.open("produtos.json");
        produtosOut << "{\n\t\"produtos\": [ " << endl;

        produtosOut << "\t\t{" << endl;

        dadosJson(produtosOut, produtos);

        produtosOut << "\t\t}" << endl;

        produtosOut << "\t]\n}" << endl;
        produtosOut.close();
}

// Esta fun��o cria o arquivo txt caso ele n�o exista e se existir ela sobrescreve

void criarListaTxt(struct estoque produtos){
    produtos.id = produtos.id - 1;
    ofstream produtosOut;
    produtosOut.open("produtos.txt");

    dadosTxt(produtosOut, produtos);

    produtosOut.close();
}


/* Esta fun��o insere um objeto json da seguinte forma
1 - Abre o arquivo para leitura, verifica linha por linha at� chegar
da chave de fechamento do ultimo objeto j� existente e guarda tudo isso em uma string.
A� ent�o, o arquivo � fechado.
2 - Depois o arquivo � aberto para saida de dados, onde � inserido o novo objeto, aplicando
a sintaxe de json.
*/
void inserirProdutoJson(struct estoque produtos){
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
        cout << "N�o foi possivel abrir o arquivo" << endl;
    }

    produtosIn.close();

    ofstream produtosOut;
    produtosOut.open("produtos.json");

    produtosOut << arquivo;
    produtosOut << "\t\t}," << endl;
    produtosOut << "\t\t{" << endl;

    dadosJson(produtosOut, produtos);

    produtosOut << "\t\t}" << endl;
    produtosOut << "\t]\n}" << endl;

    produtosOut.close();
}

// Esta fun��o insere uma tabela do produto s� que agora para um arquivo txt
void inserirProdutoTxt(struct estoque produtos){
    ofstream produtosOut;
    produtosOut.open("produtos.txt", ios::app);

    dadosTxt(produtosOut, produtos);

    produtosOut.close();
}


/*Esta fun��o remove um objeto json
 1 - chama a fun��o pegaQuantLinhas
 2 - com um segundo contador verifica as linha que ser�o removidas
 3 - guarda as linha que n�o foram removidas na string arquivo
 4 - fecha o arquivo e agora abre para sa�da
 5 - insere a string arquivo no arquivo "produtos"
 6 - fecha o arquivo
*/
void removerProdutoJson(int id){
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
                if(cont2 >= cont-TAM && cont2 <= cont+1){
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
    } else {
        cout << "O ID n�o existe!" << endl;
    }
}

void removerProdutoTxt(int id){
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

/*Esta função utiliza sobrecarga e o seu objetivo é trazer a quantidade de linhas do arquivo
1 - abre o arquivo e com o auxilio de um contador pega a quantidade de linha
*/
void pegaQuantLinhas(int& cont, string arquivo){
    string linha;
    fstream produtos;

    produtos.open(arquivo, ios::in);

    if(produtos.is_open()){
        while(getline(produtos, linha)){
            cont++;
        }
    } else {
        cout << "Não foi possível abrir o arquivo!" << endl;
    }


    produtos.close();
}

/* Aqui ela tem um breakpoint personalisado
1 - é passado no segundo parâmetro a string que vai servir de breakpoint
2 - caso ela seja encontrada o programa sai do loop e o contador só é somado até aquela linha
3 - O terceiro parametro é para verificar se o id exite
*/

void pegaQuantLinhas(int& cont, string condicao, string arquivo, bool& check){
    check = false;
    string linha;
    ifstream produtos;

    produtos.open(arquivo, ios::in);

    if(produtos.is_open()){
        while(getline(produtos, linha)){
            cont++;
            if(condicao == linha){
                check = true;
                break;
            }
        }
    } else {
        cout << "Não foi possível abrir o arquivo!" << endl;
    }


    produtos.close();
}

// Esta função pega os dados do produto
void pegaDados(string& nome, int& quant, string& marca){
    cout << "Digite o nome do produto: ";
    cin >> nome;
    cout << "Digite a quantidade: ";
    cin >> quant;
    cout << "Digite a marca: ";
    cin >> marca;
}

/* Esta função pega o id do último objeto inserido no json da seguinte forma:
1 - pega a quantidade de linhas com a função pegaQauntLinhas que retorna um contador
2 - Depois ele utiliza outro contador e quando este tiver o valor do primeiro subtraido 3 é guardada a linha
referente a posição.
4 - Assim é possivel pegar a linha onde está o id do último objeto
*/
string pegaStringUltimoId(){
    string linha, aux;
    int cont, cont2 = 0;

    pegaQuantLinhas(cont, "produtos.json");

    ifstream produtos;
    produtos.open("produtos.json");

    if(produtos.is_open()){
        while(getline(produtos, linha)){
            cont2++;
            if(cont-3 == cont2){
                aux = linha;
            }
        }

    } else {
        cout << "Não foi possível abrir o arquivo" << endl;
    }

    return aux;
}

/*Esta função utiliza a função pegaStringUltimo id e converte em inteiro
1 - guarda a string retornada
2 - Depois é feito um loop pra pegar apenas a parte numérica dessa string
3 - E então é utilizada a função stoi para converter em inteiro;
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

// Esta função cria o arquivo json caso ele não exista e se existir ela o sobrescreve
void criarListaJson(string nome, int quant, string marca, int id){

        fstream produtos;
        produtos.open("produtos.json", ios::out);
        produtos << "{\n\t\"produtos\": [ " << endl;

        produtos << "\t\t{" << endl;
        produtos << "\t\t\t\"Nome\": \"" << nome << "\","<< endl;
        produtos << "\t\t\t\"Quantidade\": " << quant << ","<< endl;
        produtos << "\t\t\t\"Marca\": \"" << marca << "\","<< endl;
        produtos << "\t\t\t\"id\": " << id++ << endl;
        produtos << "\t\t}" << endl;

        produtos << "\t]\n}" << endl;
        produtos.close();

}

// Esta função cria o arquivo txt caso ele não exista e se existir ela sobrescreve

void criarListaTxt(string nome, int quant, string marca, int id){
    ofstream produtos;
    produtos.open("produtos.txt");

    produtos << "**Produto**" << endl;
    produtos << "Nome: " << nome << endl;
    produtos << "Quantidade: " << quant << endl;
    produtos << "Marca: " << marca << endl;
    produtos << "id: " << id++ << endl;

}


/* Esta função insere um objeto json da seguinte forma
1 - Abre o arquivo para leitura, verifica linha por linha até chegar
da chave de fechamento do ultimo objeto já existente e guarda tudo isso em uma string.
Aí então, o arquivo é fechado.
2 - Depois o arquivo é aberto para saida de dados, onde é inserido o novo objeto, aplicando
a sintaxe de json.
*/
void inserirProdutoJson(string nome, int quant, string marca, int id){

    fstream produtos;
    string arquivo;
    string linha;
    produtos.open("produtos.json", ios::in);
    if(produtos.is_open()){
        while(getline(produtos, linha)){
            if(linha == "\t\t}"){
                break;
            } else
                arquivo += (linha + "\n");
        }
    } else {
        cout << "Não foi possivel abrir o arquivo" << endl;
    }

    produtos.close();

    produtos.open("produtos.json", ios::out);

    produtos << arquivo;
    produtos << "\t\t}," << endl;
    produtos << "\t\t{" << endl;
    produtos << "\t\t\t\"Nome\": \"" << nome << "\","<< endl;
    produtos << "\t\t\t\"Quantidade\": " << quant << ","<< endl;
    produtos << "\t\t\t\"Marca\": \"" << marca << "\","<< endl;
    produtos << "\t\t\t\"id\": " << ++id << endl;
    produtos << "\t\t}" << endl;
    produtos << "\t]\n}" << endl;

    produtos.close();

}

// Esta função insere uma tabela do produto só que agora para um arquivo txt
void inserirProdutoTxt(string& nome, int& quant, string& marca, int id){
    ofstream produtos;
    produtos.open("produtos.txt", ios::app);

    produtos << "**Produto**" << endl;
    produtos << "Nome: " << nome << endl;
    produtos << "Quantidade: " << quant << endl;
    produtos << "Marca: " << marca << endl;
    produtos << "id: " << ++id << endl;

    produtos.close();
}


/*Esta função remove um objeto json
 1 - chama a função pegaQuantLinhas
 2 - com um segundo contador verifica as linha que serão removidas
 3 - guarda as linha que não foram removidas na string arquivo
 4 - fecha o arquivo e agora abre para saída
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
        fstream produtos;
        produtos.open("produtos.json", ios::in);
        if(produtos.is_open()){
            while(getline(produtos, linha)){
                cont2++;
                if(cont2 >= cont-4 && cont2 <= cont+1){
                    continue;
                } else if("\t\t}," == linha && ehUltimo){
                    arquivo += "\t\t}\n";
                } else {
                    arquivo += linha + "\n";
                }
            }
        }

        produtos.close();

        produtos.open("produtos.json", ios::out);
        produtos << arquivo;
        produtos.close();
    } else {
        cout << "O ID não existe!" << endl;
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
        fstream produtos;
        produtos.open("produtos.txt", ios::in);

        if(produtos.is_open()){
            while(getline(produtos, linha)){
                cont2++;
                if(cont2 >= cont-5){
                    continue;
                } else {
                    arquivo += linha + "\n";
                }
            }
        }

        produtos.close();

        produtos.open("produtos.txt", ios::out);
        produtos << arquivo;
        produtos.close();
    }
}

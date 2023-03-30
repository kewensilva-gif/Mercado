
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
1 - o arquivo é aberto para leitura duas vezes
2 - Na primeira leitura ele faz a contagem de linha existentes e guarda no primeiro contador
3 - Na segunda ele utiliza outro contador e quando este tiver o valor do primeiro subtraido 3 é guardada a linha
referente a posição.
4 - Assim é possivel pegar a linha onde está o id do último objeto
5 - Depois é feito um loop pra pegar apenas a parte numérica dessa string
6 - E então é utilizada a função stoi para converter em inteiro;
*/
string pegaStringUltimoId(){
    fstream produtos;

    string linha, aux;
    int cont = 0, cont2 = 0;

    produtos.open("produtos.json", ios::in);

    if(produtos.is_open()){
        while(getline(produtos, linha)){
            cont++;
        }
    } else {
        cout << "Não foi possível abri o arquivo" << endl;
    }

    produtos.close();

    produtos.open("produtos.json", ios::in);

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

void removerProdutoJson(int id){
    string strId, pesquisa, linha, arquivo;
    int cont, cont2;
    bool ehUltimo = false;

    cont = cont2 = 0;
    pesquisa = "\t\t\t\"id\": " + to_string(id);
    strId = pegaStringUltimoId();

    if(strId == pesquisa){
        ehUltimo = true;
    }

    fstream produtos;

    produtos.open("produtos.json", ios::in);

    if(produtos.is_open()){
        while(getline(produtos, linha)){
            cont++;
            if(pesquisa == linha){
                break;
            }
        }
    } else {
        cout << "Não foi possível abrir o arquivo!" << endl;
    }


    produtos.close();

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
}

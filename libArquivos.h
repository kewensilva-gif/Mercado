#define TAM 5
#include <stdlib.h>
#include <string.h>
/*Esta função utiliza sobrecarga e o seu objetivo é trazer a quantidade de linhas do arquivo
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
        cout << "Não foi possível abrir o arquivo!" << endl;
    }


    produtosIn.close();
}

/* Aqui ela tem um breakpoint personalisado
1 - é passado no segundo parâmetro a string que vai servir de breakpoint
2 - caso ela seja encontrada o programa sai do loop e o contador só é somado até aquela linha
3 - O terceiro parametro é para verificar se o id exite
*/

void pegaQuantLinhas(int& cont, string condicao, string arquivo, bool& check){
    check = false;
    string linha;
    ifstream produtosIn;

    produtosIn.open(arquivo);

    if(produtosIn.is_open()){
        while(getline(produtosIn, linha)){
            cont++;
            if(condicao == linha){
                check = true;
                break;
            }
        }
    } else {
        cout << "Não foi possível abrir o arquivo!" << endl;
    }


    produtosIn.close();
}


// Esta função pega os dados do produto
void pegaDados(struct estoque &produtos){
    cout << "Digite o nome do produto: ";
    cin.ignore();
    getline(cin, produtos.nome);
    cout << "Digite a quantidade: ";
    cin >> produtos.quant;
    cout << "Digite a marca: ";
    cin.ignore();
    getline(cin, produtos.marca);
    cout << "Digite o custo: ";
    cin >> produtos.custo;
    cout << "Digite o valor de venda: ";
    cin >> produtos.venda;
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
        cout << "Não foi possível abrir o arquivo" << endl;
    }

    produtosIn.close();
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
    len = strlen(aux.c_str());

    for(int i = 0; i < len; i++){
        if(i == len-2 || i == len-1){
            aux2 += aux[i];
        }
    }

    id = stoi(aux2);
    return id;
}

float pegaValor(int id){
    int cont, cont2 = 0;
    bool checkId = false;
    string pesquisa, strQuant, linha;
    pesquisa = "id: " + to_string(id);
    pegaQuantLinhas(cont, pesquisa, "produtos.txt", checkId);

    if(checkId){
            fstream produtosInOut;
            produtosInOut.open("produtos.txt", ios::in);
            if(produtosInOut.is_open()){
                while(getline(produtosInOut, linha)){
                    cont2++;
                    if(cont2 == cont + 4 - TAM){
                        strQuant = linha;
                        break;
                    }
                }
            }

            produtosInOut.close();
            string num;

            for(int i = 7; i < strlen(strQuant.c_str()); i++){
                num += strQuant[i];
            }

            double venda;
            venda = stof(num);

            return venda;
    }
}

void calculaCustoELucro(float& custo, float& totalVendas){
    custo = totalVendas = 0;
    string linha, acum;
    int quant;
    ifstream custoTotal;
    custoTotal.open("produtos.txt");

    if(custoTotal.is_open()){
        while(getline(custoTotal, linha)){
            if(linha[0] == 'Q'){
                acum = "";
                for(int i = 12; i < strlen(linha.c_str()); i++){
                    acum += linha[i];
                }

                quant = stoi(acum);
            }
            if(linha[0] == 'C'){
                acum = "";
                for(int i = 7; i < strlen(linha.c_str()); i++){
                    acum += linha[i];
                }
                custo += stof(acum) * quant;
            }
            if(linha[0] == 'V'){
                acum = "";
                for(int i = 7; i < strlen(linha.c_str()); i++){
                    acum += linha[i];
                }
                totalVendas += stof(acum) * quant;
            }
        }
    }

    custoTotal.close();
}

void preencheFluxoCaixa(string nomeArq, float custo, float valorVenda, float lucro){
    ofstream fluxo;

    fluxo.open(nomeArq);

    fluxo << "Custo total: R$" << custo << endl;
    fluxo << "Valor total possível de vendas: R$" << valorVenda << endl;
    fluxo << "Lucro possível: R$" << lucro << endl;

    fluxo.close();
}

void fluxoDeCaixa(){
    float custo, vendaTotalEstoque, lucroPossivel;

    calculaCustoELucro(custo, vendaTotalEstoque);

    lucroPossivel = vendaTotalEstoque - custo;

    preencheFluxoCaixa("fluxoDeCaixa.txt", custo, vendaTotalEstoque, lucroPossivel);
    /*ofstream fluxo;

    fluxo.open("fluxoDeCaixa.txt");

    fluxo << "Custo total: R$" << custo << endl;
    fluxo << "Valor total possível de vendas: R$" << vendaTotalEstoque << endl;
    fluxo << "Lucro possível: R$" << lucroPossivel << endl;

    fluxo.close();*/
}

void alteraValoresCaixa(struct estoque produtos){
    string linha, valores;
    float val[3], lucro, custo, valorVendas;

    bool entrou = false;
    ifstream caixa;
    caixa.open("fluxoDeCaixa.txt");

    if(caixa.is_open()){
        int j = 0;
        while(getline(caixa, linha)){
            entrou = false;
            valores = "";
            for(int i = 0; i < strlen(linha.c_str()); i++){
                if(linha[i] == '$'){
                    i++;
                    entrou = true;
                }
                if(entrou){
                    if(linha[i] == '.'){
                        valores += ',';
                    } else{
                        valores += linha[i];
                    }
                }
            }
            val[j] = stof(valores);
            j++;
        }
    }
    caixa.close();

    custo = val[0] + (produtos.quant*produtos.custo);
    valorVendas = val[1] + (produtos.quant*produtos.venda);
    lucro = val[2] + (produtos.quant*produtos.venda - produtos.quant*produtos.custo);

    preencheFluxoCaixa("fluxoDeCaixa.txt", custo, valorVendas, lucro);
}

void pegaCustoEVenda(string strCusto, string strVenda, struct estoque produtos){
    cout << strCusto << endl;
    cout << strVenda << endl;
    string val;


    for(int i = 7; i < strlen(strCusto.c_str()); i++){
        val += strCusto[i];
    }
    produtos.custo = stof(val);

    val = "";
    for(int i = 7; i < strlen(strVenda.c_str()); i++){
        val += strVenda[i];
    }
    produtos.venda = stof(val);

    cout << produtos.venda << endl;
    cout << produtos.custo << endl;
    cout << produtos.quant << endl;
    alteraValoresCaixa(produtos);
    Sleep(3000);
}

void exibeFluxoDeCaixa(){
    string linha;
    ifstream caixa;
    caixa.open("fluxoDeCaixa.txt");

    if(caixa.is_open()){
        while(getline(caixa, linha)){
            cout << linha << endl;
        }
    }

    caixa.close();
}

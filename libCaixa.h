//Assinaturas
void pegaDadosProduto(int id, struct notaFiscal &dados);
void dadosCaixaProdutos(struct notaFiscal dados, struct estoque produtos, char opcao, float total);
void dadosCaixaConta(ofstream& notaOut, float total, float entrada, int quantidade);
void iniciaArquivo();
void insereContaNaNota(float total, float entrada, int quantidade);

void calculaCustoELucro(float& custo, float& totalVendas);
void preencheFluxoCaixa(string nomeArq, float custo, float valorVenda, float lucro, string arquivo);
void fluxoDeCaixa();
void alteraValoresCaixa(struct estoque produtos);

void preencheFluxoCaixaParcial(string nomeArq, float custo, float valorVenda, float lucro, string arquivo);
void alteraValoresCaixaParcial(float venda, float custo);

// Nota fiscal
struct notaFiscal{
    string nome;
    string unidade;
    string marca;
    string precoUnidade;
    string precoTotal;
    string id;

    int quantItens;
    float total;
    float entrada;
    float troco;
};

void pegaDadosProduto(int id, struct notaFiscal &dados){
    int cont, cont2 = 0;
    int x;
    x = 0;
    bool checkId = false;
    string pesquisa, strDados, strDado, linha;
    pesquisa = "id: " + to_string(id);
    pegaQuantLinhas(cont, pesquisa, "produtos.txt", checkId);

    if(checkId){
            fstream produtosInOut;
            produtosInOut.open("produtos.txt", ios::in);
            if(produtosInOut.is_open()){
                x = 0;
                while(getline(produtosInOut, linha)){
                    cont2++;
                    if(cont2 >= cont - TAM && cont2 <= cont){

                        for(int i = 0; i < strlen(linha.c_str()); i++){
                            if(linha[i] == ':'){
                                i++;
                                i++;
                                strDado = "";
                                for(int j = i; j < strlen(linha.c_str()); j++){
                                    strDado += linha[j];
                                }
                            }
                        }
                        if(x == 0)
                            dados.nome = strDado;
                        if(x == 2)
                            dados.marca = strDado;
                        if(x == 4)
                            dados.precoUnidade = strDado;
                        x++;
                    }
                }
            }

            produtosInOut.close();
    }
}

void dadosCaixaProdutos(struct notaFiscal dados, struct estoque produtos, char opcao, float total){
    ofstream notaOut;
    notaOut.open("nota.json", ios::app);
    notaOut << "\t\t{" << endl;
    notaOut << "\t\t\t\"Nome\": \"" << dados.nome << "\","<< endl;
    notaOut << "\t\t\t\"Quantidade\": " << produtos.quant << ","<< endl;
    notaOut << "\t\t\t\"Marca\": \"" << dados.marca << "\","<< endl;
    notaOut << "\t\t\t\"PrecoUnidade\": " << dados.precoUnidade << "," << endl;
    notaOut << "\t\t\t\"PrecoTotal\": " << total << "," << endl;
    notaOut << "\t\t\t\"id\": " << produtos.id << endl;
    if(opcao == 'n' || opcao == 'N'){
        notaOut << "\t\t}" << endl;
    }
    else {
        notaOut << "\t\t}," << endl;
    }

    notaOut.close();
}

void dadosCaixaConta(ofstream& notaOut, float total, float entrada, int quantidade){
    notaOut << "\t\t\t\"QuantidadeItens\": " << quantidade << ","<< endl;
    notaOut << "\t\t\t\"Total\": " << total << ","<< endl;
    notaOut << "\t\t\t\"Entrada\": " << entrada << ","<< endl;
    notaOut << "\t\t\t\"Troco\": " << entrada - total << endl;
}

void iniciaArquivo(){
    ofstream notaOut;
    notaOut.open("nota.json");
    notaOut << "{\n\t\"produtos\": [ " << endl;
    notaOut.close();
}

void insereContaNaNota(float total, float entrada, int quantidade){
    ofstream notaOut;
    notaOut.open("nota.json", ios::app);
    notaOut << "\t]," << endl;
    notaOut << "\t\"conta\": [ " << endl;

    notaOut << "\t\t{" << endl;

    dadosCaixaConta(notaOut, total, entrada, quantidade);

    notaOut << "\t\t}" << endl;

    notaOut << "\t]\n}" << endl;
    notaOut.close();
}


//Calculo a partir do estoque

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

void preencheFluxoCaixa(string nomeArq, float custo, float valorVenda, float lucro, string arquivo){
    ofstream fluxo;

    fluxo.open(nomeArq);

    fluxo << "Custo total: R$" << custo << endl;
    fluxo << "Valor total possivel de vendas: R$" << valorVenda << endl;
    fluxo << "Lucro possivel: R$" << lucro << endl;
    fluxo << arquivo << endl;

    fluxo.close();
}


void fluxoDeCaixa(){
    float custo, vendaTotalEstoque, lucroPossivel;

    calculaCustoELucro(custo, vendaTotalEstoque);

    lucroPossivel = vendaTotalEstoque - custo;

    preencheFluxoCaixa("fluxoDeCaixa.txt", custo, vendaTotalEstoque, lucroPossivel, "\nTotal venda: R$0\nCusto dos produtos vendidos: R$0\nLucro em cima dos produtos vendidos: R$0");
}

void alteraValoresCaixa(struct estoque produtos){
    string linha, valores, arquivo;
    float val[3], lucro, custo, valorVendas;

    bool entrou = false;
    ifstream caixa;
    caixa.open("fluxoDeCaixa.txt");

    if(caixa.is_open()){
        int j = 0;
        int cont = 0;
        while(getline(caixa, linha)){
            if(cont >= 0 && cont < 3){
                entrou = false;
                valores = "";
                for(int i = 0; i < strlen(linha.c_str()); i++){
                    if(linha[i] == '$'){
                        i++;
                        entrou = true;
                    }
                    if(entrou){
                        valores += linha[i];
                    }
                }

            val[j] = stof(valores);

            j++;
            } else {
                arquivo += linha + "\n";
            }
            cont++;
        }
    }

    caixa.close();

    custo = val[0] + (produtos.quant*produtos.custo);
    valorVendas = val[1] + (produtos.quant*produtos.venda);
    lucro = val[2] + (produtos.quant*produtos.venda - produtos.quant*produtos.custo);

    preencheFluxoCaixa("fluxoDeCaixa.txt", custo, valorVendas, lucro, arquivo);
}

void pegaCustoEVenda(string strCusto, string strVenda, struct estoque produtos, bool check){
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

    if(check){
        alteraValoresCaixa(produtos);
    }
}

void exibeFluxoDeCaixa(){
    string linha;
    int y;
    y = 18;
    ifstream caixa;
    caixa.open("fluxoDeCaixa.txt");

    if(caixa.is_open()){
        while(getline(caixa, linha)){
            gotoxy(63,y++);cout << linha << endl;
        }
    }

    caixa.close();
}


void preencheFluxoCaixaParcial(string nomeArq, float custo, float valorVenda, float lucro, string arquivo){
    ofstream fluxo;

    fluxo.open(nomeArq);
    fluxo << arquivo;
    fluxo << "Total venda: R$" << valorVenda << endl;
    fluxo << "Custo dos produtos vendidos: R$" << custo << endl;
    fluxo << "Lucro em cima dos produtos vendidos: R$" << lucro << endl;

    fluxo.close();
}

void alteraValoresCaixaParcial(float venda, float custo){
    string linha, valores, arquivo, linha2;
    float val[3], lucroProdutosParcial, custoProdutosParcial, totalVendas;

    bool entrou = false;
    ifstream caixa;
    caixa.open("fluxoDeCaixa.txt");

    if(caixa.is_open()){
        int j = 0, cont = 0;
        while(getline(caixa, linha)){

            if(cont > 3 && cont < 7){
                entrou = false;
                valores = "";
                for(int i = 0; i < strlen(linha.c_str()); i++){
                    if(linha[i] == '$'){
                        i++;
                        entrou = true;
                    }
                    if(entrou){
                        valores += linha[i];
                    }
                }
                val[j] = stof(valores);
                j++;
            } else if(cont <= 3){
                arquivo += linha + "\n";
            } else {
                break;
            }
            cont++;
        }
    }
    caixa.close();


    custoProdutosParcial = val[1] + custo;
    lucroProdutosParcial = val[2] + (venda - custo);
    totalVendas = val[0] + venda;

    preencheFluxoCaixaParcial("fluxoDeCaixa.txt", custoProdutosParcial, totalVendas, lucroProdutosParcial, arquivo);
}

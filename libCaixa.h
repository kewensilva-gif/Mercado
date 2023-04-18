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

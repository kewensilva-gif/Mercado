#define TAM 5
#include <stdlib.h>
#include <string.h>
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
        cout << "N�o foi poss�vel abrir o arquivo!" << endl;
    }


    produtosIn.close();
}


// Esta fun��o pega os dados do produto
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

/*float calculaCusto(){

}*/

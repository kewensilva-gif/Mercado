#define TAM 5
#include <stdlib.h>
#include <string.h>


//Assinaturas
void pegaQuantLinhas(int& cont, string arquivo);
void pegaDados(struct estoque &produtos);
string pegaStringUltimoId();
string pegaStringUltimoId();
int converteId();
void pegaValor(int id, float &venda, float &custo);

void visualizarEstoque();



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
        bordaFunction();
        gotoxy(63, 22);cout << "Nao foi possivel abrir o arquivo!" << endl;
    }


    produtosIn.close();
}

/* Aqui ela tem um breakpoint personalisado
1 - é passado no segundo parâmetro a string que vai servir de breakpoint
2 - caso ela seja encontrada o programa sai do loop e o contador só é somado até aquela linha
3 - O terceiro parametro é para verificar se o id exite
*/

void pegaQuantLinhas(int& cont, string condicao, string arquivo, bool& check){
    cont = 0;
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
        bordaFunction();
        gotoxy(63, 22);cout << "Nao foi possivel abrir o arquivo!" << endl;
    }


    produtosIn.close();
}


// Esta função pega os dados do produto
void pegaDados(struct estoque &produtos){
    bordaFunction();

    gotoxy(63,22);
    cout << "Digite o nome do produto: ";
    cin.ignore();
    gotoxy(63,24);getline(cin, produtos.nome);
    bordaFunction();


    gotoxy(63,22);
    cout << "Digite a quantidade: ";
    gotoxy(63,24);
    cin >> produtos.quant;
    bordaFunction();


    gotoxy(63,22);
    cout << "Digite a marca: ";
    gotoxy(63,24);
    cin.ignore();
    getline(cin, produtos.marca);
    bordaFunction();


    gotoxy(63,22);
    cout << "Digite o custo: ";
    gotoxy(63,24);
    cin >> produtos.custo;

    produtos.venda = (produtos.custo * 1.8);
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
        bordaFunction();
        gotoxy(63, 22);cout << "Nao foi possivel abrir o arquivo!" << endl;
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

void pegaValor(int id, float &venda, float &custo){
    int cont;
    int cont2 = 0;
    bool checkId = false;
    string pesquisa, strVenda, strCusto, linha;
    pesquisa = "id: " + to_string(id);
    pegaQuantLinhas(cont, pesquisa, "produtos.txt", checkId);
    if(checkId){
            fstream produtosInOut;
            produtosInOut.open("produtos.txt", ios::in);
            if(produtosInOut.is_open()){
                while(getline(produtosInOut, linha)){
                    cont2++;

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
            string num;
            num = "";
            for(int i = 7; i < strlen(strVenda.c_str()); i++){
                num += strVenda[i];
            }

            venda = stof(num);
            num = "";
            for(int i = 7; i < strlen(strCusto.c_str()); i++){
                num += strCusto[i];
            }

            custo = stof(num);
    }
}



void visualizarEstoque(){
    string linha;
    ifstream produtosIn;
    int num, j;
    num = 3;
    j = 1;
    produtosIn.open("produtos.txt");

    if(produtosIn.is_open()){
        while(getline(produtosIn, linha)){
            if(linha == "**Produto**"){
                num++;
                gotoxy(2, num++);cout << "Produto " << j++ << endl ;

            } else{
                gotoxy(2, num++);cout << linha << endl;
            }
        }
    }

    produtosIn.close();

    gotoxy(2, num + 5);system("Pause");
}




//Uarlley do Nascimento Amorim - 2018205346
//Ualaci dos Anjos Junior - 2017102015

#include "Huffman.h"

//Parametros: (ponteiro para a cabeca da lista)
//Retorno: (Quantidade de caracteres presente no arquivo)
long long quantidadeCaracteres(Node* head){
    long long size = 0;
    //Soma a frequencia do caractere de cada nó para obter a quantidade maxima de caracteres no arquivo
    while(head){
        size += head->bstnode->freq;
        head = head->next;
    }
    return size;
}

//Parametros: (Altura da arvore, tamanho da tabela)
//Retorno: (Tabela contendo o codigo de Ruffman)
tab* criaTabela(int sizeTree, int sizeList){

    tab* tabela =(tab*) calloc(sizeList,sizeof(tab));//Aloca a memoria necessaria
    //Aloca o vetor de booleanos para armazenar o codigo de cada
    //caractere se a alocacao da tabela for bem sucedida
    if(tabela){
        for(int i=0;i<sizeList;i++){
            tabela[i].vet =(bool*) calloc(sizeTree,sizeof(bool));
        }
    }
    return tabela;
}

//Parametros: (Tabela do codigo de Ruffman, tamanho da tabela)
//Retorno: (vazio)
void printTabela(tab* tabela, int sizeTab) {
    //Percorre a tabela e imprimindo os caracteres e seus respectivos códigos
    for (int i = 0; i < sizeTab; i++) {
        if (tabela[i].size) {
            if (tabela[i].caractere == '\n') printf("Caractere : \\n - Código:  ");
            else if (tabela[i].caractere == ' ') printf("Caractere : espaco - Código:  ");
            else printf("Caractere : %c - Código:  ", tabela[i].caractere);
            for (int j = 0; j < (tabela[i].size); j++) printf("%i ", tabela[i].vet[j]);//Percorre o vetor
                                                                                        //booleano e o imprime
            printf("\n");
        }
    }
}

//Parametros: (vetor booleano, indice inicial, indice final, tabela de codigos, tamanho da tabela)
//Retorno: (resultado a busca do codigo do caractere no vetor booleano)
int verificaInLista(bool* binVet, int ini, int fim, tab* tabela, int sizeTab){
    for(int i = 0; i < sizeTab; i++){//Percorre toda a tabela buscando o codigo do vetor a partir dos indices
                                     //fornecidos
        if(tabela[i].size == fim-ini){//Se o tamanho dos codigos forem iguais seus campos sao comparados
            for(int j = ini; j < fim; j++){
                if(binVet[j] != tabela[i].vet[j-ini]) {
                    break; //Para a comparacao se encontrar um campo diferente
                }
                if(j==fim-1 && binVet[j] == tabela[i].vet[j-ini]) {
                    return i;//retorna a posicao do caractere na tabela se todos os campos forem iguais
                }
            }
        }
    }
    return -1;//retorna -1 se o codigo nao for encontrado
}

/*Parametros: (nome do arquivo de saida, vetor de codigos, tamanho do vetor de codigos, tabela, tamanho da
tabela, quantidade de caracteres lidos no arquivo de entrada)
Retorno: (vazio)*/
void imprimeSaida(char* nomeSaida, bool* binVet, int size, tab* tabela,int sizeTab, long long charQnt){
    FILE* newArquivo = fopen(nomeSaida, "w");//realiza a criacao do arquivo de saida
    int i, ini = 0,k = 0;
    for(i = 0; i < size; i++){//percorre o vetor de codigos de forma sequencial
        int pos = verificaInLista(binVet, ini, i+1, tabela,sizeTab);//verifica se o subcodigo esta associado
                                                                    //com algum caractere da tabela
        if(pos != -1) {//Se for encontrado um caractere, ele eh escrito no arquivo de saida, e a posicao inicial
                       //eh atualizada
            fwrite(&tabela[pos].caractere,sizeof(char),1,newArquivo);
            k++;
            ini = i+1;
            if (k == charQnt){//finaliza a funcao se a quantidade de caracteres presente no texto
                                //de entrada for igual a quantidade escrita ate este ponto
                break;
            }
        }
    }
    fclose(newArquivo);//fecha o arquivo de saida
}


//Parametros: (vetor com um codigo comprimido, tamanho do vetor)
//Retorno: ()
bool* intToBin (unsigned char vet[], int size){
    bool* binVet = (bool*) calloc(8*size,sizeof(bool)); //Aloca a memoria necessaria para realizar a conversao
    int i=0, j=7;
    for(i=0;i<size;i++){//Percorre o vetor realizando o processo de divisoes sucessivas
                        //adicionando os resultados no vetor de booleanos
        int num = vet[i];
        if(i==0) j=7;
        else j =7*(i+1)+i;
        while(num > 0){
            binVet[j] = num % 2;
            num = num/2;
            j--;
        }
    }
    return binVet;//retorna o vetor de booleandos contendo o valor comprimido convertido em binario
}

/*Parametros: (Nome do arquivo a ser lido, ponteiro para o tamanho da lista, ponteiro para quantidade de
caracteres no arquivo )
Retorno: (ponteiro para a cabeca de uma lista encadeada contendo cada caractere presente no artigo e sua
respectiva frequencia)*/
Node* leArquivo(char* nomeArquivo, int* sizeList, long long* charQnt) {
    Node* head = NULL;//Cria a cabeca da lista
    FILE* arquivo = fopen(nomeArquivo, "r");//realiza a abertura do arquivo
    if (!arquivo) printf("Arquivo nao existe");
    //Se o arquivo existir e realiza a leitura caractere por caractere
    else{
        fseek(arquivo, 0, SEEK_END);
        long int size = ftell(arquivo);//Guarda a ultima posicao do arquivo
        fseek(arquivo, 0, SEEK_SET);
        if(size == 0) return NULL; //retorna nulo se o arquivo estiver vazio
        while (ftell(arquivo) < size) {//le ate encontrar o final do arquivo
            char t;
            fread(&t, sizeof(char), 1, arquivo);
            /*verifica se o caracter ja esta na lista, se sim sua frequencia e incrementada, caso contrario
            o mesmo e inserido na lista*/
            if(searchList(head,t) == 0){
                head = insertList(head, createBSTNode(createInfo(t, 1), 1));
                (*sizeList) += 1;
            }
            (*charQnt)++;
        }
        fclose(arquivo);//fecha o arquivo
    }
    return head;//retorna o ponteiro para a cabeca da lista
}

/*Parametros: (vetor booleano, ponteiro para a posicao do vetor, vetor de saida codificado)
Retorno: (vazio)*/
void bitToBit(bool vet[], int size, int* posicao, unsigned char saida[]) {
    unsigned char A;//1 byte para comprimir o vetor booleano
    int posbyte = 0, posbit = 0;//variaveis para contar a posicao por byte e bit respectivamente
    for (int i = 0; i < size; i++) {
        posbyte = (*posicao) / 8;
        posbit = (*posicao) % 8;

        //salva e desloca o bit para a esquerda
        A = vet[i];
        A = A << (8 - posbit - 1);
        //atualiza e incrementa a posicao do vetor de saida
        saida[posbyte] = saida[posbyte] | A;
        (*posicao)++;//incrementa a posicao na tabela
    }
}

/*Parametros: (ponteiro para o arquivo compactado, nome do arquivo de saida)
Retorno: (vazio)*/
void unpack(FILE* arquivo, char* nomeSaida){
    int countRead, sizeTab,sizeTree, charQnt;
    fread(&charQnt, sizeof(long long), 1, arquivo);//leitura da quantidade total de caracteres presentes no arquivo de texto.
    fread(&sizeTab, sizeof(int), 1, arquivo);//leitura do tramanho da tabela.
    fread(&sizeTree, sizeof(int), 1, arquivo);//leitura do tamanho da arvore.
    //criacao e preenchimento da tabela
    tab* tabela = criaTabela(sizeTree,sizeTab);
    fread(tabela, sizeof(tab), sizeTab, arquivo);
    for(int i = 0; i < sizeTab; i++){
        int sizeSaida = (tabela[i].size)/8 + 1;
        unsigned char* saidaVet = (unsigned char*)calloc(sizeSaida, sizeof(unsigned char));
        fread(saidaVet, sizeof(unsigned char*),sizeSaida, arquivo);
        tabela[i].vet = intToBin(saidaVet,sizeSaida);
        free(saidaVet);
    }
    fread(&countRead, sizeof(int), 1, arquivo);//leitura do tamanho do vetor codificado
    unsigned char* buffer = (unsigned char*)calloc(countRead, sizeof(unsigned char));//alocacao do vetor codificado
    fread(buffer, sizeof(unsigned char), countRead, arquivo);//leitura do vetor codificado
    bool* binVet = intToBin(buffer, countRead);//Conversao para binario
    imprimeSaida(nomeSaida, binVet, countRead*8 ,tabela,sizeTab, charQnt);//decodifica o codigo binario utilizando a tabela e salva no arquivo de saida

    //liberacao da memoria alocada
    freeTabela(tabela,sizeTab);
    free(binVet);
    free(buffer);
    fclose(arquivo);//fechamento de arquivo
}

/*Parametros: (nome do arquivo de entrada, vetor com o arquivo codificado, tamanho do vetor codificado, tabela de codigos, tamanho da tabela
altura da arvore, quantidade total de caracteres no arquivo de texto)*/
void pack(char* nomeArquivo, unsigned char saida[], int sizeSaida, tab* tabela, int sizeTab, int sizeTree, long long charQnt){
    FILE* write_ptr = fopen(nomeArquivo, "wb");  //abertura do arquivo
    fwrite(&charQnt, sizeof(long long), 1, write_ptr);//escrita da quantidade maxima de caracteres contidos no texto
    fwrite(&sizeTab, sizeof(int), 1, write_ptr);//escrita do tamanho da tabela de codigos
    fwrite(&sizeTree, sizeof(int), 1, write_ptr);//escrita do altura da arvore
    //escrita da tabela e o codigo de caractere contido na mesma
    fwrite(tabela, sizeof(tab), sizeTab, write_ptr);
    for(int i = 0; i < sizeTab; i++){
        int sizeSaida = (tabela[i].size)/8 + 1;
        unsigned char* saidaVet = (unsigned char*)calloc(sizeSaida, sizeof(unsigned char));
        int posicao = 0;
        //compressao e escrita do codigo do caractere da tabela
        bitToBit(tabela[i].vet, tabela[i].size, &posicao,saidaVet);
        fwrite(saidaVet, sizeof(unsigned char*), sizeSaida, write_ptr);
        free(saidaVet);//Liberacao do vetor temporario
    }
    fwrite(&sizeSaida, sizeof(int), 1, write_ptr);//Escrita do tamanho do vetor de codificacao
    fwrite(saida, sizeof(unsigned char), sizeSaida, write_ptr);//escrita do vetor codificação
    fclose(write_ptr);//fechamento do arquivo
}

/*Parametros: (ponteiro para a cabeca da lista encadeada, tamanho da lista)
Retorno: (ponteiro para a raiz de arvore)*/
BSTNode* huffman(Node* lista, int size) {


    Node* x, * y;
    if(size > 1){//se a lista possuir mais de um elemento
        for (int i = 1; i < size; i++) {
            x = lista;
            y = lista->next;
            lista = y->next;


            BSTNode* conector = createBSTNode(NULL, getFreq(x) + getFreq(y));/*soma a frequencia dos dois primeiros nos da lista e utiliza a soma para
                                                                            como frequencia de um no de arvore*/

            //torna os ponteiros para no de arvore dos dois primeiros nos da lista filhos deste novo no de arvore
            conector->left = x->bstnode;//
            conector->right = y->bstnode;
            lista = insertList(lista, conector);//insere o novo elemento n lista
            //libera apenas a memoria alocada para o no de lista, mantendo o ponteiro para o no de arvore e suas informacoes
            free(x);
            free(y);
        }
    }
    BSTNode* retorno = lista->bstnode;//salva o poteiro para a raiz da arvore
    free(lista);//libera a memoria alocada no ultimo no da lista
    return retorno;
}

/*Parametros: (tabela de caracteres e seus codigos, caractere a ser buscado, tamanho da tabela)
Retorno: (posicao do caractere na tabela)*/
int searchTab(tab* tabela, char caractere, int tabSize){
    //Realiza a busca em toda tabela
    for(int i = 0; i < tabSize; i++){
        if(tabela[i].caractere == caractere) return i;//retorna a posicao do caractere na tabela se o mesmo for encontrado
    }
    return -1;//retorna -1 se o caractere nao for encontrado
}

/*Parametros: (ponteiro para a raiz da arvore, tabela, vetor para armazenar o caminho até o no folha, tamanho do caminho, posicao na tabela)
Retorno: (Vazio)*/
void writeTab(BSTNode* root, tab tabela[],bool vet[], int *size, int *posTab) {
    if (!root) {
        (*size)--;//atualiza o tamanho do codigo
        return;
    }

    if (root->left) {
        vet[*size] = 0;//0 pois o caminho vai para esquerda
        (*size)++;//atualiza o tamanho do caminho
        writeTab(root->left,tabela,vet, size, posTab);//realiza a chamada recursiva
    }

    if (root->right) {
        vet[*size] = 1;//1 pois o caminho vai para direita
        (*size)++;//atualiza o tamanho do caminho
        writeTab(root->right, tabela,vet,size,posTab);//realiza a chamada recursiva
    }

    if (root->info != NULL) {//no folha encontrado sinalizando o fim do caminho
        //salva o caminho na tabela
        for (int i = 0; i < *size; i++) {
            (tabela[*posTab]).vet[i] = vet[i];
        }
        //salva o caractere na tabela
        (tabela[*posTab]).caractere = root->info->caractere;
        (tabela[*posTab]).size = *size;
        (*posTab)++;//incrementa a posicao na tabela
    }
    (*size)--;//Decrementa o tamanho pois o fim da arvore foi alcançado
}


/*Parametros: (tabela de caminhos, nome do arquivo de entrada, nome do arquivo de saida, quantidade de bytes necessarios para a compressao, tamanho da tabela
, altura da arvore, quantidade maxima de caracteres no arquivo de entrada)
Retorno: (vazio)*/
void writeBin(tab tabela[], char* nomeEntrada, char* nomeSaida, long long countSizeOut, int sizeTab,int sizeTree, long long charQnt) {
    int posicao = 0;
    unsigned char* saida = (unsigned char*)calloc(countSizeOut, sizeof(unsigned char));//aloca o vetor para armazenar o texto comprimido

    FILE* arquivo = fopen(nomeEntrada,"r");//leitura do arquivo a ser comprimido
    if (!arquivo) printf("Arquivo nao existe");
    else {//caso o arquivo exista, cada caracter eh lido e comprimido
        fseek(arquivo, 0, SEEK_END);
        long int size = ftell(arquivo);
        fseek(arquivo, 0, SEEK_SET);
        while (ftell(arquivo) < size) {
            char t;
            fread(&t, sizeof(char), 1, arquivo);
            int pos = searchTab(tabela,t,sizeTab);
            bitToBit(tabela[pos].vet, tabela[pos].size, &posicao, saida);
        }
        fclose(arquivo);//fecha o arquivo de entrada
        pack(nomeSaida, saida, countSizeOut, tabela,sizeTab,sizeTree,charQnt);//compacta em um arquivo.cpt
    }
    free(saida);//libera a memoria utilizada
}

/*Parametros: (raiz da arvore, caminho de um caractere na arvore)
Retorno: (frequencia de um caractere na arvore)*/
int frequenciaNo(BSTNode* root, bool* vet){
    int i = 0;
    //realiza a busca pelo caractere utilizando o caminho passado
    while(root->left && root->right){
        if(vet[i] == 0) root = root->left;
        else root = root->right;
        i++;
    }
    return root->info->frequencia;//retorna a frequencia do caractere
}

/*Parametros: (tabela de caminhos, tamanho da tabela, raiz da arvore)
Retorno? (quantidade maxima de bytes necessarios para a compressao)*/
long long countSizeOut(tab* tabela, int sizeTab, BSTNode* root) {
    long long countSize = 0;
    for (int i = 0; i < sizeTab; i++) {
        countSize += tabela[i].size * frequenciaNo(root, tabela[i].vet);//soma frequencia de cada caractere vezes o tamanho de seu caminho na arvore
    }
    //calcula a quantidade de bytes necessarios para a compressao
    if(countSize%8 > 0){
        countSize = countSize/8;
        countSize++;
    }
    else countSize = countSize/8;
    return countSize;//retorna a quantidade de bytes
}
/*Parametros: (tabela de caminhos, tamanho da tabela)
Retorno: (vazio)*/
void freeTabela(tab* tabela, int sizeTab){
    //libera a memoria alocada em cada caminho
    for(int i = 0; i < sizeTab; i++) free(tabela[i].vet);
    free(tabela);//libera a memoria alocada na tabela
}



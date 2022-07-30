//Uarlley do Nascimento Amorim - 2018205346
//Ualaci dos Anjos Junior - 2017102015

#include "BST.h"

//--------------------------------------------------------------------------------------------------------
/*Parametros: (no de lista)
Retorno: (frequencia no caractere do no)*/
int getFreq(Node* node) {
    return node->bstnode->freq; //retorna a frequencia contida no no de arvore
}
//--------------------------------------------------------------------------------------------------------
/*Parametros: (no de arvore)
Retorno: (caractere presente no no)*/
char getBstChar(Node* node) {
    return node->bstnode->info->caractere; //retorna o caractere presente no no de arvore
}
//--------------------------------------------------------------------------------------------------------
/*Parametros: (no de arvore)
Retorno: (no de lista)*/
Node* createNode(BSTNode* bstnode) {
    Node* newNode = (Node*)malloc(sizeof(Node));//aloca o espaco para o no de lista
    if (newNode) { //se o no for alocado, seu ponteiro para o proximo elemento e definido como nulo
                    //e seu no para o no de arvore aponta para o no passado no parametro
        newNode->next = NULL;
        newNode->bstnode = bstnode;
    }
    return newNode;
}


//--------------------------------------------------------------------------------------------------------
//Parametros: (ponteiro para o inicio da lista, caractere a ser buscado)
//Retorno: (um inteiro representando o resultado da busca)
int searchList(Node* head, char caractere){
    while(head!=NULL){//Segue na lista ate encontrar o ultimo no
        //incrementa a frequencia do caractere e retorna 1 representando sucesso na busca
        if(head->bstnode->info->caractere == caractere) {
            (head->bstnode->info->frequencia)++;
            (head->bstnode->freq)++;
            return 1;
        }
        head = head->next;//segue avancando na lista
    }
    return 0;//retorna 0 pois a lista chegou ao fim e o caractere nao foi encontrado
}

//--------------------------------------------------------------------------------------------------------
//Parametros: (ponteiro para a cabeca da lista, ponteiro para um no de arvore)
//Retorno: (ponteiro para a cabeca da lista)
Node* insertList(Node* head, BSTNode* bstnode) {

    Node* newNode = createNode(bstnode);//cria o novo no a ser inserido na lista
    if (head == NULL) return newNode; //caso a lista esteja vazia o novo no sera a cabeça da lista

    Node* aux = head;//cria um ponteiro auxiliar para percorrer a lista

    if (getFreq(newNode) < getFreq(head)) { // o novo no sera a nova cabeca da lista se sua frequencia
                                            // for menor que a frequencia da cabeca atual
        newNode->next = head;
        head = newNode;
        return head;
    }
    //avanca na lista ate encontrar a posicacao onde o novo no deve ser inserido
    while (aux->next != NULL && getFreq(aux->next) < getFreq(newNode)) aux = aux->next;

    //realiza a insercao do novo no
    newNode->next = aux->next;
    aux->next = newNode;

    return head; //retorna um ponteiro para a cabeca lista
}

//--------------------------------------------------------------------------------------------------------
//Parametros: (caractere, frequencia do caractere)
//Retorno: (ponteiro para um elemento de informacao)
Info* createInfo(char caractere, int freq) {
    Info* info = (Info*)malloc(sizeof(Info));//aloca o espaco necessario
    if (info) {//Se o ponteiro for alocado, as informacoes sao preenchidas
        info->caractere = caractere;
        info->frequencia = freq;
    }
    return info;//retorna o ponteiro para o novo elemento de informacao
}


//--------------------------------------------------------------------------------------------------------
//Parametros: (ponteiro para o elemento de informacao, frequencia do caractere)
//Retorno: (ponteiro para um no de arvore)
BSTNode* createBSTNode(Info* info, int freq) {
    BSTNode* newnode = (BSTNode*)malloc(sizeof(BSTNode)); //Aloca o espaco necessário para o novo no
    if (newnode != NULL) {//se a alocacao for bem sucedida os campos sao preenchidos
        newnode->info = info;
        newnode->left = newnode->right = NULL;
        newnode->freq = freq;
    }
    return newnode; //retorna o no criado
}
//--------------------------------------------------------------------------------------------------------
//Parametros: (ponteiro para a raiz da arvore)
//Retorno: (altura da arvore)
int heightBST(BSTNode* root) {
    int lH = 0, rH = 0;//define variaveis para representar a altura esquerda e direta da arvore
    if (root == NULL) return 0;//a arvore nao existir sua altura e 0
    lH = 1 + heightBST(root->left);//calcula a altura da subarvore esquerda
    rH = 1 + heightBST(root->right);//calcula a altura da subarvore direita
    //retorna a maior entre as duas alturas
    if (rH > lH) return rH;
    else return lH;
}

/*Parametros: (raiz da arvore de Huffman)
Retorno: (vazio)*/
void imprimeCodHuffman(BSTNode* root){
    if(root == NULL) return;//se a arvore nao existir a funcao é finalziada

    imprimeCodHuffman(root->left);//realiza a chamada recursiva para a esquerda
    //se o campo de informacao existir, ou seja, ser um no folha, eh impresso o caracter e sua frequencia
    if(root->info){
        if(root->info->caractere == '\n') printf("Caractere: \\n - Frequencia: %d \n", root->info->frequencia);
        else if(root->info->caractere == ' ') printf("Caractere: espaco - Frequencia: %d \n", root->info->frequencia);
        else printf("Caractere: %c - %d - Frequencia: %d \n",root->info->caractere, root->info->caractere, root->info->frequencia);
    }
    //caso contrario, eh especificado que se trata de um no nao folha
    else printf("No não folha  - Frequencia: %d \n", root->freq);
    imprimeCodHuffman(root->right);//realiza a chamada recursiva para a direita
}

/*Parametros: (cabeca da lista de ocorrencias)
Retorno: (vazio)*/
void imprimeOcorrencias(Node* head){
    Node* aux = head;//cria um ponteiro auxiliar para percorrer a lista
    //percorre a lista ate o fim realizando a impressao dos caracteres e suas respectivas frequencias
    while(aux){
        if(getBstChar(aux) == '\n') printf("Caractere: \\n - Ocorrencia(s): %d\n",aux->bstnode->info->frequencia);
        else if (getBstChar(aux) == ' ') printf("Caractere: espaco - Ocorrencia(s): %d\n",aux->bstnode->info->frequencia);
        else printf("Caractere: %c - Ocorrencia(s): %d\n", getBstChar(aux),aux->bstnode->info->frequencia);
        aux = aux->next;//segue na lista
    }
}

/*Parametros: (raiz da arvore de Huffman)
Retorno: (vazio)*/
void destroyBST(BSTNode* root){
    if(root==NULL) return;//caso a chave atual da recursão não exista, não há mais nada a destruir.
    destroyBST(root->right);//Chamada recursiva para o filho a direita do nó atual.
    destroyBST(root->left);//Chamada recursiva para o filho a esquerda do nó atual.
    if(root->info) free(root->info);//Chama a função que libera a mémoria alocada em um nó
    free(root);
}


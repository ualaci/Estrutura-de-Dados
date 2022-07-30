//Uálaci dos Anjos Júnior
//Uarlley Nascimento Amorim
//disciplina de estrutura de dados 2

/*Implementação das funções da AVL*/
#include "AVL.h" /*Inclusão das estruturas e cabeçalho das funções
                 necessárias para implementação da AVL*/
//--------------------------------------------------------------------------------------------------------
//Função que calcula e retorna o maior entre dois inteiros
int max(int a,int b){
    //Compara e retorna o maior valor entre a e b
    if(a>b) return a;
    return b;
}

//--------------------------------------------------------------------------------------------------------
//Função que calcula e retorna o fator de balanceamento de um nó
int getBalance(AVLNode* root){
    //Retorna 0 se o nó não existir
    if(root==NULL) return 0;
    //Retorna a altura do filho a esquerda menos a altura do filho a direita
    return height(root->left) - height(root->right);
}

//---------------------------------------------------------------------------------------------------------
//Função que cria e retorna um elemento de informação genérico
AVLNode* createAVLNode(void* info){
    AVLNode* newnode; //Declaração do novo nó
    if(info!=NULL){ //Verifica se o elemento de informação passado como parâmetro existe.
        newnode = (AVLNode *)malloc(sizeof(AVLNode)); //Aloca a mémoria necessária para criação de um nó.
        if(newnode!=NULL){
            /*Se a alocação for bem sucedida, define o campo de informação, a altura como 1,
            e os ponteiros para esquerda e direita como NULL.*/
            newnode->info = info;
            newnode->left = newnode->right = NULL;
            newnode->height = 1;
        }
    }
    return newnode; //Retorna o novo nó.
}

//--------------------------------------------------------------------------------------------------------
//Função que retorna o filho à direita de um nó
AVLNode* rightAVL(AVLNode* root){
    //Retorna um ponteiro para o filho a direita se o nó existir e NULL caso contrário.
    if(root) return root->right;
    else return NULL;
}

//--------------------------------------------------------------------------------------------------------
//Função que retorna o filho à esquerda de um nó
AVLNode* leftAVL(AVLNode* root){
    //Retorna um ponteiro para o filho a esquerda se o nó existir e NULL caso contrário.
    if(root) return root->left;
    else return NULL;
}
//--------------------------------------------------------------------------------------------------------
//Função que retorna a altura de um nó específico
int height(AVLNode* root){
    //Retorna 0 se o nó não existir e sua respectiva altura caso contrário.
    if(root == NULL) return 0;
    return root->height;
}
//--------------------------------------------------------------------------------------------------------
//Função que calcula e retorna a altura de uma arvore/subarvore
int heightAVL(AVLNode* root){
    int lH = 0,rH = 0; /*Define duas variaveis, lH representa a altura.
                        a esquerda, e rH a altura a direita*/
    if(root==NULL) return 0; //Se o nó não existir sua altura é 0.

    /*Calcula as alturas da esquerda e direita da arvore/subarvore utilizando chamadas recursivas.*/
    lH = 1 + heightAVL(leftAVL(root));
    rH = 1 + heightAVL(rightAVL(root));

    //Identifica e retorna a maior das alturas.
    if(rH>lH) return rH;
    else return lH;
}


//--------------------------------------------------------------------------------------------------------
/*Função que imprime um elemento de informação contido em nó da árvore.
Parâmentros: (raiz da árvore, função de impressão de um elemento de informação)*/
void printAVL(AVLNode* root, void (*imprime)(void* info)){
    if(root==NULL) return; //Sai da função se o fim da arvore/subarvore for alcançado.
    printAVL(root->left,imprime);//Faz a chamada recursiva para a esquerda.
    imprime(root->info); //Utiliza a função passada com parâmetro para imprimir o elemento de informação.
    printAVL(root->right,imprime);//Realiza a chamada recursiva a direita, mantendo a impressão ordenada.

}

//--------------------------------------------------------------------------------------------------------
/*Função que retorna um nó que contém a chave buscada se o mesmo existir na arvore e NULL caso contrário.
Parâmetros : (Raiz da arvore, chave, função de comparação entre uma chave e um elemento de informação)*/
AVLNode* searchAVL(AVLNode* root, void* key, int (*compare)(void* a, void* b)){
    if(root==NULL || compare(key,root->info)==0){
        return root; /*Retorna o nó atual se o mesmo não
                       existir ou seu elemento de informação for igual ao buscado*/
    }
    /*Realiza a chamada recursiva para a direita se a chave buscada for
    maior que o elemento de informação do nó atual e para esquerda caso contrário*/
    if(compare(key,root->info)<0) return searchAVL(leftAVL(root),key,compare);
    else return searchAVL(rightAVL(root),key,compare);
}

//--------------------------------------------------------------------------------------------------------
//Função que busca ná arvore/subarvore o maior elemento
AVLNode* findLargerstElement(AVLNode* root){
    if(rightAVL(root)==NULL) return root; //Retorna o nó atual se seu filho à direita não existir
    else return findLargerstElement(rightAVL(root)); /*Realiza a chamada recursiva para o
                                                        filho à direita do nó atual*/
}

//--------------------------------------------------------------------------------------------------------
/*Função que destroi uma arvore, liberando toda mémória utilizada pela mesma.
Parâmetros: (raiz da arvore, função de liberação de um elemento de informação)*/
void destroyAVL(AVLNode* root, void (*freeInfo)(void* info)){
    if(root==NULL) return;//caso a chave atual da recursão não existe, não há mais nada a destruir, portanto, retorna NULL.
    destroyAVL(rightAVL(root), freeInfo);//Chamada recursiva para o filho a direita da chave atual.
    destroyAVL(leftAVL(root), freeInfo);//Chamada recursiva para o filho a esquerda da chave atual.
    freeInfo(root->info);//Chama a função que limpa o elemento de informação da memória.
    free(root->info);//Limpa o conteúdo do ponteiro info.
    free(root);//Limpa o conteúdo do ponteiro root.
}


//--------------------------------------------------------------------------------------------------------
//Função que realiza rotação simples à direita.
void rotationLL(AVLNode **root){
    AVLNode* aux;//Cria ponteiro que apontará para Pivô da rotação.
    aux = leftAVL(*root);//Define o pivô como o filho a direita da raiz da subárvore.
    (*root)->left = aux->right;//Realiza a rotação.
    aux->right = *root;

    (*root)->height = max(height((*root)->left), height((*root)->right))+1;//Ajusta o valor da altura como a altura máxima entre o filho a direita e o a esquerda, +1.
    aux->height = max(height(aux->left), height(aux->right))+1;
    (*root) = aux;//O pivô agora é a raiz da subárvore.
}


//--------------------------------------------------------------------------------------------------------
//Função que realiza rotação simples à esquerda.
void rotationRR(AVLNode **root){
    AVLNode* aux;//Cria ponteiro que apontará para Pivô da rotação.
    aux = rightAVL(*root);//Define o pivô como o filho a direita da raiz da subárvore.
    (*root)->right = aux->left;//Realiza a rotação.
    aux->left = *root;

    (*root)->height = max(height((*root)->left), height((*root)->right))+1;//Ajusta o valor da altura como a altura máxima entre o filho a direita e o a esquerda, +1.
    aux->height = max(height(aux->left), height(aux->right))+1;
    (*root) = aux;//O pivô agora é a raiz da subárvore.
}


//--------------------------------------------------------------------------------------------------------
/*Função que realiza rotação dupla a direita.
//Essa rotação é a junção de duas outras, portanto a função simplesmente chama outras duas rotações.*/
void rotationLR(AVLNode **root){
    rotationRR(&(*root)->left);//Chama a rotação simples a esquerda para o filho a esquerda da raiz da subárvore.
    rotationLL(root);//Por fim, chama a rotação simples a direita para a raiz da subárvore após a rotação simples a esquerda.
}


//--------------------------------------------------------------------------------------------------------
/*Função que realiza rotação dupla a esquerda.
*///Essa rotação é a junção de duas outras, portanto a função simplesmente chama outras duas rotações.
void rotationRL(AVLNode **root){
    rotationLL(&(*root)->right);//Chama a rotação simples a direita para o filho a direita da raiz da subárvore.
    rotationRR(root);//Por fim, chama a rotação simples a esquerda para a raiz da subárvore após a rotação simples a direita.
}

//--------------------------------------------------------------------------------------------------------
/*Função que realiza o balanceamento da chave caso haja algum desbalanceamento na subárvore.
Esta função é utilizada para a re-balancear uma após uma inserção ou remoção*/
void BalanceAVL(AVLNode** root){
    if(getBalance(*root)==2){/*Verififica se á um desbalanceamento a esquerda, e
                                realiza uma rotação simples a direita ou uma rotação dupla a direita
                                dependendo do fator de balanceamento do filho a esquerda do nó passado*/
        if((*root)->left!=NULL && getBalance((*root)->left) <=-1) rotationLR(root);
        else rotationLL(root);
    }
    else if(getBalance(*root)==-2){/*Verififica se á um desbalanceamento a direita, e
                                realiza uma rotação simples a esquerda ou uma rotação dupla a esquerda
                                dependendo do fator de balanceamento do filho a direita do nó passado*/
        if((*root)->right!=NULL && getBalance((*root)->right)>=1) rotationRL(root);//Chama a rotação adequada para a situação se necessário.
        else rotationRR(root);
    }
    return;
}
//--------------------------------------------------------------------------------------------------------
/*Função que insere um elemento em uma AVL. Retorna 1 se a inserção foi realizada e 0 caso contrário.
Parâmetros: (ponteiro de ponteiro para a raiz da arvore, novo nó, função de comparaçaõ
            entre dois elementos informação)*/
int insertAVL(AVLNode **root,void* key, int (*comp)(void *a, void *b)){
    int s = 1;//Variavel utilizada para definir se a inserção foi realiza ou não.
    if(*root==NULL) {/*Se o filho de um nó folha for alcançado, realizar a inserção neste nó
                        e retornar 1.*/
        *root =  createAVLNode(key);
        return 1;
    }
    /*Utiliza a função de comparação e realiza as chamadas recursivas para identificar onde o novo nó deverá ser inserido.
    Se a chave do novo nó for igual a chave de algum nó existente na arvore, a inserção
    não será realizada, e, por consequência, será retornado 0.*/
    else if(comp(key,(*root)->info) < 0) s = insertAVL(&(*root)->left,key,comp);
    else if (comp(key,(*root)->info) > 0)  s = insertAVL(&(*root)->right,key,comp);
    else return 0;
    /*Recalcula a altura e avalia o fator de balanceamento dos nós afetados pela inserção.
    Se existir algum nó desbalanceado, é utilizada a função de balanceamento para realizar as
    rotações necessárias.*/
    if(*root && s){
        (*root)->height = 1 + max(height((*root)->left),height((*root)->right));
        if(abs(getBalance(*root))==2) BalanceAVL(root);
    }
    //Retorna s para identificar se a inserção foi ou não realizada.
    return s;
}
//--------------------------------------------------------------------------------------------------------
/*Função que deleta um elemento de uma AVL. Retorna 1 se a deleção foi realiza e 0 caso contrário.
Parâmetros: (ponteiro de ponteiro para a raiz da árvore, chave, função de comparação entre uma chave e
            um elemento de informação, função que libera a memória utilizada por um elemento de informação
            função que copia os dados de um elemento de informação para outro)*/
int deleteAVL(AVLNode **root, void* key, int (*comp)(void* a, void* b), void (*freeInfo)(void* info), void (*copy)(void* a,void* b)){
    int s = 1; //Variável ultilizada para definir se a remoção foi ou não realizada.

    if(*root==NULL) return 0;//Retorna 0 se o final da árvore for alcançada.
    /*Utiliza a função de comparação e realiza as chamadas recursivas
    para identificar onde o nó com a chave passada está posicionado na árvore*/
    if(comp(key,(*root)->info) > 0)  s = deleteAVL(&(*root)->right,key,comp,freeInfo,copy);
    else if(comp(key,(*root)->info) < 0)   s = deleteAVL(&(*root)->left,key,comp,freeInfo,copy);
    else{ //Caso o nó for encontrado.

        AVLNode* temp;//Cria um nó temporário.
        /*Verifica se o filho a esquerda do nó encontrado é NULL. Se sim, o filho a direita assume a posição
        do nó encontrado e o mesmo é deletado e sua memória é liberada. O elemento de informação é deletado
        e sua mémoria alocada de ser liberada utilizando a função passada como parâmetro.*/
        if((*root)->left==NULL){
            temp = (*root)->right;
            freeInfo((*root)->info);
            free((*root)->info);
            free(*root);
            *root = temp;
        }
        /*Verifica se o filho a direita do nó encontrado é NULL. Se sim, o filho a esquerda assume a
        posição do nó encontrado e o mesmo é deletado e sua memória é liberada. O elemento de informação
        é deletado e sua mémoria alocada deve ser liberada utilizando a função passada como parâmetro.*/
        else if((*root)->right==NULL){
            temp = (*root)->left;
            freeInfo((*root)->info);
            free((*root)->info);
            free(*root);
            *root = temp;
        }
        /*Se o nó contrado possuir tanto um filho a direita como um filho a esquerda, o maior elemento
        a esquerda desse nó será buscado e seu endereço será salvo em temp, e, então, o elemento de informação
        do nó salvo por temp será copiado no nó encontrado através da função de cópia passada como parâmetro. Após
        isso, será realizada uma chamada recursiva para remover o nó salvo por temp, que como é um nó folha,
        acabará caíndo no primeiro caso básico.*/
        else{
            temp = findLargerstElement((*root)->left);
            copy((*root)->info,temp->info);
            s = deleteAVL(&(*root)->left,(*root)->info,comp,freeInfo,copy);
        }
    }
    /*Recalcula a altura e avalia o fator de balanceamento dos nós afetados pela remoção.
    Se existir algum nó desbalanceado, é utilizada a função de balanceamento para realizar as
    rotações necessárias.*/
    if(*root && s){
        (*root)->height = 1 + max(height((*root)->left), height((*root)->right));
        if(abs(getBalance(*root))==2) BalanceAVL(root);
    }
    return s; //Retorna s para definir se a remoção foi ou não realizada.
}


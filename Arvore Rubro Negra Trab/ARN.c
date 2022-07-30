//Uarlley do Nascimento Amorim
//Ualaci dos Anjos Junior

#include "ARN.h"

ARNNode* externo;
//--------------------------------------------------------------------------------------------------------

//funcao que copia as informacoes do no a2 para o no a1
void copy(ARNNode* a1, ARNNode* a2) {
    //copia das variaveis de tipo primitivo
    a1->info->key->id = a2->info->key->id;
    a1->info->key->ano = a2->info->key->ano;
    //copia das variaveis do tipo string
    strcpy(a1->info->key->autor,a2->info->key->autor);
    strcpy(a1->info->key->palavraChave,a2->info->key->palavraChave);
    strcpy(a1->info->key->revista,a2->info->key->revista);
    strcpy(a1->info->key->titulo,a2->info->key->titulo);
    strcpy(a1->info->key->DOI,a2->info->key->DOI);
    return;
}


//--------------------------------------------------------------------------------------------------------
//Funcao que retorna o id de um no recebido como parametro
int getID(ARNNode* root) {
    return root->info->key->id;
}

//--------------------------------------------------------------------------------------------------------
//Funcao que retorna a cor de um no recebido como parametro
bool getColor(ARNNode* root) {
    return root->color;
}

//--------------------------------------------------------------------------------------------------------
//funcao que retorna o filho a esquerda de um no passado como parametro
ARNNode* leftNode(ARNNode* root) {
    return root->left;
}

//--------------------------------------------------------------------------------------------------------
//funcao que retorna o filho a direita de um no passado como parametro
ARNNode* rightNode(ARNNode* root) {
    return root->right;
}

//--------------------------------------------------------------------------------------------------------
//funcao que recebe um ponteiro para no, cria um artigo e faz esse ponteiro apontar para ele
artigo* criaArtigo(int id, int ano, char* autor, char* titulo, char* revista, char* DOI, char* palavraChave) {
    artigo* newKey = (artigo*)malloc(sizeof(artigo)); //Aloca um espaco de memoria para o artigo
    if (newKey) {//caso a alocacao tenha sido bem sucedida, copia as informacoes recebidas como parametro para os campos respectivos no artigo criado
        newKey->ano = ano;
        newKey->id = id;
        strcpy(newKey->autor, autor);
        strcpy(newKey->titulo, titulo);
        strcpy(newKey->revista, revista);
        strcpy(newKey->DOI, DOI);
        strcpy(newKey->palavraChave, palavraChave);
    }
    return newKey;//retorna o ponteiro com o artigo alocado com as informacoes adequadas.
}

//--------------------------------------------------------------------------------------------------------
/*cria um elemento de informacao de um artigo , faz o ponteiro recebido como
parametro apontar para esse artigo e o retorna
Parametros: um ponteiro para um artigo
Retorno: um ponteiro para um elemento de informacao*/
Info* createInfo(artigo* key) {
    Info* newInfo = (Info*)malloc(sizeof(Info)); //Aloca espaco de memoria para o elemento de informacao
    if (newInfo) newInfo->key = key; /*caso a alocacao tenha sido bem sucedida, faz o ponteiro da chave
                                      do no apontar para a chave recebida como parametro*/
    return newInfo; //retorna o ponteiro que aponta para o artigo recem criado
}

//--------------------------------------------------------------------------------------------------------
//cria um novo no , associa um artigo a esse no e retorna o no
ARNNode* createNode(artigo* key) {
    ARNNode* newNode = (ARNNode*)calloc(1, sizeof(ARNNode)); /*aloca o espaco de memoria necessario para o
                                                                novo no*/
    if (newNode) {/*caso  a alocacao tenha sido bem sucedida
    faz os filhos a esquerda e a direita serem nos sentinelas, define a cor do no para vermelha
    e faz o ponteiro de informacao apontar para um artigo que sera criado recebendo a chave key como parametro*/
        newNode->right = newNode->left = newNode->father = externo;
        newNode->info = createInfo(key);
        newNode->color = red;
    }
    //retorna o no recem criado
    return newNode;
}

//--------------------------------------------------------------------------------------------------------
/*Funcao responsavel por imprimir um artigo com a cor da fonte igual a cor do seu respectivo no
Parametros: um ponteiro para um nó
Nao possui retorno*/
void imprimeArtigo(ARNNode* node){
    if(node == externo) return;//caso o no seja externo, nada sera impresso.
    printf("-----------------------------------\n");
    if(node->color == red) printf("\033[0;31m");/*Altera a cor de impressao para
                                                 vermelho se o no for de cor vemelha*/
    else printf("\033[0m");//Altera a cor de impressao para preto se o no for de cor preta
    //Realiza a impressao dos dados do artigo

    printf("\nID: %d\n",node->info->key->id);
    printf("Ano: %d\n",node->info->key->ano);
    printf("Autor: %s\n", node->info->key->autor);
    printf("Titulo: %s\n", node->info->key->titulo);
    printf("Revista: %s\n",node->info->key->revista);
    printf("DOI: %s\n",node->info->key->DOI);
    printf("Palavra-chave: %s\n\n",node->info->key->palavraChave);
    printf("\033[0m");//Altera a cor de impressao para preto
    printf("----------------------------------\n");
}

//--------------------------------------------------------------------------------------------------------
/*Funcao responsavel por imprimir uma arvore/subarvore de forma ordenada (caminho em-ordem)
Parametros: um ponteiro para a raiz da arvore/subarvore
Retorno: vazio possui retorno*/
void imprimeARN(ARNNode* root) {
    if (!root) return; //Caso o no nao exista, a funcao eh finalizada
    imprimeARN(root->left);//Realiza a impressão da subarvore esquerda
    imprimeArtigo(root);//Realiza a impressao
    imprimeARN(root->right);//Realiza a impressao da subarvore direita
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por buscar um no na arvore
//Parametros: Um ponteiro para a raiz da arvore/subarvore
//Retorno: no buscado ou externo caso nao seja encontrado o no
ARNNode* searchNode(ARNNode* root, int id) {
    if (root == externo || root->info->key->id == id) return root; /*caso o no atual for sentinela ou for
                                                                    igual ao no buscado, esse no eh retornado*/
    if (root->info->key->id > id) return searchNode(root->left, id);/*se no buscado for menor que o no
                                                                    atual, a funcao eh chamada recursivamente
                                                                    com o filho a esquerda do no atual como
                                                                    parametro*/
    else return searchNode(root->right, id);/*se o no buscado for maior que o no atual, a funcao eh
                                            chamada recursivamente com o filho a direita do no
                                            atual como parametro*/
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por fazer uma rotacao a direita num no
//Parametros: ponteiro de ponteiro para a raiz da arvore, um ponteiro para um no.
//Retorno: vazio.
void rightrotate(ARNNode** root, ARNNode* node) {
    ARNNode* aux = node->left;//ponteiro aux aponta para o filho a esquerda de node.
    node->left = aux->right;//ponteiro do filho a esquerda de node, passa a apontar para o filho a direita de aux.

    /*caso node possua um filho a esquerda, o pai desde filho passa a ser node*/
    if (node->left != externo) node->left->father = node;
    aux->father = node->father;//pai do filho a esquerda do no node aponta para o pai de node.

    /*caso o pai de node seja um no sentinela, a raiz da arvore passa a ser aux*/
    if (node->father == externo) *root = aux;

    /*caso a condicao acima nao ocorra, se node for pai de seu filho a esquerda, o ponteiro para o filho
    a esquerda do pai de node ira apontar para o endereco no qual aux aponta*/
    else if (node == node->father->left) node->father->left = aux;

    /*caso nenhuma das condicoes anteriores ocorra, o ponteiro para o filho a direita, do pai de
    node, ira apontar para o endereco no qual aux aponta*/
    else  node->father->right = aux;
    aux->right = node; //o ponteiro para o filho a direita do no que aux aponta ira apontar para node.
    node->father = aux;//o ponteiro para o pai, de node, ira apontar para o no que aux aponta.
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por fazer uma rotacao a esquerda num no
//Parametros: ponteiro de ponteiro para a raiz da arvore, um ponteiro para um no.
//Retorno: vazio.
void leftrotate(ARNNode** root, ARNNode* node) {
    ARNNode* aux = node->right;//ponteiro aux aponta para o filho a direita do no node.
    node->right = aux->left;/*ponteiro do filho a direita, de node, passa a apontar para o
                            filho a esquerda de aux*/
    /*caso o filho a direita de node seja diferente de externo, o ponteiro para o pai, desse filho,
    ira apontar para o no node recebido como parametro*/
    if (node->right != externo) node->right->father = node;

    aux->father = node->father;//ponteiro para o pai, de aux, ira apontar para o pai de node
    /*caso o pai de node seja um no sentinela, o ponteiro da raiz ira apontar para o endereco no
    qual left aponta*/

    if (node->father == externo) *root = aux;
    /*caso a condicao acima nao ocorra, se node for pai de seu filho a esquerda, o ponteiro para o filho
    a esquerda do pai de node ira apontar para o no que aux aponta*/

    else if (node == node->father->left) node->father->left = aux;

    /*caso nenhuma das condicoes anteriores ocorra, o ponteiro para o filho a direita, do pai de
    node, ira apontar para o endereco no qual aux aponta*/
    else node->father->right = aux;
    aux->left = node;//o ponteiro para o filho a esquerda do no que aux aponta ira apontar para node.
    node->father = aux;//o ponteiro para o pai, de node, ira apontar para o no que aux aponta.
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por fazer o balanceamento da arvore apos uma insercao.
//Parametros: ponteiro de ponteiro para a raiz da arvore, um ponteiro para um no.
//Retorno: vazio.
void insereFixUp(ARNNode** root, ARNNode* newNode) {
    ARNNode* parent_pt = externo;//cria ponteiro auxiliar que representa o pai de newNode, apontando para o no externo
    ARNNode* grand_parent_pt = externo;//cria outro ponteiro auxiliar que representa o avo de newNode, apontando para externo

    //Caso newNode for diferente de root, e a cor de newnode for vermelha, e a cor do pai de newNode tambem for vermelha:
    while ((newNode != *root) && (newNode->color != black) && (newNode->father->color == red)){
        parent_pt = newNode->father;//ponteiro parent_pt aponta para o pai de newNode.
        grand_parent_pt = newNode->father->father;//ponteiro grand_parent_pt aponta para o avo de newNode.

        if (parent_pt == grand_parent_pt->left) //se o pai de newNode for filho a esquerda de seu pai:
        {

            ARNNode* uncle_pt = grand_parent_pt->right;//cria um ponteiro auxiliar que representa o tio de newNode, e o aponta para o filho a direita do avo de newNode.

            if (uncle_pt != externo && uncle_pt->color == red)//se o tio de newNode nao for sentinela, e sua cor for vermelha:
            {
                grand_parent_pt->color = red;//a cor do avo de newNode passa a ser vermelha.
                parent_pt->color = black;//a cor do pai de newNode passa a ser preta.
                uncle_pt->color = black;//a cor do tio de newNode passa a ser preta.
                newNode = grand_parent_pt;//newNode aponta para o no que o ponteiro grant_parent_pt aponta, que eh seu avo.
            }

            else {//se o tio de newNode for sentinela ou se sua cor for preta:
                if (newNode == parent_pt->right) {// se newNode for filho a direita de seu pai:
                    leftrotate(root, parent_pt);//faz uma rotacao a esquerda no pai de newNode.
                    newNode = parent_pt;//apos a rotacao, faz newNode apontar para o no que parent_pt aponta.
                    parent_pt = newNode->father;//parent_pt aponta para o pai de newNode, que pode ter mudado devido a rotacao.
                }

                rightrotate(root, grand_parent_pt); //faz uma rotacao a direita no noh que grand_parent_pt aponta.
                int t = parent_pt->color;//cria uma variavel para armazenar a cor do no que paren_pt aponta.
                parent_pt->color = grand_parent_pt->color;//define a cor do no que parent_pt aponta como sendo a cor do no que grant_parent_pt aponta.
                grand_parent_pt->color = t;//a cor do no que grant_parent_pt aponta passa a ser a antiga cor do no que parent_pt aponta que esta armazenada em t.
                newNode = parent_pt;//newNode aponta para o conteudo de parent_pt.
            }
        }

        else {//se o pai de newNode nao for filho a esquerda de seu pai:
            ARNNode* uncle_pt = grand_parent_pt->left;

            if ((uncle_pt != externo) && (uncle_pt->color == red))//se o tio de newNode nao for sentinela, e sua cor for vermelha:
            {
                grand_parent_pt->color = red;//a cor do avo de newNode passa a ser vermelha.
                parent_pt->color = black;//a cor do pai de newNode passa a ser preta.
                uncle_pt->color = black;//a cor do tio de newNode passa a ser preta.
                newNode = grand_parent_pt;//newNode aponta para o no que o ponteiro grant_parent_pt aponta, que eh seu avo.
            }
            else {//se o tio de newNode for sentinela ou se sua cor for preta:
                if (newNode == parent_pt->left) {// se newNode for filho a esquerda de seu pai:
                    rightrotate(root, parent_pt);//faz uma rotacao a direita no pai de newNode.
                    newNode = parent_pt;//apos a rotacao, faz newNode apontar para o no que parent_pt aponta.
                    parent_pt = newNode->father;//parent_pt aponta para o pai de newNode, que pode ter mudado devido a rotacao.
                }

                leftrotate(root, grand_parent_pt);//faz uma rotacao a direita no noh que grand_parent_pt aponta.
                int t = parent_pt->color;//cria uma variavel para armazenar a cor do no que paren_pt aponta.
                parent_pt->color = grand_parent_pt->color;//define a cor do no que parent_pt aponta como sendo a cor do no que grant_parent_pt aponta.
                grand_parent_pt->color = t;//a cor do no que grant_parent_pt aponta passa a ser a antiga cor do no que parent_pt aponta que esta armazenada em t.
                newNode = parent_pt;//newNode aponta para o conteudo de parent_pt.
            }
        }
    }

    (*root)->color = black;//define a cor da raiz como preta.
    //fim da funcao
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por fazer fazer o pai de um no, tambem ser pai de outro no, ambos passados como parametro.
//Parametros: Raiz da arvore, dois ponteiros para no.
//Retorno: vazio.
void transferePai(ARNNode** root, ARNNode* u, ARNNode* v) { //Transfere o pai do no u para o no v.
    if (u->father == externo)  *root = v; //Caso o pai de u seja externo, o ponteiro da raiz aponta para v.
    else {//do contrario:
        if (u == u->father->left) u->father->left = v; //do contrário, caso o u seja igual ao filho a esquerda de seu pai, o filho a esquerda de seu pai agora passa a ser v.
        else u->father->right = v; //por fim, do contrário, o filho a direita do pai de u passa a ser v.
    }
    v->father = u->father; // o pai de v aponta para o pai de u.
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por fazer o balanceamento de uma arvore apos a remocao de um no
//Parametros: ponteiro de ponreiro para a raiz da arvore, ponteiro para um no da arvore.
//Retorno: vazio.
void removeFixUp(ARNNode** root, ARNNode* x) {
    ARNNode* w;//declaracao de um ponteiro auxiliar do tipo no, chamado w.
    while (x != *root && x->color == black) {//se x nao apontar para a raiz , e caso o no que x aponta tiver cor preta:
        if (x == x->father->left) {//se x for filho a esquerda de seu pai:
            w = x->father->right;//w aponta para o filho a direita do pai de x.

            //caso 1:
            if (w->color == red) {//caso a cor de w for vermelha:
                w->color = black; //troca a cor de w para preta.
                x->father->color = red; //troca a cor do pai de x para vermelho.
                leftrotate(root, x->father); //realiza uma rotacao esquerda passando a raiz, e o pai de x como parametro.
                w = x->father->right; //apos a rotacao, w aponta para o filho a direita de x.
            }

            //caso 2:
            if (w->left->color == black && w->right->color == black) {//se a cor do filho a esquerda e direita forem preto:
                w->color = red; //troca a cor de w para vermelho.
                x = x->father; //x aponta para o pai dele mesmo.
            }

            //caso 3:
            else {
                
                if (w->right->color == black) {//se a cor do filho a direita de w for preto:
                    w->left->color = black; //troca a cor do filho a esquerda de w para preto.
                    w->color = red; // troca a cor de w para vermelho.
                    rightrotate(root, w); // realiza rotacao a direita passando a raiz da arvore, e w como parametro.
                    w = x->father->right; // apos a rotacao, w aponta para o pai o filho a direita do pai de x.
                }
                w->color = x->father->color; //iguala a cor de w para a cor do pai de x.
                x->father->color = black; //troca a cor do pai de x para preto.
                w->right->color = black; //troca a cor do filho a direita de w para preto.
                leftrotate(root, x->father);//realiza uma rotacao a esquerda passando a raiz da arvore, e o pai de x como parametro.
                x = *root;//x passa a apontar para a raiz da arvore
            }
        }

        else {//se x nao for filho a esquerda de seu pai:
            w = x->father->left;//w aponta para do filho a direita do pai de x.

            //caso 1:
            if (w->color == red) {
                w->color = black; //caso a cor de w for preta:
                x->father->color = red; //troca a cor do pai de x para vermelho.
                rightrotate(root, x->father); //realiza uma rotacao a direita passando a raiz, e o pai de x como parametro.
                w = x->father->left; //apos a rotacao, w aponta para o filho a esquerda de x.
            }

            if (w->left->color == black && w->right->color == black) {//se a cor do filho a esquerda e direita forem preto:
                w->color = red; //troca a cor de w para vermelho.
                x = x->father; //x aponta para o pai dele mesmo.
            }

            else {
                if (w->left->color == black) {//se a cor do filho a esquerda de w for preto:
                    w->right->color = black; //troca a cor do filho a direita de w para preto.
                    w->color = red; // troca a cor de w para vermelho.
                    leftrotate(root, w); // realiza rotacao a esquerda passando a raiz da arvore, e w como parametro.
                    w = x->father->left; // apos a rotacao, w aponta para o pai do filho a esquerda do pai de x.
                }

                w->color = x->father->color; //iguala a cor de w para a cor do pai de x.
                x->father->color = black; //troca a cor do pai de x para preto.
                w->left->color = black; //troca a cor do filho a esquerda de w para preto.
                rightrotate(root, x->father); //realiza uma rotacao a direita passando a raiz da arvore, e o pai de x como parametro.
                x = *root; //x passa a apontar para a raiz da arvore
            }
        }
    }
    x->color = black;//troca a cor de x para preto.
    //fim da funcao
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por buscar o sucessor de um no
//Parametros: ponteiro para um no, que representa o filho a direita do noh no qual se deseja buscar o sucessor.
//Retorno: temp, que representa o sucessor.
ARNNode* successor(ARNNode* node) {
    ARNNode* temp = node;//cria um ponteiro do tipo no chamado temp, apontando para o no node passado como parametro.
    while (temp->left != externo) temp = temp->left;//enquanto o filho a esquerda de temp nao for um no externo, temp vai apontando para seu filho a esquerda num loop
    return temp;// retorna o sucessor.
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por remover um no.
//Parametros: ponteiro de ponteiro para a raiz da arvore, ponteiro para um no, que representa o no a ser removido.
//Retorno: toBeRemoved, no a ser removido encontrado na arvore.
ARNNode* removeARN(ARNNode** root, int id){

    ARNNode* toBeRemoved = searchNode(*root,id);//cria um ponteiro para no, e o aponta para o no a ser removido. Caso nao seja encontrado, esse ponteiro ira aponta para o no sentinela.
    if(toBeRemoved == externo) return externo;//se toBeRemoved apontar para o no sentinela, retorna externo. (condicao de parada da recursao).

    ARNNode* x, * y;//declara dois ponteiros auxiliares do tipo no, x e y.
    int yColor = black; // declara uma variavel auxiliar para armazenar a cor de y e a define como preto.

    y = toBeRemoved;//y aponta para o no que toBeRemoved aponta.
    yColor = y->color;//variavel yColor recebe a cor de y.

    if (toBeRemoved->left == externo) {//se o filho a esquerda de toBeRemoved for o no sentinela:
        x = toBeRemoved->right;//x aponta para o filho a direita de toBeRemoved
        transferePai(root, toBeRemoved, toBeRemoved->right);//torna o pai de toBeRemoved, como o pai do filho a direita de toBeRemoved.
    }

    else {//se o filho a esquerda de toBeRemoved nao for no sentinela:
        if (toBeRemoved->right == externo) {//se o filho a direita de toBeRemoved for no sentinela:
            x = toBeRemoved->left;//x aponta para o filho a esquerda de toBeRemoved.
            transferePai(root, toBeRemoved, toBeRemoved->left);//torna o pai de toBeRemoved como o pai do filho a esquerda de toBeRemoved.
        }

        else {//se o filho a direita de toBeRemoved nao for no sentinela:
            y = successor(toBeRemoved->right);//y aponta para o sucessor de toBeRemoved.
            yColor = y->color;//yColor recebe a cor de y.
            x = y->right;//x recebe o filho a direita de y.

            if (y->father == toBeRemoved) x->father = y;//se toBeRemoved for pai de y, o ponteiro que aponta para o pai, de x, aponta para y.

            else {
                transferePai(root, y, y->right);//torna o pai do filho a direita de y como sendo o pai de y.
                y->right = toBeRemoved->right;//o ponteiro para o filho a direita de y aponta para o filho a direita de toBeRemoved.
                y->right->father = y;//o ponteiro para o pai, do filho a direita de y, aponta para y.
            }

            transferePai(root, toBeRemoved, y);//torna o pai de y como sendo o pai de toBeRemoved.
            y->left = toBeRemoved->left;//o ponteiro para o filho a esquerda, de y, aponta para o filho a esquerda de toBeRemoved.
            y->left->father = y;//o ponteiro para o pai, do filho a esquerda de y, aponta para y.
            y->color = toBeRemoved->color;//torna a cor de y como sendo a cor de toBeRemoved.
        }
    }
    if (yColor == black) removeFixUp(root, x);/* se a cor antiga de y, armazenada em yColor for preto, chama a funcao removeFixUp
                                                 para balancear a arvore, passando a raiz da arvore, e x como parametro.*/
    return toBeRemoved;//retorna toBeRemoved.
}


//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por calcular a altura de uma arvore/subarvore.
//Parametros: ponteiro para a raiz da arvore/subarvore.
//Retorno: lH ou rH, que representa a altura da arvore.
int heightARN(ARNNode* root) {
    int lH = 0, rH = 0; /*Define duas variaveis, lH representa a altura.
                        a esquerda, e rH a altura a direita*/
    if (root == externo) return 0; //Se o nó não existir sua altura é 0.

    /*Calcula as alturas da esquerda e direita da arvore/subarvore utilizando chamadas recursivas.*/
    lH = 1 + heightARN(leftNode(root));
    rH = 1 + heightARN(rightNode(root));

    //Identifica e retorna a maior das alturas.
    if (rH > lH) return rH;
    else return lH;
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por realizar a etapa de recursao da insercao.
//Parametros: ponteiro para a raiz da arvore, ponteiro para um no, que representa o no a ser inserido.
//Retorno: root, que representa a posicao na qual o no deve ser inserido.
ARNNode* insereARN(ARNNode* root, ARNNode* newNode) {
    if (root == externo) return newNode;//se a raiz for no sentinela, retorna o novo no.

    if (getID(newNode) < getID(root)) {//se o id do no a ser inserido for menor que o id do no atual que root aponta:
        root->left = insereARN(root->left, newNode);/*o ponteiro para o filho a esquerda, de root, recebe o retorno da chamada recursiva de insereARN
                                                      passando o filho a esquerda de root, e newNode como parametro*/
        root->left->father = root;//o ponteiro que aponta para o pai, do filho a esquerda de root, aponta para root.
    }
    else if (getID(newNode) > getID(root)) {//se o id do no a ser inserido nao for maior que o id do no atual que root aponta:
        root->right = insereARN(root->right, newNode);/*o ponteiro para o filho a direita, de root, recebe o retorno da chamada recursiva de insereARN
                                                      passando o filho a direita de root, e newNode como parametro*/
        root->right->father = root;//o ponteiro que aponta para o pai, do filho a direita de root, aponta para root.
    }
    return root;
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por realizar a insercao de um noh na arvore.
//Parametros: ponteiro de ponteiro para a raiz da arvore, ponteiro para um no, que representa o no a ser inserido.
//Retorno: inteiro, 1 para sucesso, e 0 para falha.
int insere(ARNNode** root, ARNNode* newNode) {
    if(searchNode(*root, newNode->info->key->id) == externo){/*busca o no a ser inserido para verificar se o mesmo ja se encontra na arvore
                                                               se a busca retornar o no sentinela, significa que o no nao foi encontrado, entao:*/
       *root = insereARN(*root, newNode);//root recebe o retorno da funcao insereARN, recebendo como parametro a raiz da arvore, e o novo no a ser inserido.
        insereFixUp(root, newNode);//chama a funcao insereFixUp para balancear a arvore, passando como parametro um ponteiro que aponta para o ponteiro da raiz, e o novo no.
        return 1;//retorna 1, pois a insercao foi bem sucedida.
    }
    else{
        freeNode(newNode);//limpa o novo no a ser inserido, pois o mesmo ja existe na arvore.
        return 0;//retorna 0 atestando falha na insercao.
    }
}

//--------------------------------------------------------------------------------------------------------
//Funcao responsavel por limpar um espaco de memoria alocado em um no.
//Parametros: ponteiro para um no, que representa o no ser limpo.
//Retorno: vazio.
void freeNode(ARNNode* node){
    if(node == externo) return;//caso o no seja externo, retorna vazio pois o mesmo nao deve ser limpo.
    free(node->info->key);//limpa a informacao alocada na chave do no.
    free(node->info);//limpa espaco alocado no ponteiro que aponta para o elemento de informacao do no.
    free(node);//limpa o espaco alocado no no.
    return;
}

//--------------------------------------------------------------------------------------------------------
/*Função que destroi uma arvore, liberando toda mémória utilizada pela mesma.
Parâmetros: (raiz da arvore)*/
void destroyARN(ARNNode* root){
    if(root==externo) return;//caso a chave atual da recursão não exista, não há mais nada a destruir.
    destroyARN(rightNode(root));//Chamada recursiva para o filho a direita do nó atual.
    destroyARN(leftNode(root));//Chamada recursiva para o filho a esquerda do nó atual.
    freeNode(root);//Chama a função que libera a mémoria alocada em um nó
}
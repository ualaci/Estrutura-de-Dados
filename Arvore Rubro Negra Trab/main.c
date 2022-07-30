//Uarlley do Nascimento Amorim
//#include "ARN.h"
#include "ARN.h"

void trataScanf(){
    printf("Erro na leitura!\n");
    while(getchar()!= '\n');
    printf("Pressione enter para continuar...");
    getchar();
    return;
}

int main(){
    int op;
    externo = (ARNNode*)calloc(1,sizeof(ARNNode));
    ARNNode* root = externo;
    while(1){
        system("clear");
        printf("--------------------------\n");
        printf("| 1 - Inserir um artigo   |\n");
        printf("| 2 - Buscar um artigo    |\n");
        printf("| 3 - Excluir um artigo   |\n");
        printf("| 4 - imprimir artigos    |\n");
        printf("| 5 - Sair                |\n");
        printf(" -------------------------\n");

        if(!scanf("%d",&op)){
            trataScanf();
            continue;
        }
        if(op == 1){
            int id,ano;
            char autor[200], titulo[200], revista[200], DOI[20], palavraChave[200];
            printf("Preencha as informações do artigo:\n");
            printf("\tID: ");
            if(!scanf("%d",&id)) {
                trataScanf();
                continue;
            }
            printf("\tAno: ");
            if(!scanf("%d",&ano)){
                trataScanf();
                continue;
            }
            getchar();
            printf("\tAutor: ");
            fgets(autor,200,stdin);
            autor[strlen(autor)-1] = 0;
            printf("\tTitulo: ");
            fgets(titulo,200,stdin);
            titulo[strlen(titulo)-1] = 0;
            printf("\tRevista: ");
            fgets(revista,200,stdin);
            revista[strlen(revista)-1] = 0;
            printf("\tDOI: ");
            fgets(DOI,20,stdin);
            DOI[strlen(DOI)-1] = 0;
            printf("\tPalavra-chave: ");
            fgets(palavraChave,200,stdin);
            palavraChave[strlen(palavraChave)-1] = 0;
            artigo* newArtigo = criaArtigo(id,ano,autor,titulo,revista,DOI,palavraChave);
            ARNNode* newNode = createNode(newArtigo);
            if(insere(&root,newNode)) printf("Artigo inserido!\n");
            else printf("A inserção falhou: Artigo duplicado.\n");
        }

        if(op == 2){
            int id;
            printf("Digite o id do artigo a ser buscado: ");
            if(!scanf("%d", &id)){
                trataScanf();
                continue;
            }
            ARNNode *resultado = searchNode(root,id);
            if(resultado != externo) imprimeArtigo(resultado);
            else printf("Artigo não encontrado!\n");
        }
        if(op == 3){
            int id;
            printf("Digite o id do artigo a ser excluido: ");
            if(!scanf("%d", &id)){
                trataScanf();
                continue;
            }
            ARNNode* removido = removeARN(&root, id);
            if(removido == externo) printf("Artigo não encontrado!\n");
            else printf("O artigo %s foi removido!\n",removido->info->key->titulo);
            freeNode(removido);

        }
        if(op == 4){
            system("clear");
            imprimeARN(root);

        }
        if(op == 5){
            destroyARN(root);
            free(externo);
            break;
        }

        if(op!=1) getchar();
        printf("Pressione enter para continuar...");
        while(getchar()!= '\n');
    }
}
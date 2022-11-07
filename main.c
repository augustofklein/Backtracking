#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char C_CAMINHO_VALIDO = 'O';
char C_CAMINHO_INVALIDO = 'X';
char C_CAMINHO_PERCORRIDO = '.';
int POSICAO_INVALIDA = 999;
int CAMINHO_ENCONTRADO = 0;

struct dados_matriz{
    int qtd_linhas;
    int qtd_colunas;
    int linha_inicial;
    int coluna_inicial;
    int linha_final;
    int coluna_final;
};

typedef struct dados_matriz Dados;

Dados dados;

void inicializa_matriz_caminho(char **mat, char **cam){

    int i, j;

    for(i=0;i<dados.qtd_linhas;i++){
        for(j=0;j<dados.qtd_colunas;j++){
            cam[i][j] = mat[i][j];
        }
    }

}

void imprime_matriz(char **mat){

    int i, j;

    printf("+---------------+\n");

    for(i=0;i<dados.qtd_linhas;i++){
        for(j=0;j<dados.qtd_colunas;j++){
            printf("| %c ", mat[i][j]);
        }
        printf("|\n");
        printf("+---------------+\n");
    }

}

char ** aloca_matriz(char **mat){

    int i;

    mat = (char**)malloc(dados.qtd_linhas * sizeof(char*));

    for(i=0;i<dados.qtd_linhas;i++){
        mat[i] = (char*)malloc(dados.qtd_colunas * sizeof(char*));
    }

    return mat;

}

char ** retorna_matriz_base(){

    int i, j;
    char **mat;
    FILE *arq;

    arq = fopen("entrada.txt", "rt");

    if(arq == NULL){
        printf("Erro na abertura do arquivo de entrada!");
        return NULL;
    }

    fscanf(arq, "%d%d", &dados.qtd_linhas, &dados.qtd_colunas);

    fscanf(arq, "%d%d", &dados.linha_inicial, &dados.coluna_inicial);

    fscanf(arq, "%d%d", &dados.linha_final, &dados.coluna_final);

    mat = aloca_matriz(mat);

    for(i=0;i<dados.qtd_linhas;i++){
        for(j=0;j<dados.qtd_colunas;j++){
            fscanf(arq, " %c ", &mat[i][j]);
        }
    }

    return mat;

}

char ** retorna_matriz_caminho(char **mat){

    char **cam;

    cam = aloca_matriz(cam);

    inicializa_matriz_caminho(mat, cam);

    return cam;

}

int posicao_valida(int pos_linha, int pos_coluna, char **mat){

    if(mat[pos_linha][pos_coluna] == C_CAMINHO_INVALIDO){
        return 1;
    }else{
        return 0;
    }

}

void seta_posicao_percorrida(int pos_linha, int pos_coluna, char **cam){

    cam[pos_linha][pos_coluna] = C_CAMINHO_PERCORRIDO;

}

void seta_posicao_invalida(int pos_linha, int pos_coluna, char **cam){

    cam[pos_linha][pos_coluna] = C_CAMINHO_INVALIDO;

}

int chegada_caminho_final(int pos_linha, int pos_coluna){

    if(pos_linha == dados.linha_final && pos_coluna == dados.coluna_final){
        return 1;
    }else{
        return 0;
    }

}

void retorna_proxima_posicao(int atual_linha, int atual_coluna, int *nova_linha, int *nova_coluna, char **cam){

    if(atual_coluna < 3){
        if(cam[atual_linha][atual_coluna + 1] == C_CAMINHO_VALIDO){
            *nova_linha = atual_linha;
            *nova_coluna = (atual_coluna + 1);
            return;
        }
    }

    if(atual_coluna > 0){
        if(cam[atual_linha][atual_coluna - 1] == C_CAMINHO_VALIDO){
            *nova_linha = atual_linha;
            *nova_coluna = (atual_coluna - 1);
            return;
        }
    }

    if(atual_linha < 3){
        if(cam[atual_linha + 1][atual_coluna] == C_CAMINHO_VALIDO){
            *nova_linha = (atual_linha + 1);
            *nova_coluna = atual_coluna;
            return;
        }
    }

    if(atual_linha > 0){
        if(cam[atual_linha - 1][atual_coluna] == C_CAMINHO_VALIDO){
            *nova_linha = (atual_linha - 1);
            *nova_coluna = atual_coluna;
            return;
        }
    }

    *nova_linha = POSICAO_INVALIDA;
    *nova_coluna = POSICAO_INVALIDA;

}

void verifica_percurso_encontrado(char **cam){

    if(!CAMINHO_ENCONTRADO){
        printf("Caminho nao encontrado para a matriz do arquivo!\n");
    }

}

void back(int atual_linha, int atual_coluna, char **mat, char **cam){

    int fim;
    int nova_linha, nova_coluna;

    fim = 0;

    while(!fim){
        if(chegada_caminho_final(atual_linha, atual_coluna)){
            CAMINHO_ENCONTRADO = 1;
            imprime_matriz(cam);
            break;
        }

        retorna_proxima_posicao(atual_linha, atual_coluna, &nova_linha, &nova_coluna, cam);

        if(nova_linha == POSICAO_INVALIDA && nova_coluna == POSICAO_INVALIDA){
            seta_posicao_invalida(atual_linha, atual_coluna, cam);
            break;
        }

        seta_posicao_percorrida(nova_linha, nova_coluna, cam);
        back(nova_linha, nova_coluna, mat, cam);
    }

}

int main(){

    char **mat;
    char **cam;

    mat = retorna_matriz_base();

    cam = retorna_matriz_caminho(mat);

    seta_posicao_percorrida(dados.linha_inicial, dados.coluna_inicial, cam);

    back(dados.linha_inicial, dados.coluna_inicial, mat, cam);

    verifica_percurso_encontrado(cam);

}

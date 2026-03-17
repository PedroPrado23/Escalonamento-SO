#include <stdio.h>
#include <stdlib.h>

typedef struct _elemento_fila{
    int info;
    struct _elemento_fila *prox;
} ElementoFila;

typedef struct _fila{
    ElementoFila *ini;
    ElementoFila *fim;
    int num_elems;
} Fila;

ElementoFila *novoElemento(int info) {
    ElementoFila *novo = (ElementoFila*) malloc(sizeof(ElementoFila));
    if (novo != NULL) {
        novo->info = info;
        novo->prox = NULL;
    }
    return novo;
}

void enfileirar(Fila *f, int info);
int desenfileirar(Fila *f);
void imprimirFila(Fila *f);
void destruirFila(Fila *f);

int main(int argc, char *argv[]){
    Fila f;
    f.ini = f.fim = NULL;
    f.num_elems = 0;
    int numTarefas;
    
    scanf("%d", &numTarefas);

    int *ingresso = malloc(numTarefas * sizeof(int));
    int *duracao  = malloc(numTarefas * sizeof(int));
    int *prioridade = malloc(numTarefas * sizeof(int));

    for(int i = 0; i < numTarefas; i++) {
        scanf("%d", &ingresso[i]);
    }
    
    for(int i = 0; i < numTarefas; i++) {
        scanf("%d", &duracao[i]);
    }
    
    for(int i = 0; i < numTarefas; i++) {
        scanf("%d", &prioridade[i]);
    }
    
    FILE *arq = fopen("1.out", "w");
    if(arq == NULL){
        printf("Erro ao criar o arquivo!\n");
        return -1;
    }

    if(arq){
        fprintf(arq, "%s", "FCFS\n");
        fprintf(arq, "%d\n", numTarefas);

        for(int i = 0; i < numTarefas; i++){
            fprintf(arq, "%d\n", ingresso[i]);
        }

        int tempo = 0;
        int concluidas = 0;
        int *restante = malloc(numTarefas *sizeof(int));
    
        for(int i = 0; i < numTarefas; i++){
            restante[i] = duracao[i];
    }
    
    while(concluidas < numTarefas){
        for(int i = 0; i < numTarefas; i++){
            if(ingresso[i] == tempo)
            enfileirar(&f, i);
    }
    
    if(f.ini != NULL){
        int idx = f.ini->info;
        fprintf(arq, "%d\n", idx + 1);
            restante[idx]--;
            
            if(restante[idx] == 0){
                desenfileirar(&f);
                concluidas++;
            }
        } else {
            fprintf(arq, "0\n");
        }
        
        tempo++;
    }

        fclose(arq);
        free(restante);
        
    } else {
        printf("Erro ao tentar abrir arquivo\n");
    }
    
    free(ingresso);
    free(duracao);
    free(prioridade);
    
    return 0;
}

void enfileirar(Fila *f, int info) {
    ElementoFila *novoElem = novoElemento(info);
    
    if(novoElem == NULL){
        printf("Erro de alocação de memória\n");
        return;
    }

    if(f->ini == NULL){
        f->ini = f->fim = novoElem;
    } else {
        f->fim->prox = novoElem;
        f->fim = novoElem;  
    }

    f->num_elems++;
}

int desenfileirar(Fila *f) {
    int ret = -1;

    ElementoFila *aux = NULL;

    if (f->ini != NULL) {

        ret = f->ini->info;
        aux = f->ini;
        f->ini = aux->prox;
        free(aux);
        if(f->ini == NULL){
            f->fim = NULL;
        }
        f->num_elems--;

    } else {
        printf("Queue Underflow!!!\n");
    }

    return ret;
}

void imprimirFila(Fila *f) {
    ElementoFila *aux = NULL;

    if (f->ini != NULL) {
        aux = f->ini;
        for (aux = f->ini; aux != NULL; aux = aux->prox){
            printf("%d <- ", aux->info);
        }

    printf("Num. Elems: %d\n", f->num_elems);
    } else {
        printf("Fila vazia!\n");
    }
}

void destruirFila(Fila *f) {
    ElementoFila *aux = f->ini;

    while(aux != NULL){
        f->ini = aux->prox;
        free(aux);
        aux = f->ini;
    }

    f->fim = NULL;
}
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

    printf("Número de tarefas: %d\n", numTarefas);
    printf("Ingresso: ");
    for(int i = 0; i < numTarefas; i++) printf("%d ", ingresso[i]);
    printf("\nDuração: ");
    for(int i = 0; i < numTarefas; i++) printf("%d ", duracao[i]);
    printf("\nPrioridade: ");
    for(int i = 0; i < numTarefas; i++) printf("%d ", prioridade[i]);
    printf("\n");
    
    free(ingresso);
    free(duracao);
    free(prioridade);

    // enfileirar(&f, 'a');
    // enfileirar(&f, 'b');
    // enfileirar(&f, 'c');
    // enfileirar(&f, 'd');
    // imprimirFila(&f);
    // desenfileirar(&f);
    // imprimirFila(&f);
    // desenfileirar(&f);

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
            printf("%c <- ", aux->info);
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
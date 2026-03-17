// Executar windows: Get-Content ./1.in | fcfs.exe ./1.out

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
    
    int linha = 0, pos = 0, secao = 1, valor, numTarefas;
    
    scanf("%d", &numTarefas);
    linha++;

    int *ingresso = malloc(numTarefas * sizeof(int));
    int *duracao  = malloc(numTarefas * sizeof(int));
    int *prioridade = malloc(numTarefas * sizeof(int));

    secao++; 

    while (scanf("%d", &valor) != EOF) {      
        
        if (secao == 2) ingresso[pos++] = valor;     
        if (secao == 3) duracao[pos++] = valor;       
        if (secao == 4) prioridade[pos++] = valor;        
            
        if (linha % numTarefas == 0)  {
            switch(secao) {
                case 2:
                    pos = 0;
                break;              
                case 3:
                    pos = 0;
                break;
                case 4:
                    pos = 0;
                break;              
            }
            secao++; 
        }
        
        linha++;
    }

    FILE *arq = fopen(argv[1], "w");
    if(arq == NULL){
        printf("Erro ao criar o arquivo!\n");
        free(ingresso); free(duracao); free(prioridade);
        return -1;
    }

    fprintf(arq, "%s", "FCFS\n");
    fprintf(arq, "%d\n", numTarefas);

    for(int i = 0; i < numTarefas; i++){
        fprintf(arq, "%d\n", ingresso[i]);
    }

    int tempo = 0;
    int concluidas = 0;
    int *restante = malloc(numTarefas * sizeof(int));

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
    
    free(ingresso);
    free(duracao);
    free(prioridade);
    
    destruirFila(&f);
    
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
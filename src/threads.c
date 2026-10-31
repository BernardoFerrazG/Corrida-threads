#include "threads.h"

#include <stdio.h>

void *correr(void *arg) {
    Corredora *corredora = arg;
    Corrida *corrida = corredora->corrida;

    /* Ninguém larga antes de todas as threads estarem criadas. */
    pthread_barrier_wait(&corrida->largada);

    for (int i = 0; i <= corrida->alvo; i++) {
        printf("Thread %d: %d\n", corredora->id, i);
    }

    /* Seção crítica: só a primeira thread a chegar aqui é registrada como vencedora. */
    pthread_mutex_lock(&corrida->mutex_vencedora);
    if (corrida->vencedora == -1) {
        corrida->vencedora = corredora->id;
        printf(">>>>> Thread %d venceu! <<<<<\n", corredora->id);
    }
    pthread_mutex_unlock(&corrida->mutex_vencedora);

    return NULL;
}

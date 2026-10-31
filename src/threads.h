#ifndef THREADS_H
#define THREADS_H

#include <pthread.h>

/* Estado compartilhado por todas as threads da corrida. */
typedef struct {
    int alvo;                     /* cada thread conta de 0 até este valor */
    int vencedora;                /* id da primeira thread a terminar, -1 enquanto ninguém terminou */
    pthread_barrier_t largada;    /* segura todas as threads até a última estar pronta */
    pthread_mutex_t mutex_vencedora;
} Corrida;

/* Argumento de cada thread. */
typedef struct {
    int id;
    Corrida *corrida;
} Corredora;

void *correr(void *arg);

#endif

#ifndef THREADS_H
#define THREADS_H

#define _XOPEN_SOURCE 700

#include <pthread.h>

#define MAX 99

typedef struct{
    int num_threads;
    int t_num_vencedor;
    pthread_barrier_t barreira;
    pthread_mutex_t vencedor_mutex;
} Thread_infos;

typedef struct{
    int t_num;
    Thread_infos *infos;
} Thread;

void *corrida_de_threads(void *t);

#endif
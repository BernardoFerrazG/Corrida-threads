#include "threads.h"

#include <stdio.h>

void *corrida_de_threads(void *t){
    Thread *thread = (Thread *)t;
    Thread_infos *t_infos = thread->infos;

    pthread_barrier_wait(&t_infos->barreira);

    for (int i = 0; i <= MAX; i++){
        printf("Thread %d: %d\n", thread->t_num, i);
    }

    pthread_mutex_lock(&t_infos->vencedor_mutex);
    if (t_infos->t_num_vencedor == -1){
        t_infos->t_num_vencedor = thread->t_num;
        printf(">>>>> Thread %d venceu! <<<<<\n", thread->t_num);
    }
    pthread_mutex_unlock(&t_infos->vencedor_mutex);

}
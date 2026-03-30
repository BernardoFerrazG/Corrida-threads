#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "threads.h"

int main(int argc, char *argv[]){

    int num_threads = atoi(argv[1]);

    Thread_infos t_info;
    t_info.num_threads = num_threads;
    t_info.t_num_vencedor = -1;


    pthread_t threads[num_threads];
    Thread t_array[num_threads];

    pthread_mutex_init(&t_info.vencedor_mutex, NULL);
    pthread_barrier_init(&t_info.barreira, NULL, num_threads);

    for (int i = 0; i < num_threads; i++){
        t_array[i].t_num = i;
        t_array[i].infos = &t_info;
        
        pthread_create(&threads[i], NULL, corrida_de_threads, &t_array[i]);
    }

    for (int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }

    printf("\nThread vencedora: %d\n", t_info.t_num_vencedor);

    pthread_barrier_destroy(&t_info.barreira);
    pthread_mutex_destroy(&t_info.vencedor_mutex);

    return 0;
}
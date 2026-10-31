#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "threads.h"

#define ALVO_PADRAO 99
#define MAX_THREADS 1024

static int le_inteiro(const char *texto, int minimo, int maximo, int *saida) {
    char *fim;
    errno = 0;
    long valor = strtol(texto, &fim, 10);
    if (errno != 0 || *fim != '\0' || valor < minimo || valor > maximo) {
        return 0;
    }
    *saida = (int)valor;
    return 1;
}

static void uso(const char *programa) {
    fprintf(stderr, "Uso: %s <num_threads> [alvo]\n", programa);
    fprintf(stderr, "  num_threads  número de threads na corrida (1 a %d)\n", MAX_THREADS);
    fprintf(stderr, "  alvo         até quanto cada thread conta (padrão: %d)\n", ALVO_PADRAO);
}

int main(int argc, char *argv[]) {
    int num_threads;
    int alvo = ALVO_PADRAO;

    if (argc < 2 || argc > 3 || !le_inteiro(argv[1], 1, MAX_THREADS, &num_threads) ||
        (argc == 3 && !le_inteiro(argv[2], 0, 1000000, &alvo))) {
        uso(argv[0]);
        return EXIT_FAILURE;
    }

    Corrida corrida = {.alvo = alvo, .vencedora = -1};
    pthread_mutex_init(&corrida.mutex_vencedora, NULL);
    pthread_barrier_init(&corrida.largada, NULL, (unsigned)num_threads);

    pthread_t *threads = malloc(sizeof *threads * (size_t)num_threads);
    Corredora *corredoras = malloc(sizeof *corredoras * (size_t)num_threads);
    if (threads == NULL || corredoras == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < num_threads; i++) {
        corredoras[i] = (Corredora){.id = i, .corrida = &corrida};
        int erro = pthread_create(&threads[i], NULL, correr, &corredoras[i]);
        if (erro != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(erro));
            return EXIT_FAILURE; /* threads já criadas ficariam presas na barreira */
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nThread vencedora: %d\n", corrida.vencedora);

    pthread_barrier_destroy(&corrida.largada);
    pthread_mutex_destroy(&corrida.mutex_vencedora);
    free(threads);
    free(corredoras);
    return EXIT_SUCCESS;
}

// Desafio: Detective Quest - Nível Aventureiro
// Objetivo: Desenvolver o sistema de coleta de pistas em Detective Quest, integrando a árvore binária do mapa com uma Árvore Binária de Busca de pistas. Ao explorar salas pré-definidas, seu código insere cada pista automaticamente e exibe todas, em ordem alfabética, ao final da jornada.

// Inclusão das bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- ESTRUTURAS DE DADOS ---

// Struct PistaNode para a Árvore Binária de Busca (BST) de pistas.
typedef struct PistaNode {
    char conteudo[100];
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;
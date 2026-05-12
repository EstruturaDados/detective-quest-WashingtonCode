// Desafio: Detective Quest - Nível Mestre
// Objetivo: Desenvolver a integração da árvore binária do mapa, BST de pistas e tabela hash de suspeitos, conduzindo a exploração interativa da mansão, coleta automática de pistas e acusação final. Seu programa confirmará evidências e encerrará a investigação em C.

// Inclusão das bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da constante com o tamanho da tabela hash
#define TAM_HASH 10

// --- ESTRUTURAS DE DADOS ---

// struct PistaNode - Árvore Binária de Busca (BST) para armazenar pistas coletadas.
typedef struct PistaNode {
    char conteudo[100];
    struct PistaNode *esq, *dir;
} PistaNode;
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

// Struct Sala para o mapa da mansão (Árvore Binária).
 
typedef struct Sala {
    char nome[50];
    char pista[100]; // Pista associada a este cômodo
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// --- PROTÓTIPOS DAS FUNÇÕES ---
Sala* criarSala(char nome[], char pista[]);
PistaNode* inserirPista(PistaNode* raiz, char conteudo[]);
void explorarSalasComPistas(Sala* mapa, PistaNode** inventario);
void exibirPistas(PistaNode* raiz);
void liberarMapa(Sala* raiz);
void liberarPistas(PistaNode* raiz);
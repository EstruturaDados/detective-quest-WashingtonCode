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

// struct Sala - Árvore Binária representando o mapa físico da mansão.
typedef struct Sala {
    char nome[50];
    char pista[100];
    struct Sala *esquerda, *direita;
} Sala;

// struct HashNode - Tabela Hash para associar Pistas a Suspeitos.
typedef struct HashNode {
    char pista[100];
    char suspeito[50];
    struct HashNode *proximo;
} HashNode;

// Tabela Hash de associações Pista/Suspeito
HashNode* tabelaHash[TAM_HASH];

// --- PROTÓTIPOS DAS FUNÇÕES ---
Sala* criarSala(char nome[], char pista[]);
PistaNode* inserirPista(PistaNode* raiz, char conteudo[]);
void inserirNaHash(char pista[], char suspeito[]);
char* encontrarSuspeito(char pista[]);
void explorarSalas(Sala* mapa, PistaNode** inventario);
void exibirPistas(PistaNode* raiz);
void percorrerEContar(PistaNode* raiz, char* acusado, int* contador);
void verificarSuspeitoFinal(PistaNode* inventario);
void liberarMapa(Sala* raiz);
void liberarPistas(PistaNode* raiz);
void liberarHash();
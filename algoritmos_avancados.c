// Desafio: Detective Quest - Nível Novato
// Objetivo: Desenvolver um jogo onde você aplicará a árvore binária para criar o mapa interativo da mansão em Detective Quest. Implemente funções criarSala(), explorarSalas() e navegue do Hall de entrada até um nó-folha, garantindo usabilidade, legibilidade e documentação clara.

// Inclusão das bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Criação da Struck sala para representar cada cômodo da mansão
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Protótipos das funções
Sala* criarSala(char nome[]);
void explorarSalas(Sala* raiz);
void liberarMemoria(Sala* raiz);
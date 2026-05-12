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

// Função principal
int main() {
    // 1. Criando os cômodos individualmente
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* jardim = criarSala("Jardim");
    Sala* despensa = criarSala("Despensa");
    Sala* escritorio = criarSala("Escritorio");

    // 2. Montando a estrutura da árvore (Mapa da Mansão)
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;

    cozinha->esquerda = despensa;
    
    biblioteca->direita = escritorio;

    // 3. Iniciando a gameplay
    explorarSalas(hall);

    // 4. Finalização e limpeza de memória
    printf("\nLimpando registros e liberando memoria...\n");
    liberarMemoria(hall);
    printf("Sistema encerrado com sucesso.\n");

    return 0;
}

/**
 * criarSala() - Aloca memória dinamicamente para uma nova sala.
 * @nome: String com o nome do cômodo.
 * Retorna: Ponteiro para a nova Sala criada.
 */
Sala* criarSala(char nome[]) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("[Erro]: Falha na alocacao de memoria.\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}
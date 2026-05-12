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

// --- FUNÇÃO PRINCIPAL ---
int main() {
        
    // 1. Inicialização do Inventário de Pistas (BST vazia)
    PistaNode* inventarioPistas = NULL;

    // 2. Montando o Mapa da Mansão com Pistas
    // criarSala(Nome, Pista)
    Sala* hall = criarSala("Hall de Entrada", "Chave enferrujada");
    Sala* salaEstar = criarSala("Sala de Estar", "Bilhete rasgado");
    Sala* cozinha = criarSala("Cozinha", "Faca suja de terra");
    Sala* biblioteca = criarSala("Biblioteca", "Livro com fundo falso");
    Sala* jardim = criarSala("Jardim", "Pegadas proximas ao muro");
    Sala* despensa = criarSala("Despensa", "Fragmento de tecido");
    Sala* escritorio = criarSala("Escritorio", "Senha do cofre");

    // Conexões do Mapa
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->esquerda = despensa;
    biblioteca->direita = escritorio;

    // 3. Execução do Jogo
    explorarSalasComPistas(hall, &inventarioPistas);

    // 4. Exibição do Resultado Final
    printf("\n========================================");
    printf("\n       RELATORIO FINAL DE PISTAS       ");
    printf("\n(Organizadas em Ordem Alfabetica pela BST)");
    printf("\n========================================\n");
    if (inventarioPistas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        exibirPistas(inventarioPistas);
    }

    // 5. Limpeza de Memória
    liberarMapa(hall);
    liberarPistas(inventarioPistas);

    printf("\nSistema encerrado. Obrigado, Detetive!\n");
    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Função criar sala
Sala* criarSala(char nome[], char pista[]) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (nova) {
        strcpy(nova->nome, nome);
        strcpy(nova->pista, pista);
        nova->esquerda = NULL;
        nova->direita = NULL;
    }
    return nova;
}

// Função inserir pista
PistaNode* inserirPista(PistaNode* raiz, char conteudo[]) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->conteudo, conteudo);
        novo->esq = novo->dir = NULL;
        return novo;
    }
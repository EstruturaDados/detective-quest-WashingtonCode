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

// --- FUNÇÃO PRINCIPAL ---
int main() {
    
    // Inicialização da Tabela Hash (Dicionário de Evidências)
    for(int i=0; i<TAM_HASH; i++) tabelaHash[i] = NULL;

    inserirNaHash("Chave enferrujada", "Mordomo");
    inserirNaHash("Livro com fundo falso", "Mordomo");
    inserirNaHash("Bilhete rasgado", "Cozinheira");
    inserirNaHash("Fragmento de tecido", "Cozinheira");
    inserirNaHash("Faca suja de terra", "Jardineiro");
    inserirNaHash("Pegadas proximas ao muro", "Jardineiro");

    // Montagem do Mapa da Mansão (Árvore Binária)
    Sala* hall = criarSala("Hall de Entrada", "Chave enferrujada");
    Sala* salaEstar = criarSala("Sala de Estar", "Bilhete rasgado");
    Sala* cozinha = criarSala("Cozinha", "Fragmento de tecido");
    Sala* biblioteca = criarSala("Biblioteca", "Livro com fundo falso");
    Sala* jardim = criarSala("Jardim", "Pegadas proximas ao muro");
    Sala* despensa = criarSala("Despensa", "Faca suja de terra");

    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    salaEstar->direita = jardim;
    cozinha->esquerda = despensa;

    // Execução do Jogo
    PistaNode* inventarioPistas = NULL;
    explorarSalas(hall, &inventarioPistas);

    // Julgamento Final
    if (inventarioPistas != NULL) {
        verificarSuspeitoFinal(inventarioPistas);
    } else {
        printf("\nInvestigacao encerrada sem pistas coletadas.\n");
    }

    // Liberação de Memória (O dever de todo programador Mestre)
    printf("\n[SISTEMA]: Desalocando estruturas e limpando memoria...\n");
    liberarMapa(hall);
    liberarPistas(inventarioPistas);
    liberarHash();

    printf("[SISTEMA]: Programa finalizado com sucesso.\n");
    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Função criarSala
Sala* criarSala(char nome[], char pista[]) {
    Sala* nova = (Sala*)malloc(sizeof(Sala));
    if (!nova) exit(1);
    strcpy(nova->nome, nome);
    strcpy(nova->pista, pista);
    nova->esquerda = nova->direita = NULL;
    return nova;
}

// Função inserirPista
PistaNode* inserirPista(PistaNode* raiz, char conteudo[]) {
    if (raiz == NULL) {
        PistaNode* novo = (PistaNode*)malloc(sizeof(PistaNode));
        strcpy(novo->conteudo, conteudo);
        novo->esq = novo->dir = NULL;
        return novo;
    }
    if (strcmp(conteudo, raiz->conteudo) < 0)
        raiz->esq = inserirPista(raiz->esq, conteudo);
    else if (strcmp(conteudo, raiz->conteudo) > 0)
        raiz->dir = inserirPista(raiz->dir, conteudo);
    return raiz;
}

// Função inserirNaHash
void inserirNaHash(char pista[], char suspeito[]) {
    int soma = 0;
    for(int i=0; pista[i] != '\0'; i++) soma += pista[i];
    int indice = soma % TAM_HASH;

    HashNode* novo = (HashNode*)malloc(sizeof(HashNode));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->proximo = tabelaHash[indice];
    tabelaHash[indice] = novo;
}

// Função encontrarSuspeito
char* encontrarSuspeito(char pista[]) {
    int soma = 0;
    for(int i=0; pista[i] != '\0'; i++) soma += pista[i];
    int indice = soma % TAM_HASH;

    HashNode* atual = tabelaHash[indice];
    while (atual) {
        if (strcmp(atual->pista, pista) == 0) return atual->suspeito;
        atual = atual->proximo;
    }
    return "Desconhecido";
}

// Função explorarSalas
void explorarSalas(Sala* mapa, PistaNode** inventario) {
    Sala* atual = mapa;
    char escolha;
    printf("\n--- MODO INVESTIGACAO ATIVO ---\n");

    while (atual) {
        printf("\nVocê está em: %s", atual->nome);
        printf("\nPista encontrada no local: %s", atual->pista);
        *inventario = inserirPista(*inventario, atual->pista);

        printf("\n\nOpcoes:\n"); 
        printf("[e] Esquerda: %s\n", atual->esquerda ? atual->esquerda->nome : "Fim");
        printf("[d] Direita: %s\n", atual->direita ? atual->direita->nome : "Fim");
        printf("[s] Sair\n");
        printf("\nEscolha: ");
        scanf(" %c", &escolha);

        if ((escolha == 'e' || escolha == 'E') && atual->esquerda) atual = atual->esquerda;
        else if ((escolha == 'd' || escolha == 'D') && atual->direita) atual = atual->direita;
        else if (escolha == 's' || escolha == 'S') break;
        else printf("\n[AVISO]: Caminho invalido!\n");
    }
}
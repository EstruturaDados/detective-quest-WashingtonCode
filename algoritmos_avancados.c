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

/**
 * explorarSalas() - Função principal de interação com o jogador.
 * Navega pela árvore conforme a entrada do usuário até encontrar um nó-folha.
 */
void explorarSalas(Sala* raiz) {
    Sala* atual = raiz;
    char escolha;

    printf("\n========================================\n");
    printf("      BEM-VINDO AO DETECTIVE QUEST      \n");
    printf("========================================\n");
    printf("Sua missao: Explore a mansao ate o fim.\n");

    while (atual != NULL) {
        printf("\nVocê está em: %s\n", atual->nome);

        // Verificação de Nó-Folha (Objetivo final)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("----------------------------------------\n");
            printf("Voce chegou ao fim do caminho nesta ala.\n");
            printf("Investigacao concluida na sala: %s\n", atual->nome);
            break;
        }

        // Exibição de opções dinâmicas
        printf("Caminhos disponiveis:\n");
        if (atual->esquerda) printf(" [e] Esquerda -> Ir para: %s\n", atual->esquerda->nome);
        if (atual->direita)  printf(" [d] Direita  -> Ir para: %s\n", atual->direita->nome);
        printf(" [s] Sair do Jogo\n");
        
        printf("\nSua escolha: ");
        scanf(" %c", &escolha);

        if (escolha == 'e' || escolha == 'E') {
            if (atual->esquerda) {
                atual = atual->esquerda;
            } else {
                printf("\aAVISO: Nao existe caminho a esquerda aqui!\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (atual->direita) {
                atual = atual->direita;
            } else {
                printf("\aAVISO: Nao existe caminho a direita aqui!\n");
            }
        } 
        else if (escolha == 's' || escolha == 'S') {
            printf("Encerrando investigacao prematuramente...\n");
            break;
        } 
        else {
            printf("Comando invalido! Use 'e', 'd' ou 's'.\n");
        }
    }
}
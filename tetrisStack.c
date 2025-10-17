#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // Necessário para gerar peças aleatórias

// --- Documentação: Constantes Globais ---
// Define a capacidade máxima da nossa fila de peças futuras.
#define TAMANHO_FILA 5

// --- Documentação: Definição da Estrutura de Peça ---
// A struct 'Peca' é o nosso tipo de dado personalizado.
// Ela armazena os atributos essenciais de cada peça do Tetris.
// - nome: O caractere que representa o formato ('I', 'O', 'T', 'L').
// - id: Um número único para identificar a peça.
typedef struct {
    char nome;
    int id;
} Peca;

// --- Documentação: Estrutura da Fila Circular ---
// A 'FilaDePecas' gerencia o inventário de próximas peças.
// Ela contém o array de peças e os índices de controle.
// - inicio: Aponta para o primeiro item da fila (quem vai sair).
// - fim: Aponta para a próxima posição livre (onde vai entrar).
// - totalItens: Controla quantos itens estão atualmente na fila.
typedef struct {
    Peca pecas[TAMANHO_FILA];
    int inicio;
    int fim;
    int totalItens;
} FilaDePecas;

// --- Protótipos das Funções (Modularização) ---
void inicializarFila(FilaDePecas *fila);
void enqueue(FilaDePecas *fila);
void dequeue(FilaDePecas *fila);
void exibirFila(FilaDePecas *fila);
Peca gerarPeca();

/**
 * @brief Ponto de entrada principal do programa.
 */
int main() {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL)); 
    
    // --- Manutenibilidade: Nomes Descritivos ---
    FilaDePecas filaProximasPecas;
    int opcao = -1; // -1 para garantir que o loop inicie

    // --- Fluxo de Execução: Inicialização ---
    // O jogo começa já preenchendo a fila de próximas peças.
    inicializarFila(&filaProximasPecas);

    // O loop 'while' continua até que o jogador escolha a opção 0 (Sair).
    while (opcao != 0) {
        // --- Requisito Funcional: Exibir estado após cada ação ---
        // A fila é exibida no início de cada loop, mostrando o resultado
        // da ação anterior (ou o estado inicial).
        exibirFila(&filaProximasPecas);
        
        // --- Usabilidade: Menu Claro ---
        printf("\nOpcoes de acao:\n");
        printf("1. Jogar peca (dequeue)\n");
        printf("2. Inserir nova peca (enqueue)\n");
        printf("0. Sair\n");
        printf("Escolha sua acao: ");
        
        // --- Entrada de Dados: Validação Simples ---
        if (scanf("%d", &opcao) != 1) {
            // Se o usuário digitar algo que não é um número
            opcao = -1; // Força a entrada no 'default' do switch
        }
        // Limpa o buffer de entrada (ex: o 'Enter' após o número)
        while (getchar() != '\n'); 

        // --- Controle de Fluxo: switch-case ---
        // Direciona a ação do jogador para a função correspondente.
        switch (opcao) {
            case 1:
                dequeue(&filaProximasPecas);
                break;
            case 2:
                enqueue(&filaProximasPecas);
                break;
            case 0:
                printf("\nSaindo do Tetris Stack... Ate a proxima!\n");
                break;
            default:
                printf("\n[ERRO] Opcao invalida. Por favor, escolha 1, 2 ou 0.\n");
        }
    } // Fim do while

    return 0;
}

/**
 * @brief Gera uma nova peça aleatória com um ID único.
 * @return A nova Peca gerada.
 */
Peca gerarPeca() {
    // 'static' faz com que 'contadorId' preserve seu valor entre as chamadas
    // da função, garantindo que o ID seja sempre único.
    static int contadorId = 0; 
    
    Peca novaPeca;
    char tiposDePeca[] = {'I', 'O', 'T', 'L', 'S', 'Z', 'J'}; // Tipos de peça
    
    // Sorteia um tipo de peça
    novaPeca.nome = tiposDePeca[rand() % 7]; 
    
    // Atribui o ID único e incrementa o contador para a próxima
    novaPeca.id = contadorId;
    contadorId++;
    
    return novaPeca;
}

/**
 * @brief Inicializa a fila com 5 peças.
 * @param fila Ponteiro para a struct FilaDePecas.
 */
void inicializarFila(FilaDePecas *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->totalItens = 0;
    
    printf("Inicializando a fila de pecas do Tetris Stack...\n");
    
    // Preenche a fila com o número máximo de itens (5)
    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca p = gerarPeca();
        // Adiciona manualmente, pois 'enqueue' impediria (fila "cheia")
        fila->pecas[fila->fim] = p; 
        
        // --- Conceito: Fila Circular (Avanço de Índice) ---
        // O operador '%' (módulo) garante que, ao chegar em 5,
        // o índice volte para 0. (ex: (4 + 1) % 5 = 0)
        fila->fim = (fila->fim + 1) % TAMANHO_FILA;
        fila->totalItens++;
    }
}

/**
 * @brief Adiciona uma nova peça ao final da fila (se houver espaço).
 * @param fila Ponteiro para a struct FilaDePecas.
 */
void enqueue(FilaDePecas *fila) {
    // --- Conceito: Validação de Restrição (Fila Cheia) ---
    if (fila->totalItens == TAMANHO_FILA) {
        printf("\n[ERRO] A fila de proximas pecas esta cheia! Jogue uma peca primeiro.\n");
        return;
    }
    
    // Gera uma nova peça automaticamente
    Peca novaPeca = gerarPeca();
    
    // --- Conceito: Fila Circular (Inserção) ---
    // Adiciona a nova peça na posição 'fim' (próximo local vago).
    fila->pecas[fila->fim] = novaPeca;
    
    // Avança o índice 'fim' de forma circular.
    fila->fim = (fila->fim + 1) % TAMANHO_FILA;
    
    // Incrementa o contador de itens.
    fila->totalItens++;
    
    printf("\n[ACAO] Nova peca gerada (Tipo: %c, ID: %d) e adicionada ao final da fila.\n", novaPeca.nome, novaPeca.id);
}

/**
 * @brief Remove (joga) a peça da frente da fila.
 * @param fila Ponteiro para a struct FilaDePecas.
 */
void dequeue(FilaDePecas *fila) {
    // --- Conceito: Validação de Restrição (Fila Vazia) ---
    if (fila->totalItens == 0) {
        printf("\n[ERRO] A fila de pecas esta vazia! Nenhuma peca para jogar.\n");
        return;
    }

    // Pega a peça que está na frente da fila (para exibir)
    Peca pecaJogada = fila->pecas[fila->inicio];

    // --- Conceito: Fila Circular (Remoção) ---
    // A "remoção" é lógica: apenas avançamos o ponteiro 'inicio'
    // de forma circular. O dado antigo será sobrescrito se a fila encher.
    fila->inicio = (fila->inicio + 1) % TAMANHO_FILA;
    
    // Decrementa o contador de itens.
    fila->totalItens--;

    printf("\n[ACAO] Peca jogada (Tipo: %c, ID: %d) foi removida da frente da fila.\n", pecaJogada.nome, pecaJogada.id);
}

/**
 * @brief Exibe o estado atual da fila, da frente para o fim.
 * @param fila Ponteiro para a struct FilaDePecas.
 */
void exibirFila(FilaDePecas *fila) {
    // --- Usabilidade: Saída Clara (Exemplo da Saída) ---
    printf("\n--- Estado Atual da Fila de Pecas (%d/%d) ---", fila->totalItens, TAMANHO_FILA);
    printf("\nFila de pecas: ");

    if (fila->totalItens == 0) {
        printf("[ VAZIA ]\n");
    } else {
        // --- Conceito: Fila Circular (Leitura) ---
        // Precisamos iterar de 'inicio' até 'fim', mas de forma circular.
        // Usamos um índice 'i' temporário e o 'totalItens' para controlar o loop.
        int indiceAtual = fila->inicio;
        for (int i = 0; i < fila->totalItens; i++) {
            printf("[%c %d] ", fila->pecas[indiceAtual].nome, fila->pecas[indiceAtual].id);
            // Avança o índice de leitura de forma circular
            indiceAtual = (indiceAtual + 1) % TAMANHO_FILA;
        }
        printf("\n");
    }
    printf("----------------------------------------------\n");
}
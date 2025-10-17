Tetris Stack - Simulador de Fila de Peças
Este projeto é uma implementação em linguagem C de um sistema de fila de peças para um jogo fictício chamado "Tetris Stack". O objetivo principal é simular e gerenciar a "fila de peças futuras" que o jogador verá no jogo, utilizando uma estrutura de dados de Fila Circular para controle eficiente.

📜 Descrição do Projeto
No Tetris Stack, os jogadores precisam organizar peças que caem. Este programa foca em uma mecânica central: a fila de "próximas peças". O sistema permite ao jogador visualizar quais peças estão por vir, "jogar" a peça atual (removendo-a da frente da fila) e adicionar uma nova peça gerada automaticamente ao final da fila.

Este projeto é um exercício prático que aplica conceitos fundamentais de Estruturas de Dados em C, como structs e a lógica de uma Fila Circular (Queue).

✨ Funcionalidades
O sistema implementa as operações fundamentais de uma Fila (Queue):

dequeue (Jogar Peça): Remove a peça que está na frente da fila. Esta é a peça que o jogador usaria no jogo.

enqueue (Inserir Nova Peça): Adiciona uma nova peça, gerada automaticamente, ao final da fila, desde que haja espaço.

Exibir Fila: Mostra o estado atual de todas as peças na fila (nome e ID) após cada operação, permitindo ao jogador visualizar a ordem.

Inicialização Automática: O programa já começa com a fila preenchida com 5 peças iniciais.

📦 Estrutura de Dados: Fila Circular
Para gerenciar as peças, o projeto utiliza duas estruturas principais:

struct Peca: Define o formato de cada peça.

C

typedef struct {
    char nome; // Tipo da peça (ex: 'I', 'O', 'T', 'L')
    int id;   // Identificador numérico único
} Peca;
struct FilaDePecas: Implementa a Fila Circular.

C

typedef struct {
    Peca pecas[TAMANHO_FILA]; // Array que armazena as peças
    int inicio;                // Índice do primeiro item (frente)
    int fim;                   // Índice da próxima posição livre (final)
    int totalItens;            // Contador de itens atuais
} FilaDePecas;
A Fila Circular é usada para que o vetor de tamanho fixo (TAMANHO_FILA) possa ser reutilizado de forma eficiente. Quando os índices inicio ou fim chegam ao final do vetor, eles "dão a volta" para o começo (posição 0), evitando desperdício de espaço.

🛠️ Tecnologias Utilizadas
Linguagem: C

Bibliotecas Padrão:

stdio.h

stdlib.h

time.h (Para a geração aleatória de novas peças)

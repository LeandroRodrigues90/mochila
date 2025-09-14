#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constantes globais para o tamanho máximo dos buffers de leitura
#define MAX_NOME 30
#define MAX_TIPO 20
#define CAPACIDADE_INICIAL 10 // Capacidade inicial da mochila

// Molde da struct item 
struct Mochila {
    char *nome; // ponteiro para o nome
    char *tipo; // ponteiro para o tipo
    int quantidade;
};

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void listarItens(struct Mochila *estoque, int tamanho) {
    printf("\n--- Itens na Mochila ---\n");
    printf("==========================\n");
    if (tamanho == 0) {
        printf("Mochila vazia.\n");
    } else {
        for (int i = 0; i < tamanho; i++) {
            printf("Item %d:\n", i + 1); // Mostra o número do item (começando em 1)
            printf("  Nome: %s\n", estoque[i].nome);
            printf("  Tipo: %s\n", estoque[i].tipo);
            printf("  Quantidade: %d\n", estoque[i].quantidade);
            printf("--------------------------\n");
        }
    }
}


int main() {
    struct Mochila *estoque = NULL; // Ponteiro que apontará para nosso array de structs
    int tamanho = 0;                // Quantos produtos temos atualmente
    int capacidade = 0;             // Quanta memória já alocamos em nº de produtos
    int opcao;

    do {
        printf("\n=====================================\n");
        printf("--- Manipulando Itens na Mochila ---\n");
        printf("=====================================\n");
        // Mostrar tamanho e capacidade corretamente
        printf("Itens na mochila: %d / %d\n\n", tamanho, capacidade);
        printf("1- Adicionar Item na Mochila\n");
        printf("2- Remover Item da Mochila (Nao implementado)\n");
        printf("3- Listar Itens na Mochila\n");
        printf("0- Sair do sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limpar_buffer();

        switch (opcao) {
            case 1: { // Usar chaves para criar um escopo local para as variáveis
                // VERIFICAR SE TEMOS ESPAÇO. SE NÃO, ALOCAR MAIS.
                if (tamanho == capacidade) {
                    // Dobramos a capacidade atual. Se for a primeira vez, usamos a capacidade inicial.
                    capacidade = (capacidade == 0) ? CAPACIDADE_INICIAL : capacidade * 2;
                    
                    struct Mochila *temp = realloc(estoque, capacidade * sizeof(struct Mochila));
                    if (temp == NULL) {
                        printf("Erro ao alocar memoria!\n");
                        free(estoque); // Liberar o que já tinha antes de sair
                        return 1;
                    }
                    estoque = temp; // Atualiza o ponteiro para a nova área de memória
                    printf("---> (Info: Memoria realocada para %d itens)\n", capacidade);
                }

                // Buffers para ler a entrada do usuário
                char buffer_nome[MAX_NOME];
                char buffer_tipo[MAX_TIPO];
                int quantidade;

                printf("\n--- Inserir Item na Mochila ---\n");
                printf("=================================\n");

                printf("Digite o nome do item: ");
                // CORREÇÃO: Leitura segura para evitar overflow e ler espaços
                scanf("%29[^\n]", buffer_nome);
                limpar_buffer();

                printf("Digite o tipo do item (arma, pocao, etc.): ");
                scanf("%19[^\n]", buffer_tipo);
                limpar_buffer();

                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                limpar_buffer();

                // Alocar memória exata para os campos de texto do novo item
                estoque[tamanho].nome = malloc(strlen(buffer_nome) + 1); // +1 para o '\0'
                estoque[tamanho].tipo = malloc(strlen(buffer_tipo) + 1);

                if (estoque[tamanho].nome == NULL || estoque[tamanho].tipo == NULL) {
                    printf("Erro ao alocar memoria para os dados do item!\n");
                    // Aqui, a lógica de limpeza de memória seria mais complexa em um programa real
                    return 1;
                }
                
                // Copiar os dados dos buffers para a memória alocada
                strcpy(estoque[tamanho].nome, buffer_nome);
                strcpy(estoque[tamanho].tipo, buffer_tipo);
                estoque[tamanho].quantidade = quantidade;

                tamanho++; // Incrementar o número de itens na mochila

                printf("Item adicionado com sucesso!\n");
                break;
            }
            case 2:{
                if (tamanho == 0) {
                    printf("Mochila ja esta vazia. Nao ha itens para remover.\n");
                    break;
                }

                // 1. Mostra os itens para o usuário escolher qual remover
                listarItens(estoque, tamanho);

                printf("Digite o numero do item que deseja remover (1 a %d): ", tamanho);
                int item_para_remover;
                scanf("%d", &item_para_remover);
                limpar_buffer();

                // 2. Valida a entrada do usuário
                if (item_para_remover < 1 || item_para_remover > tamanho) {
                    printf("Numero de item invalido!\n");
                    break;
                }

                // Converte o número do item (ex: 1, 2, 3) para o índice do array (ex: 0, 1, 2)
                int indice = item_para_remover - 1;

                // 3. Libera a memória alocada para as strings do item que será removido
                printf("Removendo o item: %s...\n", estoque[indice].nome);
                free(estoque[indice].nome);
                free(estoque[indice].tipo);

                // 4. Desloca todos os elementos posteriores uma posição para a esquerda
                for (int i = indice; i < tamanho - 1; i++) {
                    estoque[i] = estoque[i + 1];
                }

                // 5. Atualiza o contador de itens
                tamanho--;

                printf("Item removido com sucesso!\n");
                break;
            }
            case 3: {
                printf("\n--- Itens na Mochila ---\n");
                printf("==========================\n");
                if (tamanho == 0) {
                    printf("Mochila vazia.\n");
                } else {
                    for (int i = 0; i < tamanho; i++) {
                        printf("Item %d:\n", i + 1);
                        printf("  Nome: %s\n", estoque[i].nome);
                        // CORREÇÃO: Acessar o campo 'tipo' corretamente
                        printf("  Tipo: %s\n", estoque[i].tipo);
                        printf("  Quantidade: %d\n", estoque[i].quantidade);
                        printf("--------------------------\n");
                    }
                }
                break;
            }
            case 0:
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    // Liberar toda a memória alocada antes de encerrar
    printf("Liberando memoria e saindo...\n");
    // Primeiro, liberamos a memória de cada string dentro das structs
    for (int i = 0; i < tamanho; i++) {
        free(estoque[i].nome);
        free(estoque[i].tipo);
    }
    // Por último, liberamos a memória do array de structs
    free(estoque);

    printf("Sistema encerrado.\n");

    return 0;
}
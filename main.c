#include <stdio.h>
#include <stdbool.h> // Para usar o tipo bool e os valores true/false
#include <ctype.h>   // Para usar a função tolower() na validação do 's'/'n'

/**
 * @brief Limpa o buffer de entrada do teclado.
 *
 * Essencial para evitar que leituras de caracteres (como 's'/'n') sejam afetadas
 * por caracteres de nova linha ('\n') deixados por leituras de números anteriores.
 * Também remove entradas inválidas (ex: texto quando um número é esperado).
 */
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Exibe o menu principal da calculadora.
 */
void exibirMenu() {
    printf("===============================\n");
    printf("   Calculadora Simples\n");
    printf("===============================\n");
    printf("Selecione uma operação:\n");
    printf("1. Adição\n");
    printf("2. Subtração\n");
    printf("3. Multiplicação\n");
    printf("4. Divisão\n");
    printf("5. Sair\n");
}

int main() {
    int opcao;
    double num1, num2, resultado;
    char operador;
    bool continuarExecutando = true;

    do {
        exibirMenu();
        
        // --- Validação da Opção do Menu ---
        printf("Opção: ");
        // Verifica se a entrada foi um número inteiro
        if (scanf("%d", &opcao) != 1) {
            printf("\nErro: Entrada inválida. Por favor, digite um número.\n\n");
            limparBufferEntrada();
            continue; // Pula para a próxima iteração do loop, mostrando o menu novamente
        }
        
        // Valida se a opção está no intervalo correto
        if (opcao < 1 || opcao > 5) {
            printf("\nErro: Opção inválida. Por favor, digite um número entre 1 e 5.\n\n");
            continue;
        }

        // --- Opção 5: Sair ---
        if (opcao == 5) {
            printf("\nObrigado por usar a calculadora! Até a próxima.\n");
            continuarExecutando = false;
            continue; // Finaliza o loop
        }

        // --- Solicitação dos Números para Operações 1 a 4 ---
        printf("Digite o primeiro número: ");
        // Validação simples para garantir que um número foi lido
        if (scanf("%lf", &num1) != 1) {
            printf("\nErro: Entrada inválida para o primeiro número.\n");
            limparBufferEntrada();
            continue;
        }

        printf("Digite o segundo número: ");
        if (scanf("%lf", &num2) != 1) {
            printf("\nErro: Entrada inválida para o segundo número.\n");
            limparBufferEntrada();
            continue;
        }

        // --- Realização do Cálculo ---
        switch (opcao) {
            case 1: // Adição
                operador = '+';
                resultado = num1 + num2;
                break;
            case 2: // Subtração
                operador = '-';
                resultado = num1 - num2;
                break;
            case 3: // Multiplicação
                operador = '*';
                resultado = num1 * num2;
                break;
            case 4: // Divisão
                // Tratamento de erro para divisão por zero
                if (num2 == 0) {
                    printf("\nErro: Divisão por zero não é permitida.\n");
                } else {
                    operador = '/';
                    resultado = num1 / num2;
                }
                break;
        }

        // Exibição do resultado (apenas se não for divisão por zero)
        if (opcao != 4 || num2 != 0) {
            // A formatação "%g" remove zeros desnecessários no final de números decimais
            printf("Resultado: %g %c %g = %g\n", num1, operador, num2, resultado);
        }

        // --- Perguntar sobre Nova Operação ---
        char resposta;
        while (true) {
            printf("\nDeseja realizar outra operação? (s/n): ");
            limparBufferEntrada(); // Limpa o '\n' deixado pelo scanf dos números
            scanf("%c", &resposta);

            resposta = tolower(resposta); // Converte para minúsculo para aceitar 'S' e 'N'

            if (resposta == 's') {
                printf("\n"); // Adiciona um espaço para o próximo menu
                break; // Sai do loop da pergunta e continua o loop principal
            } else if (resposta == 'n') {
                printf("\nObrigado por usar a calculadora! Até a próxima.\n");
                continuarExecutando = false;
                break; // Sai do loop da pergunta e termina o loop principal
            } else {
                printf("Resposta inválida. Por favor, digite 's' para sim ou 'n' para não.\n");
            }
        }

    } while (continuarExecutando);

    return 0;
}
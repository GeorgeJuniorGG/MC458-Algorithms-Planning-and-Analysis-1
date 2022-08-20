#include <stdio.h>
#include <stdlib.h>

double MaxSubsequence(double* sequence, int size, double keyNumbers[]) {
    // Lembrando que keyNumbers[0] = Subsequencia consecutiva maxima
    // E que keyNumbers[1] = Sufixo maximo
    // E que keyNumbers[2] = Sufixo minimo

    if(size == 1) {                                                     // Caso base
        if(sequence[0] < 1) {                                           // Subsequencia vazia eh o melhor caso
            keyNumbers[0] = 1;
            keyNumbers[1] = 1;
            keyNumbers[2] = sequence[0];
        }
        else {                                                          // Elemento da primeira posicao eh o melhor caso
            keyNumbers[0] = sequence[0];
            keyNumbers[1] = sequence[0];
            keyNumbers[2] = 1;
        }
    }
    else {
        MaxSubsequence(sequence, size - 1, keyNumbers);                 // Passo indutivo

        if(sequence[size - 1] > 0) {                                    // Quando o elemento atual eh positivo, temos um caso simples
            if (keyNumbers[1] > 1 && sequence[size - 1] > 1) {              // Caso em que o sufixo maximo atual eh o sufixo maximo anterior * o ultimo elemento atual      
                keyNumbers[1] = keyNumbers[1] * sequence[size - 1];
            }
            else if (sequence[size - 1] > 1) {                              // Caso em que o ultimo elemento atua eh o novo sufixo maximo
                keyNumbers[1] = sequence[size - 1];
            }
            else {                                                          // Caso em que o novo sufixo maximo eh vazio
                keyNumbers[1] = 1;
            }
            if (keyNumbers[2] * sequence[size - 1] < keyNumbers[2]) {       // Inclui o elemento atual no novo sufixo minimo se ele tornar o sufixo minimo anterior menor
                keyNumbers[2] = keyNumbers[2] * sequence[size - 1];
            }
            else {                                                          // Caso contrario, o novo sufixo minimo eh o proprio elemento atual
                keyNumbers[2] = sequence[size - 1];
            }
        }

        else if(sequence[size - 1] == 0) {                              // Quando o elemento atual eh zero, os casos sao mais simples
            keyNumbers[1] = 1;
            keyNumbers[2] = 0;
        }

        else {                                                          // Quando o elemento atual eh negativo, temos um caso especial
            double prevSMax = keyNumbers[1];

            if(keyNumbers[2] * sequence[size - 1] > keyNumbers[1]) {    // Caso o SMax aumente
                keyNumbers[1] = keyNumbers[2] * sequence[size - 1];
                if(prevSMax * sequence[size - 1] < keyNumbers[2]) {     // Verifica se o Smin incorpora o Smax anterior
                    keyNumbers[2] = prevSMax * sequence[size - 1];      // Se Smin incorporar
                }
                else {
                    keyNumbers[2] = sequence[size - 1];                 // Senao, Smin assume o valor do elemento atual
                }
            }
            else if(keyNumbers[1] * sequence[size - 1] < keyNumbers[2]) {   // Smax nao aumenta, Smin incorpora o Smax anterior
                keyNumbers[2] = keyNumbers[1] * sequence[size - 1];
                keyNumbers[1] = 1;
            }
            else {                                                          // Smax nao aumenta, Smin nao incorpora o Smax anterior
                keyNumbers[2] = sequence[size - 1];
                keyNumbers[1] = 1;
            }
        }

        if (keyNumbers[1] > keyNumbers[0]) {                            // Caso o novo sufixo seja maior do que a sequencia consecutiva maxima anterior, a SCM assume o valor da SM
            keyNumbers[0] = keyNumbers[1];
        }
    }

    return keyNumbers[0];                                               // Por conta do vetor keyNumbers, a saida so importa para a primeira chamada da funcao
}


int main()
{
    int n;
    scanf("%d", &n);                                                    // Leitura do numero de elementos

    double* sequence = malloc(n * sizeof(double));                      // Aloca o vetor que armazenara os elementos

    for (int i = 0; i < n; i++) {
        scanf("%lf", &sequence[i]);                                     // Leitura dos elementos
    }

    double maxSubsequence;                                              // Guarda o valor da subsequencia consecutiva maxima
    double keyNumbers[3];                                               // Vetor da seguinte forma: keyNumbers = [SCM, SMax, SMin]

    maxSubsequence = MaxSubsequence(sequence, n, keyNumbers);           // Calculo da subsequencia consecutiva maxima
    printf("%.6lf\n", maxSubsequence);

    free(sequence);                                                     // Desaloca a memoria do vetor
    return 0;
}
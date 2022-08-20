#include <stdio.h>
#include <stdlib.h>

void CountingSort(int* A, int* B, int n, int digit) {
    // Se fizessemos apenas o CountingSort, criariamos um vetor de tamanho n^2 e o algortimo seria O(n^2)
    
    int* count = calloc(n, sizeof(int));            // Aloca o vetor que contara a ocorrencia de cada numero, inicializado com count[i] = 0 para todo 0 <= i < n

    for (int i = 0; i < n; i++) {                   // Adiciona 1 na ocorrencia de cada valor possivel para um digito ([0, n-1])
        count[(A[i]/digit) % n] ++;
    }

    for (int i = 1; i < n; i++) {                   // Faz cada posicao count[i] armazenar as ocorrencias acumuladas dos valores de 0 a i
        count[i] = count[i] + count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {              // Percorre de forma decrescente, olhando apenas o primeiro ou o segundo digito (dependendo de digit)
        B[count[(A[i]/digit) % n] - 1] = A[i];      // Coloca o A[i] na posicao correta do vetor ordenado B, de acordo com o primeiro ou segundo digito, com base no numero de ocorrencias de numeros menores ou iguais a ele
        count[(A[i]/digit) % n] --;                 // Diminui em 1 a ocorrencia de numeros com primeiro ou segundo digito igual a (A[i]/digit) % n
    }
    free(count);                                    // Libera a memoria alocada
}

void RadixSort(int* A, int* B, int n) {
    // Um jeito de fazer essa ordenacao eh ordenar de forma que os numeros estejam em base n
    // Assim, sendo esses numeros de [0, n^2-1], o numero pode ter 1 digito, se for de [0, n-1], ou 2 digitos, se for de [n, n^2-1]

    CountingSort(A, B, n, 1);                       // Ordena pelo digito menos significativo (segundo) e guarda em B

    // Como CountingSort eh estavel, quando ele encontrar numeros com primeiros digitos iguais, ele vai manter a ordem que esses elementos ja estao no vetor
    // E como os segundos digitos ja foram ordenados, ele vai deixar esses numeros ordenados entre si

    CountingSort(B, A, n, n);                       // Ordena pelo digito mais significativo (primeiro) e guarda em A
}

int main () {
    int size;                                           // Leitura do tamanho do vetor de entrada
    scanf("%d", &size);

    int* input = malloc(size * sizeof(int));            // Alocando o vetor que guardara a entrada
    for (int i = 0; i < size - 1; i++) {                // Leitura dos n-1 primeiros elementos do vetor
        scanf("%d ", &input[i]);
    }
    scanf("%d", &input[size - 1]);                      // Leitura do ultimo elemento do vetor

    int* aux = malloc(size * sizeof(int));              // Alocando o vetor auxiliar

    RadixSort(input, aux, size);                        // Chama a funcao que ordenara o vetor em tempo linear

    for (int i = 0; i < size - 1; i++) {                // Imprime os n - 1 menores elementos da entrada, em ordem crescente
        printf("%d ", input[i]);
    }
    printf("%d\n", input[size - 1]);                    // Imprime o maior elemento da entrada

    free(input);                                        // Libera a memoria alocada
    free(aux);
    return 0;
}
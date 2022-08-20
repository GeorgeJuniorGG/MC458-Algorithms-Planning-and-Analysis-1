#include <stdio.h>
#include <stdlib.h>

void Merge(int* A, int* B, int p, int q, int r) {
    int n1 = q - p + 1;                                             // Limite do vetor esquerdo
    int n2 = r - q;                                                 // Limite do vetor direito

    int L[n1];                                                      // Vetores temporarios para elementos das metades direita e esquerda
    int R[n2];
    int Laux[n1];
    int Raux[n2];

    for (int i = 0; i < n1; i++) {                                  // Preenche os vetores da esquerda
        L[i] = A[p + i];
        Laux[i] = B[p + i];
    }
    for (int i = 0; i < n2; i++) {                                  // Preenche os vetores da direita
        R[i] = A[q + 1 + i];
        Raux[i] = B[q + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = p;

    while(i < n1 && j < n2) {                                       // Preenche os vetores na ordem certa, intercalando valores dos vetores R e L, conforme ordem crescente
        if(L[i] <= R[j]) {
            A[k] = L[i];
            B[k] = Laux[i];
            i++;
        }
        else {
            A[k] = R[j];
            B[k] = Raux[j];
            j++;
        }
        k++;
    }

    while(i < n1) {                                                 // Verifica se faltou adicionar algum elemento do vetor da esquerda
        A[k] = L[i];
        B[k] = Laux[i];
        i++;
        k++;
    }

    while(j < n2) {                                                 // Verifica se faltou adicionar algum elemento do vetor da direita
        A[k] = R[j];
        B[k] = Raux[j];
        j++;
        k++;
    }
 }

void MergeSort(int* A, int* B, int p, int r) {
    int q;                                                      // Algoritmo do Merge Sort adapdtado para conter o vetor Posicoes
    if (p < r) {
        q = (p + r)/2;
        MergeSort(A, B, p, q);
        MergeSort(A, B, q + 1, r);
        Merge(A, B, p, q, r);
    }
}

int main()
{
    int N;                                                      // Guarda o numero de tarefas

    scanf("%d", &N);                                            // Leitura do numero de tarefas

    int* P = malloc(N * sizeof(int));                           // Guarda o tempo de processamento das tarefas
    int* Posicoes = malloc(N * sizeof(int));                    // Guarda as posicoes nas quais as tarefas foram dadas

    for(int i = 0; i < N - 1; i++) {                            // Leitura do tempo de processamento de cada tarefa
        scanf("%d ", &P[i]);
        Posicoes[i] = i + 1;                                    // Guarda as posicoes nas quais as entradas foram dadas
    }
    scanf("%d", &P[N - 1]);
    Posicoes[N - 1] = N;

    int tempoTotal = 0;

    MergeSort(P, Posicoes, 0, N - 1);                           // Ordena o vetor P em O(nlogn), mexendo corretamente no vetor Posicoes para que seus elementos continuem indicando as posicoes nas quais as entradas foram dadas

    for(int i = 0; i < N - 1; i++) {                            // Calcula o tempo total de processamento na ultima posicao de P
        P[i + 1] += P[i];
    }

    for(int i = 0; i < N; i++) {
        tempoTotal += P[i];
    }

    printf("%d\n", tempoTotal);

    for(int i = 0; i < N - 1; i++) {                            // Imprime a ordem das tarefas que otimiza o problema, que ja foi corretamente calculada em Posicoes por meio do MergeSort
        printf("%d ", Posicoes[i]);
    }
    printf("%d\n", Posicoes[N - 1]);

    free(P);
    free(Posicoes);
    return 0;
}

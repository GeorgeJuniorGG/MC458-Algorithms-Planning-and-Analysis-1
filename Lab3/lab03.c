#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;                                              // Guarda o numero de colunas/linhas do tabuleiro

    scanf("%d", &n);

    int (*diag_direita)[n] = malloc(sizeof(int[n][n]));     // Tabela que guarda o preco dado na entrada, assumindo apenas movimentos para a diagonal direita
    int (*reto)[n] = malloc(sizeof(int[n][n]));             // Tabela que guarda o preco dado na entrada, assumindo apenas movimentos para a frente
    int (*diag_esquerda)[n] = malloc(sizeof(int[n][n]));    // Tabela que guarda o preco dado na entrada, assumindo apenas movimentos para a diagonal esquerda

    for (int i = 0; i < n; i++) {                           // Inicializa destinos impossiveis com preco impossivel
        diag_direita[0][i] = -1001;
        diag_direita[i][0] = -1001;

        reto[0][i] = -1001;

        diag_esquerda[0][i] = -1001;
        diag_esquerda[i][n - 1] = -1001;
    }

    int (*melhores_precos)[n] = malloc(sizeof(int[n][n]));      // Tabela que guardara os melhores precos possiveis para chegar ate cada posicao
    int (*melhores_posicoes)[n] = malloc(sizeof(int[n][n]));    // Tabela que guardara as melhores posicoes que maximizam o preco

    for (int i = 0; i < n; i++) {                               // Inicializando os precos das posicoes iniciais e as posicoes iniciais
        melhores_precos[0][i] = 0;
        melhores_posicoes[0][i] = -1;
    }

    int rx, cx, ry, cy, p;
    for (int i = 0; i < ((3*n - 2) * (n - 1)); i++) {           // Leitura das linhas, que guarda os precos nas tabelas corretas
        scanf("%d %d %d %d %d", &rx, &cx, &ry, &cy, &p);
        if (cx < cy) {
            diag_direita[ry][cy] = p;
        }
        else if (cx == cy) {
            reto[ry][cy] = p;
        }
        else if (cx > cy) {
            diag_esquerda[ry][cy] = p;
        }
    }

    for (int i = 1; i < n; i++) {                                                                                   // Calcula o melhor preco para cada posicao do tabuleiro, a partir da linha anterior, e guarda as colunas que levaram para cada linha obter o maior preco
        for (int j = 0; j < n; j++) {
            melhores_precos[i][j] = melhores_precos[i - 1][j] + reto[i][j];                                         // Comeca assumindo que o maior preco eh indo reto
            melhores_posicoes[i][j] = j;
            if (j > 0 && (diag_direita[i][j] + melhores_precos[i - 1][j - 1]) >= melhores_precos[i][j]) {           // Verifica se ir para a direita da um preco maior ou igual (igual pois seria indicativo de um caminho a partir de uma coluna mais a esquerda)
                melhores_precos[i][j] = diag_direita[i][j] + melhores_precos[i - 1][j - 1];
                melhores_posicoes[i][j] = j - 1;
            }
            if (j < (n - 1) && (diag_esquerda[i][j] + melhores_precos[i - 1][j + 1]) > melhores_precos[i][j]) {     // Verifica se ir para a esquerda da um preco maior
                melhores_precos[i][j] = diag_esquerda[i][j] + melhores_precos[i - 1][j + 1];
                melhores_posicoes[i][j] = j + 1;
            }
        }
    }
    int max = 0;
    for (int i = 0; i < n; i++) {                                                   // Verifica o maior preco possivel na ultima linha
        if (melhores_precos[n - 1][i] > melhores_precos[n - 1][max]) {
            max = i;
        }
    }

    printf("%d\n", melhores_precos[n - 1][max]);                                    // Imprime o maior preco para se cruzar o tabuleiro

    int pos[n];
    int aux = max;
    for (int i = n - 1; i > 0; i--) {                                               // Recupera a ordem das colunas que levaram ao maior preco e guarda em um vetor, de tras para frente
        pos[i - 1] = melhores_posicoes[i][aux];
        aux = pos[i - 1];
    }
    pos[n - 1] = max;

    for (int i = 0; i < n - 1; i++) {                                               // Imprime as colunas na ordem correta (da primeira linha ate a ultima)
        printf("%d ", pos[i]);
    }
    printf("%d\n", pos[n - 1]);

    free(diag_direita);                                         // Libera a memoria alocada
    free(reto);
    free(diag_esquerda);
    free(melhores_precos);
    free(melhores_posicoes);
    return 0;
}
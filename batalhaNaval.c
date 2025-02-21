#include <stdio.h>
#include <stdlib.h>

#define LINHAS 10
#define COLUNAS 10
#define HORIZONTAL 0
#define VERTICAL 1

void popularTabuleiro(int tabuleiro[LINHAS][COLUNAS]);
int validarPosicionamento(int navio[4], int tabuleiro[LINHAS][COLUNAS]);
int posicionarNavio(int navio[4], int tabuleiro[LINHAS][COLUNAS]);
void desenharTabuleiro(int tabuleiro[LINHAS][COLUNAS]);


char *msgErros[] = {
    "Coordenadas inválidas",
    "Tamanho do navio inválido",
    "Posição inválida",
};



int main() {
    int tabuleiro[LINHAS][COLUNAS];
    // x, y, tamanho, orientação horizontal = 0 vertical = 1
    int navio1[4] = {0, 0, 3, HORIZONTAL}; 
    int navio2[4] = {3, 4, 3, VERTICAL};

    popularTabuleiro(tabuleiro);
    posicionarNavio(navio1, tabuleiro);
    posicionarNavio(navio2, tabuleiro);
    desenharTabuleiro(tabuleiro);
    
    return 0;
}

void popularTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            tabuleiro[i][j] = 0;
}

int validarPosicionamento(int navio[4], int tabuleiro[LINHAS][COLUNAS]) {
    int x = navio[0];
    int y = navio[1];
    int tamanho = navio[2];
    int orientacao = navio[3];
    int casaOcupada;

    // verifica se as coordenadas são válidas
    if (x < 0 || x > LINHAS || y < 0 || y > COLUNAS)
        return 1;

    // verifica se o tamanho do navio é maior que o tabuleiro
    if (tamanho > LINHAS || tamanho > COLUNAS)
        return 2;

    // verifica se o navio está fora do tabuleiro
    if (COLUNAS - tamanho < 0 || LINHAS - tamanho < 0)
        return 3;

    // verifica se o navio está sobrepondo outro
    for (int contador = 0; contador < tamanho; contador++) {
        if (orientacao == HORIZONTAL)
            casaOcupada = tabuleiro[x][y + contador];
        else
            casaOcupada = tabuleiro[x + contador][y];

        if (casaOcupada) return 2;

    }


    return 0;

}


int posicionarNavio(int navio[4], int tabuleiro[LINHAS][COLUNAS]) {
    int x = navio[0];
    int y = navio[1];
    int tamanho = navio[2];
    int orientacao = navio[3];

    int erroPosicionamento = validarPosicionamento(navio, tabuleiro);
    if (erroPosicionamento)
        return erroPosicionamento;

    for (int contador = 0; contador < tamanho; contador++) {
        if (orientacao == HORIZONTAL)
            tabuleiro[x][y + contador] = tamanho;
        else
            tabuleiro[x + contador][y] = tamanho;

    }


    return 0;


}

void desenharTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    int casa;

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            casa = tabuleiro[i][j];
            printf("%d", casa);
            // insere um espaço como o separador entre as casas
            if (j < COLUNAS - 1)
                printf(" ");
            
        }

        printf("\n");
    }
}


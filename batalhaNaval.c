#include <stdio.h>

#define LINHAS 10
#define COLUNAS 10
#define HORIZONTAL 'H'
#define VERTICAL 'V'
#define DIAGONAL 'D'


void popularTabuleiro(int tabuleiro[LINHAS][COLUNAS]);
void inserirNavios(int *navios[4], int tabuleiro[LINHAS][COLUNAS]);
void desenharTabuleiro(int tabuleiro[LINHAS][COLUNAS]);
int posicionarNavio(int navio[4], int tabuleiro[LINHAS][COLUNAS]);
int validarPosicionamento(int navio[4], int tabuleiro[LINHAS][COLUNAS]);


char *mensagens[] = {
    "Coordenadas inválidas",
    "Tamanho inválido",
    "Posicionamento inválido"
};



int main() {
    int tabuleiro[LINHAS][COLUNAS];
    // x, y, tamanho, orientação horizontal = 0 vertical = 1
    int navio1[4] = {0, 0, 3, HORIZONTAL}; 
    int navio2[4] = {3, 4, 3, VERTICAL};
    int navio3[4] = {5, 3, 3, DIAGONAL};
    int navio4[4] = {0, 4, 3, -DIAGONAL};

    int *navios[4] = {navio1, navio2, navio3, navio4};

    popularTabuleiro(tabuleiro);
    inserirNavios(navios, tabuleiro);
    desenharTabuleiro(tabuleiro);
    
    return 0;
}


void popularTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++)
            tabuleiro[i][j] = 0;
}


void inserirNavios(int *navios[4], int tabuleiro[LINHAS][COLUNAS]) {
    int resultado;
    for (int indice = 0; indice < 4; indice++) {
        resultado = posicionarNavio(navios[indice], tabuleiro);

        if (resultado) {
            printf("[ERRO] Navio %d", indice + 1);
            printf(" %s\n", mensagens[resultado - 1]);
        }
            
        
    }
}


void desenharTabuleiro(int tabuleiro[LINHAS][COLUNAS]) {
    int casa;

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            casa = tabuleiro[i][j];
            if (casa) {
                printf("\033[31m");
                printf("%d", casa);
                printf("\033[m");
            } else
                printf("%d", casa);

            // insere um espaço como o separador entre as casas
            if (j < COLUNAS - 1)
                printf(" ");
            
        }

        printf("\n");
    }
}


int posicionarNavio(int navio[4], int tabuleiro[LINHAS][COLUNAS]) {
    int x = navio[0];
    int y = navio[1];
    int tamanho = navio[2];
    int orientacao = navio[3];

    int erroPosicionamento = validarPosicionamento(navio, tabuleiro);
    if (erroPosicionamento) return erroPosicionamento;

    for (int contador = 0; contador < tamanho; contador++) {
        if (orientacao == HORIZONTAL)
            tabuleiro[x][y + contador] = tamanho;

        else if (orientacao == VERTICAL)
            tabuleiro[x + contador][y] = tamanho;

        else if (orientacao == DIAGONAL)
            tabuleiro[x + contador][y + contador] = tamanho;

        else if (orientacao == -DIAGONAL)
            tabuleiro[x + contador][y - contador] = tamanho;

    }


    return 0;


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
        return 1;

    // verifica se o navio está sobrepondo outro
    for (int contador = 0; contador < tamanho; contador++) {
        if (orientacao == HORIZONTAL)
            casaOcupada = tabuleiro[x][y + contador];

        else if (orientacao == VERTICAL)
            casaOcupada = tabuleiro[x + contador][y];

        else if (orientacao == DIAGONAL)
            casaOcupada = tabuleiro[x + contador][y + contador];

        else if (orientacao == -DIAGONAL)
            casaOcupada = tabuleiro[x + contador][y - contador];

        else
            return 3;

        if (casaOcupada) return 2;

    }


    return 0;

}


#include <stdio.h>



#define TLINHAS 10
#define TCOLUNAS 10
#define HLINHAS 5
#define HCOLUNAS 5
#define TAMANHO_NAVIO 3

enum Formas {
    CONE,
    CRUZ,
    OCTAEDRO
};

enum Orientacoes {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL
};

enum EstadosSaida {
    SUCESSO,
    COORDENADA_INVALIDA,
    TAMANHO_INVALIDO,
    POSICIONAMENTO_INCORRETO
};


void inicializarCone(int matriz[HLINHAS][HCOLUNAS]);
void inicializarCruz(int matriz[HLINHAS][HCOLUNAS]);
void inicializarOctaedro(int matriz[HLINHAS][HCOLUNAS]);
void desenharTabuleiro(int tabuleiro[TLINHAS][TCOLUNAS]);
void posicionarNavio(int navio[4], int tabuleiro[TLINHAS][TCOLUNAS]);
void usarHabilidade(int habilidade[5], int tabuleiro[TLINHAS][TCOLUNAS]);
int validarPosicionamento(int navio[4], int tabuleiro[TLINHAS][TCOLUNAS]);


char *mensagens[] = {
    "Coordenadas inválidas",
    "Tamanho inválido",
    "Posicionamento inválido"
};

const int CENTRO_X = HCOLUNAS % 2 ? HCOLUNAS / 2 : HCOLUNAS / 2 - 1;
const int CENTRO_Y = HLINHAS % 2 ? HLINHAS / 2 : HLINHAS / 2 - 1;

int main() {
    int tabuleiro[TLINHAS][TCOLUNAS] = {0};

    //  navio[4] = {x, y, orientação}
    int navio1[3] = {4, 1, HORIZONTAL};
    int navio2[3] = {3, 0, VERTICAL};
    int navio3[3] = {0, 3, DIAGONAL};
    int navio4[3] = {7, 0, -DIAGONAL};

    // habilidade[4] = {x, y, forma}
    int habilidade1[3] = {2, 1, CONE};
    int habilidade2[3] = {7, 2, CRUZ};
    int habilidade3[3] = {2, 7, OCTAEDRO};

    posicionarNavio(navio1, tabuleiro);
    posicionarNavio(navio2, tabuleiro);

    usarHabilidade(habilidade1, tabuleiro);
    usarHabilidade(habilidade2, tabuleiro);
    usarHabilidade(habilidade3, tabuleiro);

    /*usarHabilidade(cone, tabuleiro);*/
    desenharTabuleiro(tabuleiro);
    
    return 0;
}


void usarHabilidade(int habilidade[3], int tabuleiro[TLINHAS][TCOLUNAS]) {
    // habilidade[4] = {x, y, forma}
    int x = habilidade[0];
    int y = habilidade[1];
    int forma = habilidade[2];
    int matriz[HLINHAS][HCOLUNAS] = {0};

    switch (forma) {
        case CONE: inicializarCone(matriz); break;
        case CRUZ: inicializarCruz(matriz); break;
        case OCTAEDRO: inicializarOctaedro(matriz); break;
    }


    int px = x - CENTRO_X;
    int py = forma == CONE ? y : y - CENTRO_Y;
                          
    // verifica se a habilidade está dentro do tabuleiro
    if (px < 0 || py < 0 || px + HCOLUNAS > TCOLUNAS || py + HLINHAS > TLINHAS) {
        return;
    }

    // posicionamento da habilidade no tabuleiro
    for (int i = 0; i < HLINHAS; i++) {
        for (int j = 0; j < HCOLUNAS; j++) {
            int areaAfetada = matriz[i][j];
            if (areaAfetada)
                tabuleiro[py + i][px + j] = areaAfetada * 5;
        }
    }



}




void inicializarCone(int matriz[HLINHAS][HCOLUNAS]) {
    for (int i = 0; i <= CENTRO_X; i++) {
        // desenha a coluna central
        matriz[i][2] = 1;
        for (int j = 1; j <= i; j++) {
            // desenha o lado direito
            matriz[i][CENTRO_X + j] = 1;
            // desenha o lado esquerdo
            matriz[i][CENTRO_X - j] = 1;
        }
    }

}

void inicializarCruz(int matriz[HLINHAS][HCOLUNAS]) {
    for (int i = 0; i < HLINHAS; i++) matriz[i][CENTRO_X] = 1;
    for (int i = 0; i < HCOLUNAS; i++) matriz[CENTRO_Y][i] = 1;
}

void inicializarOctaedro(int matriz[HLINHAS][HCOLUNAS]) {
    int aresta = CENTRO_Y < CENTRO_X ? CENTRO_Y : CENTRO_X;

    for (int i = 0; i <= aresta; i++) {
        for (int j = 0; j < aresta + 1 - i; j++) {
             // desenha as linhas inferiores
             matriz[CENTRO_Y + i][CENTRO_X + j] = 1;
             matriz[CENTRO_Y + i][CENTRO_X - j] = 1;
            
            // aviso: na primeira iteração a linha central é repetida!
            // desenha as linhas superiores
             matriz[CENTRO_Y - i][CENTRO_X + j] = 1;
             matriz[CENTRO_Y - i][CENTRO_X - j] = 1;

        }
    }
}



void desenharTabuleiro(int tabuleiro[TLINHAS][TCOLUNAS]) {
    int casa;

    for (int i = 0; i < TLINHAS; i++) {
        for (int j = 0; j < TCOLUNAS; j++) {
            casa = tabuleiro[i][j];
            if (casa == 5) {
                printf("\033[31m");
            } else if (casa == 3){
                printf("\033[36m");
            }
            printf("%d", casa);

            printf("\033[m");

            // insere um espaço como o separador entre as casas
            if (j < TCOLUNAS - 1)
                printf(" ");
        }

        printf("\n");
    }
}

void calcularDeslocamentos(int *dx, int *dy, int orientacao) {
    switch (orientacao) {
        case HORIZONTAL:
            *dy = 1;
            break;
        case VERTICAL:
            *dx = 1;
            break;
        case DIAGONAL:
            *dx = *dy = 1;
            break;
        case -DIAGONAL:
            *dx = 1; *dy = -1;
            break;
    }
}

void posicionarNavio(int navio[3], int tabuleiro[TLINHAS][TCOLUNAS]) {
    int x = navio[0];
    int y = navio[1];
    int orientacao = navio[2];


    int erro = validarPosicionamento(navio, tabuleiro);

    if (erro) {
        printf("[ERRO] %s\n", mensagens[erro - 1]);
        return;
    }

    int dx = 0, dy = 0;
    calcularDeslocamentos(&dx, &dy, orientacao);

    for (int i = 0; i < TAMANHO_NAVIO; i++)
        tabuleiro[y + dx * i][x + dy * i] = TAMANHO_NAVIO;
}


int validarPosicionamento(int navio[3], int tabuleiro[TLINHAS][TCOLUNAS]) {
    int x = navio[0];
    int y = navio[1];
    int orientacao = navio[2];
    int dx = 0, dy = 0;
    int casaOcupada;

    // verifica se as coordenadas são válidas
    if (x < 0 || x > TCOLUNAS || y < 0 || y > TLINHAS)
        return COORDENADA_INVALIDA;

    // verifica se o tamanho do navio é maior que o tabuleiro
    if (TAMANHO_NAVIO > TLINHAS || TAMANHO_NAVIO > TCOLUNAS)
        return TAMANHO_INVALIDO;

    // verifica se o navio está fora do tabuleiro
    //
    //
    calcularDeslocamentos(&dx, &dy, orientacao);

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        casaOcupada = tabuleiro[y + dx * i][x + dy * i];
        if (casaOcupada) return COORDENADA_INVALIDA;
    }

    return SUCESSO;

}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 10 // Tamanho do tabuleiro (10x10)
#define AGUA '~'   // Símbolo para água
#define NAVIO 'N'  // Símbolo para navio
#define EFEITO 'X' // Símbolo para área de efeito

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    printf("  ");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se uma posição é válida
int posicaoValida(int x, int y) {
    return (x >= 0 && x < TAMANHO && y >= 0 && y < TAMANHO);
}

// Função para posicionar um navio horizontalmente
void posicionarNavioHorizontal(char tabuleiro[TAMANHO][TAMANHO], int x, int y, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (posicaoValida(x, y + i)) {
            tabuleiro[x][y + i] = NAVIO;
        }
    }
}

// Função para posicionar um navio verticalmente
void posicionarNavioVertical(char tabuleiro[TAMANHO][TAMANHO], int x, int y, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (posicaoValida(x + i, y)) {
            tabuleiro[x + i][y] = NAVIO;
        }
    }
}

// Função para posicionar um navio diagonalmente
void posicionarNavioDiagonal(char tabuleiro[TAMANHO][TAMANHO], int x, int y, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (posicaoValida(x + i, y + i)) {
            tabuleiro[x + i][y + i] = NAVIO;
        }
    }
}

// Função para aplicar habilidade especial em forma de cruz
void habilidadeCruz(char tabuleiro[TAMANHO][TAMANHO], int x, int y, int alcance) {
    // Marcar o centro
    if (posicaoValida(x, y)) {
        tabuleiro[x][y] = EFEITO;
    }
    
    // Marcar nas quatro direções
    for (int i = 1; i <= alcance; i++) {
        // Cima
        if (posicaoValida(x - i, y)) {
            tabuleiro[x - i][y] = EFEITO;
        }
        // Baixo
        if (posicaoValida(x + i, y)) {
            tabuleiro[x + i][y] = EFEITO;
        }
        // Esquerda
        if (posicaoValida(x, y - i)) {
            tabuleiro[x][y - i] = EFEITO;
        }
        // Direita
        if (posicaoValida(x, y + i)) {
            tabuleiro[x][y + i] = EFEITO;
        }
    }
}

// Função para aplicar habilidade especial em forma de cone
void habilidadeCone(char tabuleiro[TAMANHO][TAMANHO], int x, int y, int alcance, int direcao) {
    // direcao: 0=cima, 1=direita, 2=baixo, 3=esquerda
    
    // Marcar o centro
    if (posicaoValida(x, y)) {
        tabuleiro[x][y] = EFEITO;
    }
    
    for (int i = 1; i <= alcance; i++) {
        for (int j = -i; j <= i; j++) {
            int novoX = x;
            int novoY = y;
            
            switch (direcao) {
                case 0: // Cone para cima
                    novoX = x - i;
                    novoY = y + j;
                    break;
                case 1: // Cone para direita
                    novoX = x + j;
                    novoY = y + i;
                    break;
                case 2: // Cone para baixo
                    novoX = x + i;
                    novoY = y + j;
                    break;
                case 3: // Cone para esquerda
                    novoX = x + j;
                    novoY = y - i;
                    break;
            }
            
            if (posicaoValida(novoX, novoY)) {
                tabuleiro[novoX][novoY] = EFEITO;
            }
        }
    }
}

// Função para aplicar habilidade especial em forma de octaedro (todas as direções)
void habilidadeOctaedro(char tabuleiro[TAMANHO][TAMANHO], int x, int y, int alcance) {
    for (int i = -alcance; i <= alcance; i++) {
        for (int j = -alcance; j <= alcance; j++) {
            // Verifica se está dentro do alcance do octaedro (distância de Manhattan)
            if (abs(i) + abs(j) <= alcance) {
                if (posicaoValida(x + i, y + j)) {
                    tabuleiro[x + i][y + j] = EFEITO;
                }
            }
        }
    }
}

int main() {
    char tabuleiro[TAMANHO][TAMANHO];
    
    // Inicializar o gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializar o tabuleiro
    inicializarTabuleiro(tabuleiro);
    
    printf("=== BATALHA NAVAL - OCEANIC GAMES ===\n\n");
    
    printf("Tabuleiro inicial:\n");
    exibirTabuleiro(tabuleiro);
    printf("\n");
    
    // Posicionar navios
    printf("Posicionando navios...\n");
    posicionarNavioHorizontal(tabuleiro, 2, 3, 4); // Navio de tamanho 4 na horizontal
    posicionarNavioVertical(tabuleiro, 5, 7, 3);   // Navio de tamanho 3 na vertical
    posicionarNavioDiagonal(tabuleiro, 1, 1, 3);   // Navio de tamanho 3 na diagonal
    
    printf("Tabuleiro com navios:\n");
    exibirTabuleiro(tabuleiro);
    printf("\n");
    
    // Demonstrar habilidades especiais
    printf("Demonstração de habilidades especiais:\n\n");
    
    // Cópia do tabuleiro para demonstrar habilidade Cruz
    char tabuleiroHabilidade1[TAMANHO][TAMANHO];
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiroHabilidade1[i][j] = tabuleiro[i][j];
        }
    }
    
    printf("1. Habilidade Cruz (alcance 2) na posição (4,4):\n");
    habilidadeCruz(tabuleiroHabilidade1, 4, 4, 2);
    exibirTabuleiro(tabuleiroHabilidade1);
    printf("\n");
    
    // Cópia do tabuleiro para demonstrar habilidade Cone
    char tabuleiroHabilidade2[TAMANHO][TAMANHO];
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiroHabilidade2[i][j] = tabuleiro[i][j];
        }
    }
    
    printf("2. Habilidade Cone (alcance 3) na posição (5,5) direção direita:\n");
    habilidadeCone(tabuleiroHabilidade2, 5, 5, 3, 1);
    exibirTabuleiro(tabuleiroHabilidade2);
    printf("\n");
    
    // Cópia do tabuleiro para demonstrar habilidade Octaedro
    char tabuleiroHabilidade3[TAMANHO][TAMANHO];
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiroHabilidade3[i][j] = tabuleiro[i][j];
        }
    }
    
    printf("3. Habilidade Octaedro (alcance 2) na posição (7,7):\n");
    habilidadeOctaedro(tabuleiroHabilidade3, 7, 7, 2);
    exibirTabuleiro(tabuleiroHabilidade3);
    
    return 0;
}
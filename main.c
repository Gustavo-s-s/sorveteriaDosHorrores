#include <math.h>
#include <string.h>		// para usar strings
#include "include/SOIL.h"

// Rotinas para acesso da OpenGL
#include "opengl.h"

// Variáveis globais a serem utilizadas:
typedef struct
{
    int quantidadeIgual;
    RGB8 cor;
} Cell;

// Dimensões da imagem de entrada
int sizeX, sizeY;

// Imagem de entrada
Image24 pic;

// Imagem de 8 bits
Image8 pic8;

// Modo de exibição atual
int modo;

// Protótipos
void load(char* name, Image24* pic);
void process();

int calcDistance(RGB8 color, RGB8 comparator)
{
    int squeredDeltaR = pow((color.r - comparator.r), 2);
    int squeredDeltaG = pow((color.g - comparator.g), 2);
    int squeredDeltaB = pow((color.b - comparator.b), 2);

    int cate = squeredDeltaR + squeredDeltaG + squeredDeltaB;
    return sqrt(cate);
}

int findIndexOfLessDistance(Cell *source, int size, RGB8 target)
{
    int indexOflessDistance = 0;
    for (int i = 1; i < size; i++)
    {
        int firstDist = calcDistance(target, source[indexOflessDistance].cor);
        int secondDist = calcDistance(target, source[i].cor);

        if (firstDist > secondDist)
            indexOflessDistance = i;
    }
    return indexOflessDistance;
}

int containsCell(Cell *source, int size, RGB8 target)
{
    for (int i = 0; i < size; i++)
    {
        char r = source[i].cor.r;
        char g = source[i].cor.g;
        char b = source[i].cor.b;

        if (target.r == r && target.g == g && target.b == b)
            return i;
    }

    return -1;
}

Cell *filter(Cell *source, int size, int quantidadeDeCores)
{
    Cell *cells = malloc(sizeof(Cell) * quantidadeDeCores);

    for (int i = 0; i < size; i++)
    {
        const int quant = source[i].quantidadeIgual;

        if (i < quantidadeDeCores)
        {
            cells[i] = source[i];
        }
        else
        {
            int index = findIndexOfLessDistance(cells, quantidadeDeCores, source[i].cor);

            if (quant > cells[index].quantidadeIgual)
            {
                cells[index] = source[i];
            }
        }
    }

    return cells;
}

// Carrega uma imagem para a struct Img
void load(char* name, Image24* pic)
{
    int chan;
    pic->pixels = (RGB8*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->pixels)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
}

// Função principal de processamento: ela deve chamar outras funções
// quando for necessário
void process()
{
    //
    // EXEMPLO: preenche a imagem 8 bits com pixels de cores diversas
    //
    //
    // SUBSTITUA este código pelos algoritmos a serem implementados
    //

    // Exemplo: imagem de 8 bits (com outras cores, para testar)
 

    //
    // NÃO ALTERAR A PARTIR DAQUI!!!!
    //
    buildTex();
}

int main(int argc, char** argv)
{
    if(argc==1) {
        printf("colors [image file]\n");
        exit(1);
    }

    // Inicialização da janela gráfica
    init(argc,argv);

    load(argv[1], &pic);
    sizeX = pic.width;
    sizeY = pic.height;

    // Aloca memória para imagem de 8 bits
    pic8.width  = sizeX;
    pic8.height = sizeY;
    pic8.pixels = (unsigned char*) malloc(sizeX * sizeY);

    modo = IMG24;

    // Aplica processamento inicial
    process();

    // Não retorna... a partir daqui, interação via teclado e mouse apenas, na janela gráfica
    glutMainLoop();
    return 0;
}

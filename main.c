#include <math.h>
#include <string.h> // para usar strings
#include "include/SOIL.h"

// Rotinas para acesso da OpenGL
#include "opengl.h"

// Variáveis globais a serem utilizadas:
typedef struct
{
    int quantity;
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
void load(char *name, Image24 *pic);
void process();

Cell createNewCell(RGB8 color)
{
    Cell cell = {0, color};
    return cell;
}

double calcDistance(RGB8 color, RGB8 comparator)
{
    double squeredDeltaR = pow((color.r - comparator.r), 2);
    double squeredDeltaG = pow((color.g - comparator.g), 2);
    double squeredDeltaB = pow((color.b - comparator.b), 2);

    double cate = squeredDeltaR + squeredDeltaG + squeredDeltaB;
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

void loadPall(Cell *colors, int size)
{
    for (int i = 0; i < size; i++)
        pic8.pal[i] = colors[i].cor;
}

void generateNewImage(Cell *cells, int quantidadeDeCores)
{
    for (int i = 0; i < sizeX * sizeY; i++)
        pic8.pixels[i] = findIndexOfLessDistance(cells, quantidadeDeCores, pic.pixels[i]);
}

int indexOfCellWithTolerance(Cell *source, int size, RGB8 target, int tolerace)
{
    for (int i = 0; i < size; i++) 
        if (calcDistance(source[i].cor, target) < tolerace)
            return i;

    return -1;
}

// filtra cores mais populares
void *filterByHighPopularity(Cell *source, int size, int newSizeOfSource)
{
    Cell *cells = malloc(sizeof(Cell) * newSizeOfSource);

    for (int i = 0; i < size; i++)
    {
        const int QUANTITY = source[i].quantity;

        if (i < newSizeOfSource)
        {
            cells[i] = source[i];
            continue;
        }

        int index = 0;
        for (int j = 0; j < newSizeOfSource; j++)
            if (cells[index].quantity < cells[j].quantity)
                index = j;

        if (QUANTITY > cells[index].quantity)
            cells[index] = source[i];
    }

    source = cells;
}



// agrupa as cores por uma determinada proximidade (tolerance)
Cell *groupingByCloserColor(RGB8 *colors, int size, int tolerance, int *newSize)
{
    Cell *cells = malloc(sizeof(Cell) * (sizeX * sizeY));
    int sizeOfCells = 0;

    for (int i = 0; i < size; i++)
    {
        if (i == 0)
        {
            cells[sizeOfCells++] = createNewCell(colors[i]);
            continue;
        }

        int cellIndex = indexOfCellWithTolerance(cells, sizeOfCells, colors[i], tolerance);
        if (cellIndex < 0)
            cells[sizeOfCells++] = createNewCell(colors[i]);
        else
            cells[cellIndex].quantity++;
    }

    *newSize = sizeOfCells;
    return cells;
}



// Carrega uma imagem para a struct Img
void load(char *name, Image24 *pic)
{
    int chan;
    pic->pixels = (RGB8 *)SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if (!pic->pixels)
    {
        printf("SOIL loading error: '%s'\n", SOIL_last_result());
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
    const int QUANTITY_OF_UNIQUE_COLORS = 256;
    const int TOLERANCE = 24;
    const int TOTAL_SIZE_OF_IMAGE = sizeX * sizeY;
    int size;

    Cell *cells = groupingByCloserColor(pic.pixels, TOTAL_SIZE_OF_IMAGE, TOLERANCE, &size);
    filterByHighPopularity(cells, size, QUANTITY_OF_UNIQUE_COLORS);
    loadPall(cells, QUANTITY_OF_UNIQUE_COLORS);
    generateNewImage(cells, QUANTITY_OF_UNIQUE_COLORS);

    // Exemplo: imagem de 8 bits (com outras cores, para testar)
    //
    // NÃO ALTERAR A PARTIR DAQUI!!!!
    //
    buildTex();
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        printf("colors [image file]\n");
        exit(1);
    }

    // Inicialização da janela gráfica
    init(argc, argv);

    load(argv[1], &pic);
    sizeX = pic.width;
    sizeY = pic.height;

    // Aloca memória para imagem de 8 bits
    pic8.width = sizeX;
    pic8.height = sizeY;
    pic8.pixels = (unsigned char *)malloc(sizeX * sizeY);

    modo = IMG24;

    // Aplica processamento inicial
    process();

    // Não retorna... a partir daqui, interação via teclado e mouse apenas, na janela gráfica
    glutMainLoop();
    return 0;
}

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
    unsigned int pos = 0;
    unsigned char r = 0;
    for(int y=0; y<sizeY; y++) {
        if (y>sizeY/4)
            r = 1;
        if (y>sizeY/2)
            r = 2;
        if (y>sizeY-sizeY/4)
        {
            r = 3;
        }
        for(int x=0; x<sizeX; x++) {
            pic8.pixels[pos] = r;
            pos++;
        }
    }
    // Exemplo: imagem de 8 bits (com outras cores, para testar)
    pic8.pal[0].r = 200;
    pic8.pal[0].g = 0;
    pic8.pal[0].b = 0;
    pic8.pal[1].r = 0;
    pic8.pal[1].g = 200;
    pic8.pal[1].b = 0;
    pic8.pal[2].r = 0;
    pic8.pal[2].g = 0;
    pic8.pal[2].b = 200;
    pic8.pal[3].r = 200;
    pic8.pal[3].g = 120;
    pic8.pal[3].b = 0;

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

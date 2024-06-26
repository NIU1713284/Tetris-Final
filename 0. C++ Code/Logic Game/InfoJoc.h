#ifndef INFO_JOC_H
#define INFO_JOC_H

const int N_TIPUS_FIGURES = 7;

typedef enum
{
    ESQUERRA = 0,
    DRETA = 1,
    GIR_HORARI_1 = 2,
    GIR_ANTI = 3,
    BAIXA_UNA = 4,
    BAIXA_FINAL = 5,
} TipusTecla;

typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;

typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S
} TipusFigura;

typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

typedef struct
{
    TipusFigura tipus;
    int fila;
    int columna;
    int girar;

} DadesFigura;

// Tamany de la pantalla gr�fica
const int SCREEN_SIZE_X = 600;
const int SCREEN_SIZE_Y = 700;

// Mida dels quadrats que formen el tauler
const int MIDA_QUADRAT = 26;

// Tamany del tauler
const int N_FILES_TAULER = 21;
const int N_COL_TAULER = 11;

// Posici� del tauler a la pantalla
const int POS_X_TAULER = 120;
const int POS_Y_TAULER = 100;

//Puntuacio jugador
const int POS_X_PUNTS = 120;
const int POS_Y_PUNTS = 50;

//Nivell dificultat
const int POS_X_NIVELL = 300;
const int POS_Y_NIVELL = 50;

//Game over
const int POS_X_GAME = 120;
const int POS_Y_GAME = 300;

void dibuixPlantilla(ColorFigura color, int x, int y);

#endif
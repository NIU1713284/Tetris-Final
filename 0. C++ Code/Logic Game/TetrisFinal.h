#ifndef TETRIS_H
#define TETRIS_H

#define SDL_MAIN_HANDLED

#include <list>
#include <fstream>
#include <iostream>
#include "Partida.h"
#include "../Graphic Lib/libreria.h"

using namespace std;

struct Puntuacio {
    string nom;
    int punts;
};

class Tetris {
public:
    Tetris(const string& fitxerPuntuacions);
    int juga(Screen& pantalla, ModeJoc mode, const string& nomFitxerInicial, const string& nomFitxerFigures, const string& nomFitxerMoviments);
    void actualitzaPuntuacio(const string& nom, int punts);
    void visualitzaPuntuacions();
    void guardaPuntuacions(const string& nomFitxer);

private:
    Partida m_partida;
    list<Puntuacio> m_puntuacions;
};

#endif

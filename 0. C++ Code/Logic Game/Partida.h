#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include <ctime>
#include "Joc.h"
#include "InfoJoc.h"
#include "LListaEspera.h"
#include "RegistreMoviment.h"

using namespace std;

// Ajustes joc
const int PUJAR_NIVELL = 200;
const double VELOCITAT = 1.0;
const double INC_VELOCITAT = 0.50;

//Punts per fila completadad
const int PP_FIGURA = 10;
const int P_1FIL = 100;
const int P_2FIL = 50;
const int P_3FIL = 75;
const int P_4FIL = 120;

typedef enum
{
    MODE_NORMAL,
    MODE_PROVA
} ModeJoc;


class Partida 
{
public:
    Partida() : m_mode(MODE_NORMAL), m_temps(0.0), m_punts(0), m_nivell(1), m_velocitat(VELOCITAT), m_final(false) {
        srand(time(0));
    }
    Partida(ModeJoc mode) : m_mode(mode), m_temps(0.0), m_punts(0), m_nivell(1), m_velocitat(VELOCITAT), m_final(false) {
        srand(time(0));
    }
    void inicialitza(const string& Fitxer1, const string& Fitxer2, const string& Fitxer3);
    int GetPuntuacio() const { return m_punts; }
    void actualitza(float deltaTime);

private:
    Joc m_joc;
    double m_temps;
    ModeJoc m_mode;
    int m_punts;
    int m_nivell;
    double m_velocitat;
    bool m_final;

    LlistaEspera m_figures;
    RegistreDesplac m_desplas;

    void inicialitzaDesplas(const string& Nfitxer);
    void inicialitzaFig(const string& nomFitxer);

    void canviaNormal(float deltaTime);
    void canviaProva(float deltaTime);
    void actualitzar(int eliminaFiles);
};

#endif 

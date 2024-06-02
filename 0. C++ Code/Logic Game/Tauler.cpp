#include <iostream>
#include "Tauler.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
using namespace std;

Tauler::Tauler() //Creem el tauler amb fons negre i parets incolores
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL + 4; j++)
        {
            if (j < 2 || j >= MAX_COL + 2)
                m_tauler[i][j] = NO_COLOR;
            else
                m_tauler[i][j] = COLOR_NEGRE;
        }
        m_lliures[i] = MAX_COL;
    }
}

Tauler::~Tauler()
{
    //Destructor
}

void Tauler::inicialitza(ColorFigura taulerInicial[MAX_FILA][MAX_COL]) //Guardem l'informació del tauler quantes caselles hi ha lliures "negres"
{
    for (int i = 0; i < MAX_FILA; ++i)
    {
        m_lliures[i] = MAX_COL;
        for (int j = 0; j < MAX_COL; ++j)
        {
            m_tauler[i][j + 2] = taulerInicial[i][j];
            if (taulerInicial[i][j] != COLOR_NEGRE)
                --m_lliures[i];
        }
    }
}

bool Tauler::confrontacioFigures(const Figura& figura) //Mirem si hi ha alguna casella ocupada mitjançant la mascara
{
    int mascara[MAX_ALCADA][MAX_AMPLADA];
    figura.getMascara(mascara);

    for (int filaMascara = 0; filaMascara < figura.getAltura(); ++filaMascara)
    {
        int filaTauler = figura.getFila() + filaMascara - 1;
        for (int colMascara = 0; colMascara < figura.getAmplada(); ++colMascara)
        {
            int colTauler = figura.getColumna() + colMascara + 1;
            if (mascara[filaMascara][colMascara] != 0 && m_tauler[filaTauler][colTauler] != COLOR_NEGRE)
            {
                return true;
            }
        }
    }
    return false;

}

int Tauler::posicioFigura(const Figura& figura) //Mirem si hi ha alguna fila plena en cas que sí, movem tot el taulell cap abaix
{
    int mascara[MAX_ALCADA][MAX_AMPLADA];
    int numFilesFetes = 0;

    ColorFigura color = figura.getColor();
    figura.getMascara(mascara);

    for (int filaMascara = 0; filaMascara < figura.getAltura(); ++filaMascara)
    {
        int filaTauler = figura.getFila() + filaMascara - 1;
        int colTauler = figura.getColumna() + 1;

        for (int colMascara = 0; colMascara < figura.getAmplada(); ++colMascara)
        {
            if (mascara[filaMascara][colMascara] != 0)
            {
                m_tauler[filaTauler][colTauler] = color;
                m_lliures[filaTauler]--;
                if (m_lliures[filaTauler] == 0)
                {
                    ++numFilesFetes;
                    destruirFila(filaTauler);
                }
            }
            ++colTauler;
        }
    }
    return numFilesFetes;
}


void Tauler::printFigura(const Figura& figura) //Dibuixem la figura en el tauler "No mirem si hi ha alguna casella ocupada, ho donem per suposat que ja ho hem mirat"
{
    int mascara[MAX_ALCADA][MAX_AMPLADA], colT;
    figura.getMascara(mascara);

    ColorFigura color = figura.getColor();
    int filaTauler = figura.getFila() - 1;

    for (int i = 0; i < figura.getAltura(); ++i)
    {
        colT = figura.getColumna() + 1;
        for (int j = 0; j < figura.getAmplada(); ++j)
        {
            if (mascara[i][j] != 0)
            {
                m_tauler[filaTauler][colT] = color;
            }
            ++colT;
        }
        ++filaTauler;
    }
}

void Tauler::destruirFila(int fila) //movem tot el tauler cap abaix una fila "destruim la fila" en cas que sigui una superior la pintem negre
{
    if (fila > 0)
    {
        for (int i = fila; i > 0; --i)
        {
            for (int j = 0; j < MAX_COL; ++j)
            {
                m_tauler[i][j + 2] = m_tauler[i - 1][j + 2];
            }
            m_lliures[i] = m_lliures[i - 1];
        }
    }

    for (int i = 0; i < MAX_COL; ++i)
    {
        m_tauler[0][i + 2] = COLOR_NEGRE;
    }
    m_lliures[0] = MAX_COL;
}

void Tauler::getValorsTauler(ColorFigura tauler[MAX_FILA][MAX_COL]) //Guardem l'informació del tauler per passar-la com a parametre en el futur
{
    for (int i = 0; i < MAX_FILA; ++i)
    {
        for (int j = 0; j < MAX_COL; ++j)
        {
            tauler[i][j] = m_tauler[i][j + 2];
        }
    }
}

void Tauler::representa()
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);
    for (int i = 0; i < MAX_AMPLADA; i++)
    {
        for (int j = 0; j < MAX_ALCADA; j++)
        {
            if (m_tauler[i][j + 2] != COLOR_NEGRE)
            {
                dibuixPlantilla(m_tauler[i][j + 2], POS_X_TAULER + ((j + 1) * MIDA_QUADRAT), POS_Y_TAULER + (1 * MIDA_QUADRAT));
            }
        }
    }
}
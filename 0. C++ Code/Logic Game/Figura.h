#ifndef FIGURA_H
#define FIGURA_H

#include "InfoJoc.h"

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

class Figura
{
public:
    Figura() : m_tipus(NO_FIGURA), m_color(NO_COLOR), m_amplada(MAX_AMPLADA), m_altura(MAX_ALCADA), m_fila(0), m_columna(0), m_girar(0) { reiniciaFigura(); }
    void inicialitza(TipusFigura tipus, int fila, int columna);
    void gira(DireccioGir direccio);
    void mou(int posX);
    void baixa();
    void puja();
    void representa();

    //Getters
    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }

    ColorFigura getColor() const { return m_color; }
    void getMascara(int mascara[MAX_ALCADA][MAX_AMPLADA]) const;

    int getAltura() const { return m_altura; }
    int getAmplada() const { return m_amplada; }

    TipusFigura getTipus() const { return m_tipus; }

    //Metodes
    void reiniciaFigura(); //Avans de que es creii ens assegurem que la figura es la que volem
    void representacioEnBinari(TipusFigura tipus); //Inicialitza la forma de la figura
    void transposaMascara();//Transposa la mascara de la figura 
    void inverteixMascaraHorizontal(); //Trasposem la matriu horitzontalment 
    void inverteixMascaraVertical();//Trasposem la matriu verticalment 

private:
    //Caracterisitques figures
    TipusFigura m_tipus;
    ColorFigura m_color;
    //Creacio de la figura
    int m_mascara[MAX_ALCADA][MAX_AMPLADA];
    int m_fila;
    int m_columna;
    //Creacio de la figura maxims de amplada i alcada
    int m_amplada;
    int m_altura;
    //Rotacio de la figura
    int m_girar;


};


#endif
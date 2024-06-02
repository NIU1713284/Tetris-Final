#include <iostream>
#include <fstream>
#include "Joc.h"

using namespace std;

void Joc::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		int tipus, fila, columna, gir, color;
		fitxer >> tipus >> fila >> columna >> gir;
		m_figuraAct.inicialitza(TipusFigura(tipus), fila, columna); //Inicialitzem la figura actual
		for (int i = 0; i < gir; i++)//Bucle per girar la figura de forma horaria
			m_figuraAct.gira(GIR_HORARI);

		ColorFigura taulerInicial[MAX_FILA][MAX_COL];

		for (int i = 0; i < MAX_FILA; i++) //Assignem els valors a la tauler amb el colors que hi hagi
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer >> color;
				taulerInicial[i][j] = ColorFigura(color);
			}
		m_tauler.inicialitza(taulerInicial);
		fitxer.close();
	}
}

bool Joc::giraFigura(DireccioGir direccio)
{
	m_figuraAct.gira(direccio);
	bool xoca = m_tauler.confrontacioFigures(m_figuraAct);
	if (xoca)
	{
		if (direccio == GIR_HORARI)
			direccio = GIR_ANTI_HORARI;
		else
			direccio = GIR_HORARI;
		m_figuraAct.gira(direccio);
	}
	return !xoca;
}

bool Joc::mouFigura(int posicioX) //Movem la figura com volguem i si detecta que xoca amb alguna figura retorna un true vol dir que ha xocat i es desfà el moviment tiranr una posicio enrere
{
	m_figuraAct.mou(posicioX);
	bool xoca = m_tauler.confrontacioFigures(m_figuraAct);
	if (xoca)
		m_figuraAct.mou(-posicioX);
	return !xoca;
}

int Joc::baixaFigura()
{
	int nFiles = 0;
	m_figuraAct.baixa();
	if (m_tauler.confrontacioFigures(m_figuraAct))
	{
		m_figuraAct.puja();
		nFiles = m_tauler.posicioFigura(m_figuraAct);
		m_figuraAct.inicialitza(NO_FIGURA, -1, -1); //retorna el numero de posicions ocupades
	}
	return nFiles;
}

void Joc::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		if (m_figuraAct.getTipus() != NO_FIGURA)
			m_tauler.printFigura(m_figuraAct);
		ColorFigura tauler[MAX_FILA][MAX_COL];
		m_tauler.getValorsTauler(tauler);
		for (int i = 0; i < MAX_FILA; i++)
		{
			for (int j = 0; j < MAX_COL; j++)
			{
				fitxer << int(tauler[i][j]) << " ";
			}
			fitxer << endl;
		}

		fitxer.close();
	}
}

bool Joc::creaFigura()
{
	TipusFigura tipus = TipusFigura((rand() % N_TIPUS_FIGURES) + 1);
	int maxCol = N_COL_TAULER - 2;
	int columna = (rand() % maxCol) + 1;
	int nGir = (rand() % 4);
	m_figuraAct.inicialitza(tipus, 1, columna);

	if (tipus == FIGURA_O)
		maxCol = N_COL_TAULER - 1;
	else
		if (tipus == FIGURA_I)
			maxCol = N_COL_TAULER - 3;

	
	for (int i = 0; i < nGir; i++)
		m_figuraAct.gira(GIR_HORARI);

	bool colisiona = m_tauler.confrontacioFigures(m_figuraAct);
	return colisiona;
}

void Joc::creaFigura(DadesFigura figura)
{
	m_figuraAct.inicialitza(figura.tipus, figura.fila, figura.columna);
	for (int i = 0; i < figura.girar; i++)
		m_figuraAct.gira(GIR_HORARI);
}

int Joc::posarFigura()
{
	int numFil;

	while (numFil != -1)
	{
		numFil = baixaFigura();
	}

	return (numFil);
}

void Joc::representa()
{
	m_tauler.representa();
	m_figuraAct.representa();
}
#include <iostream>
#include "Figura.h"

void::Figura::reiniciaFigura() //Ens assegurem que la matriu de la figura està inicialitzada a zero per evitar problemes amb numeros
{
	for (int i = 0; i < m_altura; i++)
		for (int j = 0; j < m_amplada; j++)
			m_mascara[i][j] = 0;
}

void Figura::representacioEnBinari(TipusFigura tipus) //Creem cada figura amb forma binaria
{
	switch (tipus)
	{
	case FIGURA_J:
		m_amplada = 3;
		m_altura = 3;
		reiniciaFigura();
		m_mascara[0][0] = 1;
		m_mascara[1][0] = 1;
		m_mascara[1][1] = 1;
		m_mascara[1][2] = 1;
		m_color = COLOR_BLAUFOSC;
		break;
	case FIGURA_L:
		m_amplada = 3;
		m_altura = 3;
		reiniciaFigura();
		m_mascara[0][2] = 1;
		m_mascara[1][0] = 1;
		m_mascara[1][1] = 1;
		m_mascara[1][2] = 1;
		m_color = COLOR_TARONJA;
		break;
	case FIGURA_S:
		m_amplada = 3;
		m_altura = 3;
		reiniciaFigura();
		m_mascara[0][1] = 1;
		m_mascara[0][2] = 1;
		m_mascara[1][0] = 1;
		m_mascara[1][1] = 1;
		m_color = COLOR_VERD;
		break;
	case FIGURA_Z:
		m_amplada = 3;
		m_altura = 3;
		reiniciaFigura();
		m_mascara[0][0] = 1;
		m_mascara[0][1] = 1;
		m_mascara[1][1] = 1;
		m_mascara[1][2] = 1;
		m_color = COLOR_VERMELL;
		break;
	case FIGURA_T:
		m_amplada = 3;
		m_altura = 3;
		reiniciaFigura();
		m_mascara[0][1] = 1;
		m_mascara[1][0] = 1;
		m_mascara[1][1] = 1;
		m_mascara[1][2] = 1;
		m_color = COLOR_MAGENTA;
		break;
	case FIGURA_I:
		m_amplada = 4;
		m_altura = 4;
		reiniciaFigura();
		m_mascara[1][0] = 1;
		m_mascara[1][1] = 1;
		m_mascara[1][2] = 1;
		m_mascara[1][3] = 1;
		m_color = COLOR_BLAUCEL;
		break;
	case FIGURA_O:
		m_amplada = 2;
		m_altura = 2;
		m_mascara[0][0] = 1;
		m_mascara[0][1] = 1;
		m_mascara[1][0] = 1;
		m_mascara[1][1] = 1;
		m_color = COLOR_GROC;
		break;
	}
}

void Figura::inicialitza(TipusFigura tipus, int fila, int columna) //Igualem cata private
{
	m_tipus = tipus;
	m_fila = fila;
	m_columna = columna;
	m_girar = 0;
	representacioEnBinari(tipus);
}

void Figura::getMascara(int mascara[MAX_ALCADA][MAX_AMPLADA]) const //Copiem la matriu de la figura "en questa farem els canvis"
{
	for (int i = 0; i < m_altura; i++)
		for (int j = 0; j < m_amplada; j++)
			mascara[i][j] = m_mascara[i][j];
}
void Figura::puja()
{
	m_fila -= 1;
}
void Figura::baixa()
{
	m_fila += 1;
}
void Figura::mou(int posX)
{
	m_columna += posX;
}
void Figura::gira(DireccioGir direccio) //Gira la matriu 90º dreta o esquerra
{
	transposaMascara();
	if (direccio == GIR_HORARI)
	{
		inverteixMascaraVertical();
		m_girar = (m_girar + 1) % 4;
	}
	else
	{
		inverteixMascaraHorizontal();
		m_girar = (m_girar - 1) % 4;
	}

}
void Figura::transposaMascara() //Transposa la matriu "Copiem i substituim"
{
	int ax;
	for (int i = 1; i < m_altura; i++)
		for (int j = 0; j < i; j++)
		{
			ax = m_mascara[i][j];
			m_mascara[i][j] = m_mascara[j][i];
			m_mascara[j][i] = ax;
		}
}
void Figura::inverteixMascaraVertical() //Girem la matriu veritcalment 
{
	int c1, c2, ax;
	if (m_amplada != 2)
	{
		if (m_amplada == 3)
		{
			c1 = 0;
			c2 = 2;
		}
		else
		{
			c1 = 1;
			c2 = 2;
		}
		for (int i = 0; i < m_altura; i++)
		{
			ax = m_mascara[i][c1];
			m_mascara[i][c1] = m_mascara[i][c2];
			m_mascara[i][c2] = ax;
		}
	}
}
void Figura::inverteixMascaraHorizontal() //fem el mateix que avans pero horitzontalment pel que agafem les files en ves de columnes
{
	int f1, f2, ax;
	if (m_altura != 2)
	{
		if (m_altura == 3)
		{
			f1 = 0;
			f2 = 2;
		}
		else
		{
			f1 = 1;
			f2 = 2;
		}
		for (int i = 0; i < m_amplada; i++)
		{
			ax = m_mascara[f1][i];
			m_mascara[f1][i] = m_mascara[f2][i];
			m_mascara[f2][i] = ax;
		}
	}

}

void Figura::representa()
{
	for (int i = 0; i < m_altura; i++)
		for (int j = 0; j < m_amplada; j++)
		{
			if (m_mascara[i][j] != 0)
				dibuixPlantilla(m_color, POS_X_TAULER + ((m_altura + j) * MIDA_QUADRAT), POS_Y_TAULER + ((m_amplada - 1 + i) * MIDA_QUADRAT));
		}

}
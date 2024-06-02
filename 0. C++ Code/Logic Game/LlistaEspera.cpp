#include <iostream>
#include "LListaEspera.h"
using namespace std;

void LlistaEspera::eliminar() //Eliminem el primer element que hagi a la llista d'espera
{
	Forma* temp;
	if (m_primer == m_final)
	{
		delete m_primer;
		m_primer = nullptr;
		m_final = nullptr;
	}
	else
	{
		temp = m_primer->GetSeguent();
		delete m_primer;
		m_primer = temp;
	}
}

LlistaEspera::~LlistaEspera()
{
	while (m_primer != nullptr)
	{
		eliminar();
	}
}

int LlistaEspera::GetNumElements() const //Contem quants elements hi ha a la llista
{
	int nElements = 0;
	Forma* auxiliar = m_primer;

	while (auxiliar != NULL)
	{
		nElements++;
		auxiliar = auxiliar->GetSeguent();
	}

	return nElements;
}

LlistaEspera& LlistaEspera::operator=(const LlistaEspera &list)//copiam una llista i la passem a una altre amb la dada eliminat
{
	if (this != &list)
	{
		while (m_primer != nullptr)
			eliminar();
		Forma* auxiliar = list.m_primer;
		Forma* auCrea = m_primer;
		while (auCrea != nullptr)
		{
			auCrea = insereix(auxiliar->GetValor());
			auxiliar = auxiliar->GetSeguent();
		}
	}
	return *this;
}

LlistaEspera::LlistaEspera(const LlistaEspera &list) //crea la copia
{
	m_primer = nullptr;
	m_final = nullptr;
	Forma* auxiliar = list.m_primer;
	Forma* auCrea = m_primer;

	while (auxiliar != nullptr)
	{
		auCrea = insereix(auxiliar->GetValor());
		auxiliar = auxiliar->GetSeguent();
	}

}


Forma* LlistaEspera::insereix(const DadesFigura &tecla) //Insereix un nou element a la llista amb el valor especificat. Si la llista està buida, el nou element es converteix en el primer
{
	Forma* auxiliar = new Forma;
	if (auxiliar != nullptr)
	{
		auxiliar->SetValor(tecla);
		auxiliar->SetSeguent(nullptr);
		if (m_primer == nullptr)
		{
			m_primer = auxiliar;
		}
		else
		{
			m_final->SetSeguent(auxiliar);
		}
		m_final = auxiliar;
	}

	return (auxiliar);
}


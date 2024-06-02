#include <iostream>
#include "RegistreMoviment.h"
using namespace std;

desplacVect* RegistreDesplac::insereix(const TipusTecla &tecla)
{
	desplacVect* nouDesplac = new desplacVect;

	if (nouDesplac != nullptr)
	{
		nouDesplac->SetNum(tecla);
		nouDesplac->SetSeguent(nullptr);

		if (m_primer == nullptr)
		{
			m_primer = nouDesplac;
		}
		else
		{
			m_final->SetSeguent(nouDesplac);
		}
		m_final = nouDesplac;
	}

	return nouDesplac;
}

void RegistreDesplac::eliminar()
{
	if (m_primer == nullptr){return; }

	desplacVect* seguentDesplac = m_primer->GetSeguent();
	delete m_primer;

	if (seguentDesplac == nullptr)
	{
		// Només hi havia un element a la llista
		m_primer = nullptr;
		m_final = nullptr;
	}
	else
	{
		m_primer = seguentDesplac;
	}
}

RegistreDesplac::~RegistreDesplac()
{
	while (m_primer != nullptr)
		eliminar();
}

RegistreDesplac::RegistreDesplac(const RegistreDesplac &list)
{
	m_primer = nullptr;
	m_final = nullptr;
	desplacVect* auxiliar = list.m_primer;
	desplacVect* auxCrea = m_primer;

	while (auxiliar != nullptr)
	{
		auxCrea = insereix(auxiliar->GetNum());
		auxiliar = auxiliar->GetSeguent();
	}

}

RegistreDesplac& RegistreDesplac::operator=(const RegistreDesplac& list)
{
	if (this != &list)
	{
		while (m_primer != nullptr)
			eliminar();

		desplacVect* auxiliar = list.m_primer;
		desplacVect* auxCrea = m_primer;

		while (auxiliar != nullptr)
		{
			auxCrea = insereix(auxiliar->GetNum());
			auxiliar = auxiliar->GetSeguent();
		}
	}

	return (*this);
}

int RegistreDesplac::GetNumElements() const
{
	int nElements = 0;
	desplacVect* auxiliar = m_primer;

	while (auxiliar != NULL)
	{
		nElements++;
		auxiliar = auxiliar->GetSeguent();
	}

	return nElements;
}


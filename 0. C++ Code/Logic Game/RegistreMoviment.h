#include <iostream>
#include "Desplas.h"

class RegistreDesplac
{
private:
	desplacVect* m_primer;
	desplacVect* m_final;

public:
	RegistreDesplac(desplacVect* primer, desplacVect* final) : m_primer(primer), m_final(final) {}
	RegistreDesplac() : m_primer(nullptr) {}
	~RegistreDesplac();
	RegistreDesplac(const RegistreDesplac &list);
	RegistreDesplac& operator=(const RegistreDesplac &list);
	desplacVect* insereix(const TipusTecla &tecla);

	// GETTERS
	int GetNumElements() const;
	TipusTecla GetPrimer() const { return m_primer->GetNum(); }

	void eliminar();
	bool lliure() const { return m_primer == nullptr; }

};
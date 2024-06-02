#include <iostream>
#include "Forma.h"

class LlistaEspera
{
private:
	Forma* m_primer;
	Forma* m_final;

public:
    LlistaEspera(Forma* primer, Forma* final) : m_primer(primer), m_final(final) {}
    LlistaEspera() : m_primer(nullptr), m_final(nullptr) {}
    ~LlistaEspera();
    LlistaEspera(const LlistaEspera& list);
    LlistaEspera& operator=(const LlistaEspera& list);
    Forma* insereix(const DadesFigura& tecla);

    // GETTERS
    int GetNumElements() const;
    DadesFigura GetPrimer() const { return m_primer->GetValor(); }

    bool lliure() const { return m_primer == nullptr; }
    void eliminar();
};
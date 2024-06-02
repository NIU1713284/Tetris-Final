#include <stdlib.h>
#include <iostream>
#include "InfoJoc.h"

class Forma
{
private:
	Forma* m_seguent;
	DadesFigura m_valor;

public:
	Forma() { m_seguent = nullptr; };
	~Forma() {};
	Forma(const DadesFigura& val) { m_valor = val; m_seguent = nullptr; }

	//GETTERS
	Forma* GetSeguent() { return m_seguent; }
	DadesFigura GetValor() { return m_valor; }

	//SETTERS
	void SetSeguent(Forma* seg) { m_seguent = seg; }
	void SetValor(const DadesFigura& num) { m_valor = num; }
};
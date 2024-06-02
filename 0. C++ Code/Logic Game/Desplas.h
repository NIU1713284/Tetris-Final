#include <iostream>
#include <stdlib.h>
#include "InfoJoc.h"

class desplacVect
{
private:
	desplacVect* m_seguent;
	TipusTecla m_numero;

public:
	desplacVect() { m_seguent = nullptr; }
	~desplacVect() {}
	desplacVect(const TipusTecla& valor) { this->m_numero = valor; m_seguent = nullptr; }

	//Getters
	desplacVect* GetSeguent() { return m_seguent; }
	TipusTecla GetNum() { return m_numero; }

	//Setters
	void SetSeguent(desplacVect* seg) { m_seguent = seg; }
	void SetNum(const TipusTecla& num) { m_numero = num; }
};
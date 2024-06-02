#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>
using namespace std;

class Joc
{
public:
	Joc() {}
	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int posicioX);
	int baixaFigura();
	void escriuTauler(const string& nomFitxer);

	//Noves addicions
	bool creaFigura();
	void creaFigura(DadesFigura figura);
	int posarFigura();
	void representa();

private:
	Tauler m_tauler;
	Figura m_figuraAct;
};

#endif
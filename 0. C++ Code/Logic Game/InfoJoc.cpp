#include <iostream>
#include "InfoJoc.h"
#include "GraphicManager.h"

void dibuixPlantilla(ColorFigura color, int x, int y)
{
	IMAGE_NAME grafic;

	switch (color)
	{
	case COLOR_GROC:
		grafic = GRAFIC_QUADRAT_GROC;
		break;
	case COLOR_BLAUCEL:
		grafic = GRAFIC_QUADRAT_BLAUCEL;
		break;
	case COLOR_MAGENTA:
		grafic = GRAFIC_QUADRAT_MAGENTA;
		break;
	case COLOR_TARONJA:
		grafic = GRAFIC_QUADRAT_TARONJA;
		break;
	case COLOR_BLAUFOSC:
		grafic = GRAFIC_QUADRAT_BLAUFOSC;
		break;
	case COLOR_VERMELL:
		grafic = GRAFIC_QUADRAT_VERMELL;
		break;
	case COLOR_VERD:
		grafic = GRAFIC_QUADRAT_VERD;
		break;
	}

	GraphicManager::getInstance()->drawSprite(grafic, x, y, false);
}
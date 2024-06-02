#include <fstream>
#include <iostream>
#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"

void Partida::inicialitza(const string& Fitxer1, const string& Fitxer2, const string& Fitxer3) //Inicialitza la partida segons el mode de joc (normal o personalitzat). Si és normal, crea una figura. Si és personalitzat, carrega dades dels fitxers.
{
    if (m_mode == MODE_NORMAL)
    {
        m_final = m_joc.creaFigura();
    }
    else
    {
        m_joc.inicialitza(Fitxer1);
        inicialitzaFig(Fitxer2);
        inicialitzaDesplas(Fitxer3);
    }
}

void Partida::inicialitzaFig(const string& nomFitxer) //Llegeix les figures des d'un fitxer i les insereix a la llista de figures.
{
    ifstream fitxer(nomFitxer);
    if (fitxer.is_open())
    {
        DadesFigura figura;
        int tipus;
        fitxer >> tipus >> figura.fila >> figura.columna >> figura.girar;
        figura.tipus = TipusFigura(tipus);
        while (!fitxer.eof())
        {
            m_figures.insereix(figura);
            fitxer >> tipus >> figura.fila >> figura.columna >> figura.girar;
            figura.tipus = TipusFigura(tipus);
        }
        fitxer.close();
    }
    else
    {
        cout << "No s'ha pogut obrir el fitxer: " << endl;
    }
}

void Partida::inicialitzaDesplas(const string& Nfitxer) //Llegeix els moviments des d'un fitxer i els insereix a la llista de desplaçaments
{
    ifstream fitxer;
    fitxer.open(Nfitxer);
    if (fitxer.is_open())
    {
        int tipus;
        fitxer >> tipus;
        while (!fitxer.eof())
        {
            m_desplas.insereix(TipusTecla(tipus));
            fitxer >> tipus;
        }
        fitxer.close();
    }
}

void Partida::canviaNormal(float deltaTime) //Gestiona els moviments i girs de la figura en mode normal, basant-se en l'entrada del tecla
{
    // Moviment horitzontal
    if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
    {
        m_joc.mouFigura(1);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
    {
        m_joc.mouFigura(-1);
    }

    // Rotació
    if (Keyboard_GetKeyTrg(KEYBOARD_UP))
    {
        m_joc.giraFigura(GIR_HORARI);
    }
    else if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
    {
        m_joc.giraFigura(GIR_ANTI_HORARI);
    }

    // Posar figura o baixar-la
    if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
    {
        int nFilesEliminades = m_joc.posarFigura();
        actualitzar(nFilesEliminades);
        m_final = m_joc.creaFigura();
        m_temps = 0.0;
    }
    else
    {
        m_temps += deltaTime;
        if (m_temps > m_velocitat)
        {
            int nFilesEliminades = m_joc.baixaFigura();
            if (nFilesEliminades != -1)
            {
                m_final = m_joc.creaFigura();
                actualitzar(nFilesEliminades);
            }
            m_temps = 0.0;
        }
    }
}

void Partida::canviaProva(float deltaTime) //Gestiona els moviments i girs de la figura en mode prova, basant-se en els moviments llegits del fitxer.
{
    m_temps += deltaTime;
    if (m_temps <= m_velocitat) return;

    m_temps = 0.0;
    if (m_desplas.lliure())
    {
        m_final = true;
        return;
    }

    TipusTecla moviment = m_desplas.GetPrimer();
    m_desplas.eliminar();
    int nFilesEliminades;

    switch (moviment)
    {
    case DRETA:
        m_joc.mouFigura(1);
        break;
    case ESQUERRA:
        m_joc.mouFigura(-1);
        break;
    case GIR_HORARI_1:
        m_joc.giraFigura(GIR_HORARI);
        break;
    case GIR_ANTI:
        m_joc.giraFigura(GIR_ANTI_HORARI);
        break;
    case BAIXA_FINAL:
        nFilesEliminades = m_joc.posarFigura();
        actualitzar(nFilesEliminades);
        if (m_figures.lliure())
        {
            m_final = true;
        }
        else
        {
            DadesFigura figura = m_figures.GetPrimer();
            m_figures.eliminar();
            m_joc.creaFigura(figura);
        }
        break;
    case BAIXA_UNA:
        nFilesEliminades = m_joc.baixaFigura();
        if (nFilesEliminades != -1)
        {
            actualitzar(nFilesEliminades);
            if (m_figures.lliure())
            {
                m_final = true;
            }
            else
            {
                DadesFigura figura = m_figures.GetPrimer();
                m_figures.eliminar();
                m_joc.creaFigura(figura);
            }
        }
        break;
    default:
        break;
    }
}

void Partida::actualitza(float deltaTime) //Actualitza l'estat del joc, dibuixa el fons, la puntuació, el nivell, i mostra el missatge de final de joc si és necessari.
{
    if (!m_final)
    {
        if (m_mode == MODE_NORMAL)
            canviaNormal(deltaTime);
        else
            canviaProva(deltaTime);
    }

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    m_joc.representa();
    string numPunts = "Puntuacio: " + to_string(m_punts);
    string nivell = "Nivell: " + to_string(m_nivell);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_PUNTS, POS_Y_PUNTS, 0.8, numPunts);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_NIVELL, POS_Y_NIVELL, 0.8, nivell);
    if (m_final)
    {
        string gameOver = "GAME OVER";
        GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_GAME, POS_Y_GAME, 1.8, gameOver);

    }
}

void Partida::actualitzar(int eliminaFiles) //Actualitza la puntuació i el nivell en funció del nombre de files eliminades.
{
    if (eliminaFiles == 0)
        m_punts += PP_FIGURA;
    else
    {
        m_punts += P_1FIL;
        switch (eliminaFiles)
        {
        case 2:
            m_punts += P_2FIL;
            break;
        case 3:
            m_punts += P_3FIL;
            break;
        case 4:
            m_punts += P_4FIL;
            break;
        }
    }
    if (m_punts > (m_nivell * PUJAR_NIVELL))
    {
        m_nivell += 1;
        m_velocitat *= INC_VELOCITAT;
    }
}
#include "TetrisFinal.h"
#include "../Graphic Lib/NFont/NFont.h"

Tetris::Tetris(const string& fitxerPuntuacions) {
    ifstream fitxer(fitxerPuntuacions);
    if (fitxer.is_open()) {
        Puntuacio p;
        while (fitxer >> p.nom >> p.punts) {
            m_puntuacions.push_back(p);
        }
        fitxer.close();
    }
}

void Tetris::visualitzaPuntuacions() {
    cout << endl;
    cout << "LLISTAT DE PUNTUACIONS" << endl;
    cout << "======================" << endl;
    int ordre = 1;
    for (const auto& punt : m_puntuacions) {
        cout << ordre << ". " << punt.nom << " " << punt.punts << endl;
        ordre++;
    }
    cout << endl;
}

void Tetris::guardaPuntuacions(const string& nomFitxer) {
    ofstream fitxer(nomFitxer);
    for (const auto& punt : m_puntuacions) {
        fitxer << punt.nom << " " << punt.punts << endl;
    }
    fitxer.close();
}

void Tetris::actualitzaPuntuacio(const string& nom, int punts) {
    auto it = m_puntuacions.begin();
    while (it != m_puntuacions.end() && it->punts > punts) {
        ++it;
    }
    Puntuacio p;
    p.nom = nom;
    p.punts = punts;
    m_puntuacions.insert(it, p);
}

int Tetris::juga(Screen& pantalla, ModeJoc mode, const string& nomFitxerInicial, const string& nomFitxerFigures, const string& nomFitxerMoviments) {
    pantalla.show();

    m_partida.inicialitza(nomFitxerInicial, nomFitxerFigures, nomFitxerMoviments);

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    do {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        pantalla.processEvents();
        m_partida.actualitza(deltaTime);
        pantalla.update();
    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));

    return m_partida.GetPuntuacio();
}

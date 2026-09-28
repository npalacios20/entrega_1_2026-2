#include "Jugador.h"
using namespace std;

Jugador::Jugador(int _id) : id(_id), puntuajeTotal(0) {}

void Jugador::recibirCarta(Carta* c) {
    mano.push_back(c);
}

Carta* Jugador::jugarCarta(int indice) {
    if (indice >= 0 && indice < (int)mano.size()) {
        Carta* c = mano[indice];
        mano.erase(mano.begin() + indice);
        return c;
    }
    return nullptr;
}

void Jugador::sumarPuntos(int puntos) {
    puntuajeTotal = puntuajeTotal + puntos;
}

void Jugador::setPuntuajeTotal(int valor) {
    puntuajeTotal = valor;
}

void Jugador::reiniciarTodo() {
    puntuajeTotal = 0;
    for (Carta* c : mano) {
        delete c;
    }
    mano.clear();
}

void Jugador::mostrarMano() const {
    cout << "\n" << AZUL << "--- Mano del Jugador " << id << " ---" << RESET << "\n";
    if (mano.empty()) {
        cout << "   ⚠️ No tienes cartas.\n";
        return;
    }
    for (size_t i = 0; i < mano.size(); i++) {
        cout << "   [" << i << "] " << mano[i]->mostrar() << "\n";
    }
}

void Jugador::mostrarPuntuacion() const {
    cout << "👤 Jugador " << id << " → " << VERDE << puntuajeTotal << " puntos" << RESET << "\n";
}

int Jugador::getId() const { 
    return id; 
}

int Jugador::getPuntuajeTotal() const { 
    return puntuajeTotal; 
}

int Jugador::cantidadCartas() const { 
    return (int)mano.size(); 
}

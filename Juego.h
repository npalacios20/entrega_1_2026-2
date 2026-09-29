#ifndef JUEGO_H
#define JUEGO_H
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Jugador.h"
#include "Carta.h"
#include "Emojis_Colores.h"

class Juego {
private:
    std::vector<Jugador*> jugadores;
    std::vector<Carta*> mazo;
    int cantidadJugadores;
    int turnoActual;
    bool partidaActiva;

    std::string colorBase;
    bool reglaMayor;
    int valorReferencia;
    int ganadorUltimaRonda;
    int numeroRonda;

    void crearMazo();
    void mezclarMazo();
    bool asegurarCarpeta();

public:
    Juego(int cantJugadores);

    void iniciarNuevaPartida();
    void repartirCartas(int cantidadPorJugador);
    void mostrarTodasLasPuntuaciones() const;
    void siguienteTurno();
    void definirReglaRonda(Carta* cartaJugada);
    bool validarCarta(Carta* carta) const;
    void jugarRonda();
    bool guardarPartida();
    bool cargarPartida();
    void finalizarPartida();
    void reiniciarJuegoCompleto();
};

#endif
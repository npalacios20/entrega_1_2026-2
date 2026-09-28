#ifndef JUGADOR_H
#define JUGADOR_H
#include <vector>
#include <iostream>
#include "Carta.h"
#include "Emojis_Colores.h"

class Jugador {
private:
    int id;
    int puntuajeTotal;
    std::vector<Carta*> mano;

public:
    Jugador(int _id);

    void recibirCarta(Carta* c);
    Carta* jugarCarta(int indice);
    void sumarPuntos(int puntos);
    void setPuntuajeTotal(int valor);
    void reiniciarTodo();
    
    void mostrarMano() const;
    void mostrarPuntuacion() const;
    
    int getId() const;
    int getPuntuajeTotal() const;
    int cantidadCartas() const;
};

#endif
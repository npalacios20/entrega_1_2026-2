#include "Carta.h"
using namespace std;

Carta::Carta(string color_, int valor_) {
    color = color_;
    valor = valor_;
}

string Carta::getColor() const {
    return color;
}

int Carta::getValor() const {
    return valor;
}

string Carta::mostrar() const {
    return "🎴 Color: " + color + " | Valor: " + to_string(valor);
}
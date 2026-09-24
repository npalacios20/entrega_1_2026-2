#include "Carta.h"

Carta::Carta(std::string color_, int valor_) {
    color = color_;
    valor = valor_;
}

std::string Carta::getColor() const {
    return color;
}

int Carta::getValor() const {
    return valor;
}

std::string Carta::mostrar() const {
    return std::to_string(valor) + " de " + color;
}
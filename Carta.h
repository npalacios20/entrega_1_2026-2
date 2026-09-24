#ifndef CARTA_H
#define CARTA_H
#include <string>

class Carta {
private:
    std::string color;
    int valor;

public:
    Carta(std::string color_, int valor_);

    std::string getColor() const;
    int getValor() const;

    std::string mostrar() const;
};

#endif
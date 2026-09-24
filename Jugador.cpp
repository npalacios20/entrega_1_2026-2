// *********************************************************************************
// CLASE: Jugador
// *********************************************************************************
class Jugador {
private:
    int id;
    int puntuajeTotal;
    vector<Carta*> mano;

public:
    Jugador(int _id) : id(_id), puntuajeTotal(0) {}

    void recibirCarta(Carta* c) {
        mano.push_back(c);
    }

    Carta* jugarCarta(int indice) {
        if (indice >= 0 && indice < (int)mano.size()) {
            Carta* c = mano[indice];
            mano.erase(mano.begin() + indice);
            return c;
        }
        return nullptr;
    }

    void sumarPuntos(int puntos) {
        puntuajeTotal += puntos;
    }

    void setPuntuajeTotal(int valor) {
        puntuajeTotal = valor;
    }

    void reiniciarTodo() {
        puntuajeTotal = 0;
        for (Carta* c : mano) delete c;
        mano.clear();
    }

    void mostrarMano() const {
        cout << "\n" << AZUL << "--- Mano del Jugador " << id << " ---" << RESET << "\n";
        if (mano.empty()) {
            cout << "   ⚠️ No tienes cartas.\n";
            return;
        }
        for (size_t i = 0; i < mano.size(); i++) {
            cout << "   [" << i << "] " << mano[i]->mostrar() << "\n";
        }
    }

    void mostrarPuntuacion() const {
        cout << "👤 Jugador " << id << " → " << VERDE << puntuajeTotal << " puntos" << RESET << "\n";
    }

    int getId() const { return id; }
    int getPuntuajeTotal() const { return puntuajeTotal; }
    int cantidadCartas() const { return (int)mano.size(); }
};


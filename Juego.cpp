
// ======================================
// CLASE: Juego
// ======================================
class Juego {
private:
    vector<Jugador*> jugadores;
    vector<Carta*> mazo;
    int cantidadJugadores;
    int turnoActual;
    bool partidaActiva;

    string colorBase;
    bool reglaMayor;
    int valorReferencia;
    int ganadorUltimaRonda;
    int numeroRonda;

    void crearMazo() {
        mazo.clear();
        vector<string> colores = {"Rojo", "Azul", "Verde", "Amarillo"};
        for (string col : colores) {
            for (int val = 1; val <= 10; val++) {
                mazo.push_back(new Carta(col, val));
            }
        }
    }

    void mezclarMazo() {
        srand(time(nullptr));
        for (size_t i = 0; i < mazo.size(); i++) {
            size_t aleatorio = (size_t)(rand() % mazo.size());
            swap(mazo[i], mazo[aleatorio]);
        }
    }

    bool asegurarCarpeta() {
        ofstream prueba(CARPETA_GUARDADO + "/prueba_acceso.tmp");
        if (prueba) {
            prueba.close();
            remove((CARPETA_GUARDADO + "/prueba_acceso.tmp").c_str());
            return true;
        }
        cout << AMARILLO << "⚠️ No se puede acceder a la carpeta: " << CARPETA_GUARDADO << RESET << "\n";
        cout << "   💡 Crea una carpeta llamada 'partidas_guardadas' junto al programa.\n";
        return false;
    }

public:
    Juego(int cantJugadores) : cantidadJugadores(cantJugadores), turnoActual(0), partidaActiva(false), ganadorUltimaRonda(1), numeroRonda(0) {
        for (int i = 0; i < cantidadJugadores; i++) {
            jugadores.push_back(new Jugador(i + 1));
        }
        crearMazo();
    }

    void iniciarNuevaPartida() {
        reiniciarJuegoCompleto();
        crearMazo();
        mezclarMazo();
        repartirCartas(5);
        partidaActiva = true;
        ganadorUltimaRonda = 1;
        numeroRonda = 0;
        cout << "\n" << VERDE << "✅ PARTIDA NUEVA INICIADA con " << cantidadJugadores << " jugadores" << RESET << "\n";
        cout << "📌 Reglas: + = Mayor o igual  |  - = Menor o igual\n";
        cout << "📌 Puntuación: Se suma el valor de la carta ganadora\n";
        mostrarTodasLasPuntuaciones();
    }

    void repartirCartas(int cantidadPorJugador) {
        for (Jugador* j : jugadores) {
            for (int c = 0; c < cantidadPorJugador && !mazo.empty(); c++) {
                j->recibirCarta(mazo.back());
                mazo.pop_back();
            }
        }
    }

    void mostrarTodasLasPuntuaciones() const {
        cout << "\n" << CIAN << "==== TABLA DE PUNTUACIONES ====" << RESET << "\n";
        for (const Jugador* j : jugadores) {
            j->mostrarPuntuacion();
        }
        cout << CIAN << "================================" << RESET << "\n";
    }

    void siguienteTurno() {
        turnoActual = (turnoActual + 1) % cantidadJugadores;
    }

    void definirReglaRonda(Carta* cartaJugada) {
        colorBase = cartaJugada->getColor();
        valorReferencia = cartaJugada->getValor();

        cout << "\n🎴 Jugador " << jugadores[turnoActual]->getId() << " inicia con: " << cartaJugada->mostrar() << "\n";
        cout << "🎨 Color base establecido: " << colorBase << "\n";

        char opcion;
        cout << "⚙️ Regla? Escribe + para MAYOR o - para MENOR: ";
        cin >> opcion;
        
        while (opcion != '+' && opcion != '-') {
            cout << ROJO << "❌ Opción inválida. " << RESET << "Escribe + o -: ";
            cin >> opcion;
        }
        
        reglaMayor = (opcion == '+');

        cout << "📏 Regla: Carta del mismo color y valor " 
             << (reglaMayor ? "MAYOR o IGUAL (>=)" : "MENOR o IGUAL (<=)") 
             << " a " << valorReferencia << "\n";
    }

    bool validarCarta(Carta* carta) const {
        if (carta->getColor() != colorBase) return false;
        return reglaMayor ? (carta->getValor() >= valorReferencia) : (carta->getValor() <= valorReferencia);
    }

    void jugarRonda() {
        numeroRonda++;
        int jugadorInicio = ganadorUltimaRonda - 1;
        turnoActual = jugadorInicio;
        int mejorValor = -1;
        int ganadorTurno = -1;
        int valorGanadora = 0;

        cout << "\n" << NEGRITA << "---------- 🏆 RONDA " << numeroRonda << " ----------" << RESET << "\n";

        Jugador* actual = jugadores[turnoActual];
        cout << "🔴 Inicia: Jugador " << actual->getId() << "\n";
        actual->mostrarMano();

        int idx;
        cout << "🃏 Elige carta a jugar: ";
        cin >> idx;
        Carta* carta = actual->jugarCarta(idx);

        if (!carta) {
            cout << ROJO << "❌ Carta inválida. Pierdes el turno.\n" << RESET;
            siguienteTurno();
            return;
        }

        definirReglaRonda(carta);
        mejorValor = carta->getValor();
        ganadorTurno = turnoActual;
        valorGanadora = carta->getValor();
        delete carta;

        siguienteTurno();

        for (int i = 1; i < cantidadJugadores; i++) {
            actual = jugadores[turnoActual];
            cout << "\n🔄 TURNO: Jugador " << actual->getId() << "\n";
            cout << "🎨 Color: " << colorBase << " | 📏 Referencia: " << valorReferencia 
                 << " | ⚙️ Regla: " << (reglaMayor ? "+ (>=)" : "- (<=)") << valorReferencia << "\n";
            actual->mostrarMano();

            cout << "🃏 Elige carta (-1 = no tienes): ";
            cin >> idx;

            if (idx == -1) {
                cout << AMARILLO << "⏭️ Pasas esta ronda.\n" << RESET;
                siguienteTurno();
                continue;
            }

            carta = actual->jugarCarta(idx);
            if (!carta) {
                cout << ROJO << "❌ Carta inválida. Pierdes el turno.\n" << RESET;
                siguienteTurno();
                continue;
            }

            if (!validarCarta(carta)) {
                cout << ROJO << "❌ No cumple la regla. " << RESET << "Debe ser " << colorBase << " y valor " 
                     << (reglaMayor ? ">= " : "<= ") << valorReferencia << "\n";
                delete carta;
                siguienteTurno();
                continue;
            }

            cout << VERDE << "✅ Válida → " << RESET << carta->mostrar() << "\n";

            bool supera = reglaMayor ? (carta->getValor() > mejorValor) : (carta->getValor() < mejorValor);
            if (supera || carta->getValor() == mejorValor) {
                mejorValor = carta->getValor();
                valorGanadora = carta->getValor();
                ganadorTurno = turnoActual;
                valorReferencia = carta->getValor();
                cout << "🏆 ¡Ahora lideras con valor " << mejorValor << "!\n";
            }

            delete carta;
            siguienteTurno();
        }

        ganadorUltimaRonda = ganadorTurno + 1;
        jugadores[ganadorTurno]->sumarPuntos(valorGanadora);

        cout << "\n----------------------------------------\n";
        cout << NEGRITA << "🏆 GANADOR DE LA RONDA " << numeroRonda << RESET << "\n";
        cout << "👤 Jugador " << ganadorUltimaRonda << "\n";
        cout << "🃏 Carta ganadora: Valor " << valorGanadora << "\n";
        cout << "💰 Puntos sumados esta ronda: " << VERDE << valorGanadora << RESET << "\n";
        mostrarTodasLasPuntuaciones();
        cout << "----------------------------------------\n";

        for (Jugador* j : jugadores) {
            while (j->cantidadCartas() < 5 && !mazo.empty()) {
                j->recibirCarta(mazo.back());
                mazo.pop_back();
            }
        }
    }

    bool guardarPartida() {
        if (!asegurarCarpeta()) {
            return false;
        }

        ofstream archivo(RUTA_COMPLETA);
        if (!archivo) {
            cout << ROJO << "❌ No se pudo escribir el archivo.\n" << RESET;
            cout << "Ruta intentada: " << RUTA_COMPLETA << "\n";
            return false;
        }

        archivo << cantidadJugadores << "\n";
        archivo << numeroRonda << "\n";
        archivo << ganadorUltimaRonda << "\n";
        for (Jugador* j : jugadores) {
            archivo << j->getId() << " " << j->getPuntuajeTotal() << "\n";
        }
        archivo.close();
        
        cout << "\n" << VERDE << "✅ PARTIDA GUARDADA EXITOSAMENTE" << RESET << "\n";
        cout << "📂 RUTA DEL ARCHIVO:\n   " << RUTA_COMPLETA << "\n";
        return true;
    }

    bool cargarPartida() {
        ifstream archivo(RUTA_COMPLETA);
        if (!archivo) {
            cout << ROJO << "❌ No se encontró partida guardada en:\n   " << RUTA_COMPLETA << RESET << "\n";
            cout << "ℹ️ Inicia una partida nueva y guárdala para crear el archivo.\n";
            return false;
        }

        int jugadoresGuardados;
        archivo >> jugadoresGuardados;
        
        if (jugadoresGuardados < 2) {
            cout << ROJO << "❌ La partida guardada tiene menos de 2 jugadores. No se puede cargar.\n" << RESET;
            archivo.close();
            return false;
        }
        if (jugadoresGuardados != cantidadJugadores) {
            cout << ROJO << "❌ La partida guardada tiene " << jugadoresGuardados << " jugadores, pero ingresaste " << cantidadJugadores << ".\n" << RESET;
            cout << "💡 Ingresa el mismo número de jugadores para continuar.\n";
            archivo.close();
            return false;
        }

        reiniciarJuegoCompleto();
        crearMazo();
        mezclarMazo();

        archivo >> numeroRonda;
        archivo >> ganadorUltimaRonda;

        for (int i = 0; i < cantidadJugadores; i++) {
            int id, puntos;
            archivo >> id >> puntos;
            if ((size_t)i < jugadores.size()) {
                jugadores[i]->setPuntuajeTotal(puntos);
            }
        }
        archivo.close();

        repartirCartas(5);
        partidaActiva = true;

        cout << "\n" << VERDE << "✅ PARTIDA CARGADA CORRECTAMENTE" << RESET << "\n";
        cout << "📂 RUTA: " << RUTA_COMPLETA << "\n";
        cout << "🔄 Rondas jugadas: " << numeroRonda << "\n";
        cout << "▶️ Quien inicia la siguiente ronda: Jugador " << ganadorUltimaRonda << "\n";
        mostrarTodasLasPuntuaciones();
        return true;
    }

    void finalizarPartida() {
        partidaActiva = false;
        
        char opcionGuardar;
        cout << "\n💾 ¿Deseas guardar esta partida? (s/n): ";
        cin >> opcionGuardar;
        if (opcionGuardar == 's' || opcionGuardar == 'S') {
            guardarPartida();
        } else {
            cout << "ℹ️ Partida NO guardada.\n";
        }

        cout << "\n\n";
        cout << "========================================\n";
        cout << "           🏆 FIN DEL JUEGO 🏆          \n";
        cout << "========================================\n";
        cout << "📊 Rondas jugadas: " << numeroRonda << "\n";
        mostrarTodasLasPuntuaciones();

        int maxPuntos = -1;
        vector<Jugador*> ganadores;

        for (Jugador* j : jugadores) {
            int p = j->getPuntuajeTotal();
            if (p > maxPuntos) {
                maxPuntos = p;
                ganadores.clear();
                ganadores.push_back(j);
            } else if (p == maxPuntos) {
                ganadores.push_back(j);
            }
        }

        cout << "\n" << NEGRITA << "🏆 GANADOR DEL JUEGO:" << RESET << "\n";
        if (ganadores.size() == (size_t)cantidadJugadores) {
            cout << "🤝 ¡EMPATE TOTAL! Todos tienen " << maxPuntos << " puntos.\n";
        } else if (ganadores.size() > 1) {
            cout << "🤝 EMPATE entre: ";
            for (size_t i = 0; i < ganadores.size(); i++) {
                if (i > 0) cout << ", ";
                cout << "Jugador " << ganadores[i]->getId();
            }
            cout << " con " << maxPuntos << " puntos cada uno.\n";
        } else {
            cout << "🎉 EL GANADOR DEL JUEGO ES EL JUGADOR " << ganadores[0]->getId() << " 🎉\n";
            cout << "   Con un total de " << VERDE << maxPuntos << " puntos acumulados!" << RESET << "\n";
        }
        cout << "\n🎴 ¡Gracias por jugar Triumph! 🎴\n";
    }

    void reiniciarJuegoCompleto() {
        for (Jugador* j : jugadores) j->reiniciarTodo();
        for (Carta* c : mazo) delete c;
        mazo.clear();
        turnoActual = 0;
        partidaActiva = false;
        ganadorUltimaRonda = 1;
        numeroRonda = 0;
    }

    ~Juego() {
        reiniciarJuegoCompleto();
        for (Jugador* j : jugadores) delete j;
    }
};

// ======================================
// FUNCION PRINCIPAL
// ======================================
int main() {
    configurarConsola(); // ✅ Activa emojis y colores automáticamente

    cout << "========== 🎴 JUEGO TRIUMPH 🎴 ==========\n";
    cout << "📂 Archivo de guardado en:\n" << RUTA_COMPLETA << "\n";
    cout << "(Carpeta junto al programa)\n\n";

    int numJugadores = 0;
    int opcion;

    do {
        cout << "========== 📋 MENU PRINCIPAL ==========\n";
        cout << "1. 🆕 Iniciar partida DESDE CERO\n";
        cout << "2. 📂 Cargar partida guardada y continuar\n";
        cout << "3. 👋 Salir\n";
        cout << "Elige una opción: ";
        cin >> opcion;

        if (opcion == 1) {
            do {
                cout << "Cantidad de jugadores (mínimo 2): ";
                cin >> numJugadores;
                if (numJugadores < 2) {
                    cout << ROJO << "❌ El juego requiere mínimo 2 jugadores. Intenta de nuevo.\n" << RESET;
                }
            } while (numJugadores < 2);

            Juego juego(numJugadores);
            juego.iniciarNuevaPartida();
            
            char seguir;
            do {
                juego.jugarRonda();
                cout << "\n¿Jugar siguiente ronda? (s/n): ";
                cin >> seguir;
            } while (seguir == 's' || seguir == 'S');
            
            juego.finalizarPartida();
        } 
        else if (opcion == 2) {
            do {
                cout << "Cantidad de jugadores (mínimo 2, igual a la partida guardada): ";
                cin >> numJugadores;
                if (numJugadores < 2) {
                    cout << ROJO << "❌ El juego requiere mínimo 2 jugadores. Intenta de nuevo.\n" << RESET;
                }
            } while (numJugadores < 2);

            Juego juego(numJugadores);
            if (juego.cargarPartida()) {
                char seguir;
                do {
                    juego.jugarRonda();
                    cout << "\n¿Jugar siguiente ronda? (s/n): ";
                    cin >> seguir;
                } while (seguir == 's' || seguir == 'S');
                
                juego.finalizarPartida();
            } else {
                cout << "💡 Inicia una partida nueva primero para crear el archivo.\n";
            }
        }
    } while (opcion != 3);

    cout << "\n👋 ¡Hasta la próxima!\n";
    return 0;
}
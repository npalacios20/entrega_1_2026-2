#include <iostream>
#include "Juego.h"
#include "Emojis_Colores.h"
using namespace std;

int main() {
    configurarConsola(); 
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
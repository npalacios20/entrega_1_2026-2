#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

// *********************************************************************************
// Fracmento de codigo para habilitar emojis y colores en la consola de Windows
// *********************************************************************************
#ifdef _WIN32
#include <windows.h>
void configurarConsola() {
    // Habilitar salida UTF-8 para ver los emojis y palabras con tildes
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // Habilitar secuencias ANSI Para ver los colores
    HANDLE hSalida = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo = 0;
    GetConsoleMode(hSalida, &modo);
    modo |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hSalida, modo);
}
#else
void configurarConsola() {
    // No se requiere configuración especial para sistemas diferentes a Windows
}
#endif

// Codigos de colores ANSI
#define RESET   "\033[0m"
#define VERDE   "\033[32m"
#define ROJO    "\033[31m"
#define AZUL    "\033[34m"
#define AMARILLO "\033[33m"
#define CIAN    "\033[36m"
#define NEGRITA "\033[1m"

using namespace std;
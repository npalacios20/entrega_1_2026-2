#ifndef EMOJIS_COLORES_H
#define EMOJIS_COLORES_H

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
inline void configurarConsola() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE hSalida = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo = 0;
    GetConsoleMode(hSalida, &modo);
    modo |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hSalida, modo);
}
#else
inline void configurarConsola() {}
#endif

#define RESET    "\033[0m"
#define VERDE    "\033[32m"
#define ROJO     "\033[31m"
#define AZUL     "\033[34m"
#define AMARILLO "\033[33m"
#define CIAN     "\033[36m"
#define NEGRITA  "\033[1m"

const std::string CARPETA_GUARDADO = "partidas_guardadas";
const std::string ARCHIVO_GUARDADO = "partida.txt";
const std::string RUTA_COMPLETA   = CARPETA_GUARDADO + "/" + ARCHIVO_GUARDADO;

#endif
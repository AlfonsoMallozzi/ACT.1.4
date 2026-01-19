/**
 * - Ana Regina Rodríguez Múzquiz | A01286913
 * - Javier Barrón Vargas | A00842507
 * - Alfonso José Morales Mallozzi | A00841550
 *
 * Compilar:
 *   g++ -std=c++17 -Wall -o act1_4 main.cpp RegistroBitacora.cpp
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


#include "RegistroBitacora.h"

int main() {
    std::ifstream archivo("bitacoraData.txt");

    // Verificar que el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo bitacoraData.txt" << std::endl;
        return 1;
    }

    std::vector<RegistroBitacora> registros;
    std::string linea;

    // Leer el archivo línea por línea
    while (getline(archivo, linea)) {

        std::string mesTexto;
        int dia;
        std::string horaCompleta;
        std::string ipPuerto;
        std::string mensaje;

        std::istringstream iss(linea);

        // Leer los primeros datos
        iss >> mesTexto >> dia >> horaCompleta >> ipPuerto;

        // El resto de la línea es el mensaje
        getline(iss, mensaje);

        // Quitar espacio inicial del mensaje
        if (!mensaje.empty() && mensaje[0] == ' ') {
            mensaje.erase(0, 1);
        }

        // Separar hora:minuto:segundo
        int hora, minuto, segundo;
        char c;

        std::istringstream tiempo(horaCompleta);
        tiempo >> hora >> c >> minuto >> c >> segundo;

        // Convertir mes a número
        int mes = RegistroBitacora::mesATextoANumero(mesTexto);

        // Crear objeto RegistroBitacora
        RegistroBitacora registro(mes, dia, hora, minuto, segundo, ipPuerto, mensaje);

        // Guardar en el vector
        registros.push_back(registro);
    }

    archivo.close();

    // Mensaje simple para verificar que sí leyó
    std::cout << "Registros leidos: " << registros.size() << std::endl;

    return 0;
}


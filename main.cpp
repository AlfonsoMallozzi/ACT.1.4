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

// Lee una fecha ingresada por el usuario y la convierte a un objeto RegistroBitacora
// Complejidad: O(1) tiempo, O(1) espacio
RegistroBitacora leerFechaUsuario(const std::string& s) {
    std::istringstream iss(s);

    std::string mesTxt;
    std::string horaCompleta;
    int dia;

    iss >> mesTxt >> dia >> horaCompleta;

    int hora = 0;
    int minuto = 0;
    int segundo = 0;
    char c;

    std::istringstream tiempo(horaCompleta);
    tiempo >> hora >> c >> minuto >> c >> segundo;

    // Convertir mes de texto a número
    int mes = RegistroBitacora::mesATextoANumero(mesTxt);

    // ipPuerto y mensaje no son relevantes para comparar fechas
    return RegistroBitacora(mes, dia, hora, minuto, segundo, "", "");
}

// Devuelve el primer índice i tal que registros[i] >= clave
// Complejidad: O(log n) tiempo, O(1) espacio
int lowerBoundFecha(const std::vector<RegistroBitacora>& registros,
                    const RegistroBitacora& clave) {
    int l = 0;
    int r = (int)registros.size() - 1;
    int ans = (int)registros.size();

    while (l <= r) {
        int mid = l + (r - l) / 2;

        // Si registros[mid] >= clave
        if (!(registros[mid] < clave)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    return ans;
}

// Devuelve el último índice i tal que registros[i] <= clave
// Complejidad: O(log n) tiempo, O(1) espacio
int upperBoundUltimoMenorIgual(const std::vector<RegistroBitacora>& registros,
                               const RegistroBitacora& clave) {
    int l = 0;
    int r = (int)registros.size() - 1;
    int ans = -1;

    while (l <= r) {
        int mid = l + (r - l) / 2;

        if (registros[mid] <= clave) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    return ans;
}

// Verifica si una fecha exacta existe dentro de la bitácora
// Complejidad: O(log n) tiempo, O(1) espacio
bool fechaExisteExacta(const std::vector<RegistroBitacora>& registros,
                       const RegistroBitacora& clave) {
    int i = lowerBoundFecha(registros, clave);

    if (i >= (int)registros.size()) {
        return false;
    }

    return registros[i].getFechaClave() == clave.getFechaClave();
}

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

    // Mensaje simple para verificar que sí leyo
    std::cout << "Registros leidos: " << registros.size() << std::endl;



    

/*/////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////*/





    
    // Solicitar al usuario la fecha inicial
std::cout << "\nIngresa la fecha inicial (formato: Mes Dia HH:MM:SS, ej: Jun 01 00:22:36):\n";
std::string f1;
std::getline(std::cin, f1);

// En caso de que se haya quedado una línea vacía en el buffer
if (f1.size() == 0) {
    std::getline(std::cin, f1);
}

// Solicitar al usuario la fecha final
std::cout << "Ingresa la fecha final (formato: Mes Dia HH:MM:SS, ej: Jun 01 08:23:57):\n";
std::string f2;
std::getline(std::cin, f2);

// Convertir las fechas ingresadas a objetos RegistroBitacora
RegistroBitacora inicio = leerFechaUsuario(f1);
RegistroBitacora fin = leerFechaUsuario(f2);

// Si el usuario ingresa el rango al revés, se intercambian
if (fin < inicio) {
    RegistroBitacora temp = inicio;
    inicio = fin;
    fin = temp;
}

// Verificar si las fechas existen de forma exacta en la bitácora
if (!fechaExisteExacta(registros, inicio)) {
    std::cout << "Aviso: la fecha inicial NO esta exacta en la bitacora.\n";
}

if (!fechaExisteExacta(registros, fin)) {
    std::cout << "Aviso: la fecha final NO esta exacta en la bitacora.\n";
}

// Buscar los índices que delimitan el rango cerrado [inicio, fin]
int idxI = lowerBoundFecha(registros, inicio);
int idxF = upperBoundUltimoMenorIgual(registros, fin);

// Mostrar los registros dentro del rango de fechas
std::cout << "\n--- Registros en el rango ---\n";

if (idxI >= (int)registros.size() || idxF < 0 || idxI > idxF) {
    std::cout << "No hay registros dentro del rango.\n";
} else {
    for (int i = idxI; i <= idxF; i++) {
        std::cout << registros[i].toString() << std::endl;
    }
}
    
    return 0;
}


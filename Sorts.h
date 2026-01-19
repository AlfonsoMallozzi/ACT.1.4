#ifndef SORTS_H
#define SORTS_H

#include <vector>
#include "RegistroBitacora.h"

class Sorts {
public:
    // Ordenamiento burbuja
    // Complejidad: O(n^2) tiempo, O(1) espacio
    static void bubbleSort(std::vector<RegistroBitacora>& datos,
                           long long& comparaciones,
                           long long& swaps);
};

#endif


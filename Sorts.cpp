#include "Sorts.h"

void Sorts::bubbleSort(std::vector<RegistroBitacora>& datos,
                       long long& comparaciones,
                       long long& swaps) {
    int n = datos.size();

    comparaciones = 0;
    swaps = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparaciones++;

            if (datos[j + 1] < datos[j]) {
                RegistroBitacora temp = datos[j];
                datos[j] = datos[j + 1];
                datos[j + 1] = temp;
                swaps++;
            }
        }
    }
}


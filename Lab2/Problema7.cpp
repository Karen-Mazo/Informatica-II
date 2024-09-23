/*Escribe un programa que reciba una cadena de caracteres y
elimina los caracteres repetidos */

#include <iostream>

using namespace std;

void repetidos(const char* original, char* sinRepetidos) {
    int repetidos[256] = {0};
    int indice = 0;

    for (int i = 0; original[i] != '\0'; i++) {
        unsigned char c = original[i];

        if (repetidos[c] == 0) {
            sinRepetidos[indice++] = c;
            repetidos[c] = 1;
        }
    }
    sinRepetidos[indice] = '\0';
}

int main() {
    char original[100];
    char sinRepetidos[100];

    cout << "Introduce una cadena de caracteres: ";
    cin.getline(original, 100);

    repetidos(original, sinRepetidos);

    cout << "Original: " << original << endl;
    cout << "Sin repetidos: " << sinRepetidos << endl;

    return 0;
}

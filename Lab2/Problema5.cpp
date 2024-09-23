/*Haz una función que reciba un número entero (int) y lo convierta a cadena de caracteres. Usa parámetros por
referencia para retornar la cadena. Escribe un programa de prueba. */

#include <iostream>
#include <string>

using namespace std;

void enteroACadena(int num, string &cadena) {
    cadena = to_string(num);
}

int main() {
    int num;
    cout << "Ingrese un numero entero: ";
    cin >> num;
    string cadena;
    enteroACadena(num, cadena);

    cout << "El numero convertido es: \"" << cadena << "\"" << endl;

    return 0;
}

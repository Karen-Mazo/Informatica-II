/*Escribe un programa que reciba un número n y lea una cadena de caracteres numéricos, el programa debe
separar la cadena de caracteres en números de n cifras, sumarlos e imprimir el resultado. En caso de no poderse
dividir exactamente en números de n cifras se colocan ceros a la izquierda del primer número.*/

#include <iostream>
#include <string>

using namespace std;


int sumar(const string& cadena, int n) {
    int longitud = cadena.length();
    int suma = 0;

    int numerosFaltantes = longitud % n;
    if (numerosFaltantes > 0) {
        int ceros = n - numerosFaltantes;
        string cadenaConCeros = string(ceros, '0') + cadena;
        longitud = cadenaConCeros.length();
        for (int i = 0; i < longitud; i += n) {
            int acumulador = 0;
            for (int j = 0; j < n; j++) {
                acumulador = acumulador * 10 + (cadenaConCeros[i + j] - '0');
            }
            suma += acumulador;
        }
    } else {
        for (int i = 0; i < longitud; i += n) {
            int acumulador = 0;
            for (int j = 0; j < n; j++) {
                acumulador = acumulador * 10 + (cadena[i + j] - '0');
            }
            suma += acumulador;
        }
    }

    return suma;
}

int main() {
    string cadena;
    int n;
    cout << "Introduce una cadena de numeros: ";
    cin >> cadena;
    cout << "Introduce el valor de n (numero de cifras a agrupar): ";
    cin >> n;
    int resultado = sumar(cadena, n);
    cout << "Original: " << cadena << endl;
    cout << "Suma: " << resultado << endl;
    return 0;
}

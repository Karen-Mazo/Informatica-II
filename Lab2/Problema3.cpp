#include <iostream>
#include <string>

using namespace std;

bool compararCadenas(string &cadena1, string &cadena2) {
    if (cadena1.length() != cadena2.length()) {
        return false;
    }

    for (int i = 0; i < cadena1.length(); i++) {
        if (cadena1[i] != cadena2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    string cadena1, cadena2;

    cout << "Ingrese la primera cadena: ";
    getline(cin, cadena1);

    cout << "Ingrese la segunda cadena: ";
    getline(cin, cadena2);

    if (compararCadenas(cadena1, cadena2)) {
        cout << "Las cadenas son iguales." << endl;
    } else {
        cout << "Las cadenas son diferentes." << endl;
    }

    return 0;
}

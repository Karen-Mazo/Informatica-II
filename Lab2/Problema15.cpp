//Elabora un programa que permita hallar la intersección entre un par de rectángulos.

#include <iostream>

using namespace std;

void interseccion(int A[4], int B[4], int C[4]) {
    // Calcular las coordenadas de la esquina inferior derecha de A y B
    int A_derecha = A[0] + A[2];
    int A_abajo = A[1] + A[3];
    int B_derecha = B[0] + B[2];
    int B_abajo = B[1] + B[3];

    // Calcular las coordenadas de la esquina superior izquierda del rectangulo interseccion
    C[0] = max(A[0], B[0]);
    C[1] = max(A[1], B[1]);

    // Calcular las coordenadas de la esquina inferior derecha del rectangulo interseccion
    int C_derecha = min(A_derecha, B_derecha);
    int C_abajo = min(A_abajo, B_abajo);

    // Calcular el ancho y la altura del rectangulo interseccion
    C[2] = C_derecha - C[0];
    C[3] = C_abajo - C[1];

    // Si no hay interseccion, ancho o altura sera negativo
    if (C[2] < 0) C[2] = 0;
    if (C[3] < 0) C[3] = 0;
}

int main() {
    int A[4];
    int B[4];
    int C[4];
    cout << "Ingrese los datos del rectangulo A (x, y, ancho, altura): ";
    cin >> A[0] >> A[1] >> A[2] >> A[3];
    cout << "Ingrese los datos del rectangulo B (x, y, ancho, altura): ";
    cin >> B[0] >> B[1] >> B[2] >> B[3];

    interseccion(A, B, C);
    cout << "Rectangulo interseccion C: {" << C[0] << ", " << C[1] << ", " << C[2] << ", " << C[3] << "}\n";

    return 0;
}

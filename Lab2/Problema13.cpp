/* Elabora y prueba una función que reciba un puntero a la matriz de enteros como argumento y que retorne el
número de estrellas encontradas en la imagen. Ignora las posibles estrellas que puedan existir en los bordes de la
matriz.*/

#include <iostream>

using namespace std;

int estrellas(int** matriz, int filas, int columnas){
    int estrellas = 0;
    for(int i = 1; i < filas - 1; i++){
        for(int j = 1; j < columnas - 1; j++){
           float suma = matriz[i][j] + matriz[i][j - 1] + matriz[i][j + 1] + matriz[i - 1][j] + matriz[i + 1][j];
            if(suma / 5 > 6){
                estrellas++;
            }
        }
    }
    return estrellas;
}

int main()
{
    int filas = 6;
    int columnas = 8;
    int** matriz = new int*[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }

    int arreglo[6][8] ={
        {0,3,4,0,0,0,6,8},
        {5,13,6,0,0,0,2,3},
        {2,6,2,7,3,0,10,0},
        {0,0,4,15,4,1,6,0},
        {0,0,7,12,6,9,10,4},
        {5,0,6,10,6,4,8,0}
    };
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = arreglo[i][j];
        }
    }
    int numEstrellas = estrellas(matriz,6,8);
    cout << "Numero de estrellas: " << numEstrellas << endl;
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
    return 0;
}

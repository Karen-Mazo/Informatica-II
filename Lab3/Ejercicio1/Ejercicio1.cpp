#include <iostream>
#include <string>
#include<fstream>
# include <bitset>

using namespace std;

string caracterToBinario(string& fileName)
{
    ifstream archivo;
    try
    {
        archivo.open(fileName, ios::binary);
        if (!archivo.is_open())
        {
            cout << "Error al abrir el archivo\n";
            return "";
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << '\n';
    }

    char caracter;
    string str_binario;

    while (archivo.get(caracter))
    {
        bitset<8> binario(caracter);
        str_binario += binario.to_string();
    }
    archivo.close();

    return str_binario;
}

void escribirArchivo(string& fileName, string& texto, bool limpiar=false)
{
    fstream archivo;
    if (limpiar) // Si limpiar es verdadero, se sobreescribe el archivo
    {
        archivo.open(fileName, ios::out | ios::binary | ios::trunc);
    }
    else // Si limpiar es falso, se agrega contenido al final del archivo
    {
        archivo.open(fileName, ios::out | ios::binary | ios::app);
    }

    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo\n";
        return;
    }
    archivo << texto << endl;
    archivo.close();
    cout << "Datos escritos en el archivo: " << fileName << endl;
}

string primerMetodo(const int n,string& str_binario){
    string codificados;
    unsigned int tamanio = str_binario.size();
    bool primerBloque = true;
    string bloqueAnterior;
    //Separo el contenido en n bits
    for(unsigned int i = 0; i < tamanio; i += n){
        string Bloque = str_binario.substr(i,n);
        string bloqueOriginal = Bloque;
        //Codifico el primer bloque
        if(primerBloque){
            for(char& bit : Bloque){
                bit = (bit == '0') ? '1' : '0';
            }
            primerBloque = false;
        }
        //Codifico el resto de bloques
        else{
            //Cuento cantidad de ceros y unos
            int ceros = 0, unos = 0;
            for(char bit : bloqueAnterior){
                if(bit == '0'){
                    ceros++;
                }
                else if(bit == '1'){
                    unos++;
                }
            }
            //Regla uno
            if(ceros == unos){
                for(char& bit : Bloque){
                    bit = (bit == '0') ? '1' : '0';
                }
            }

            //Regla dos
            else if(ceros > unos){
                for(int i = 0; i < n; i += 2){
                    if (i + 1 < n) {
                        Bloque[i + 1] = (Bloque[i + 1] == '0') ? '1' : '0';
                    }
                }
            }
            //Regla tres
            else{
                for(int i = 0; i < n; i += 3){
                    if (i + 2 < n) {
                        Bloque[i + 2] = (Bloque[i + 2] == '0') ? '1' : '0';
                    }
                }
            }
        }
        codificados += Bloque;
        bloqueAnterior = bloqueOriginal;
    }

    return codificados;
}

string segundoMetodo(const int n, string& str_binario){
    string codificados;
    unsigned int tamanio = str_binario.size();
    //Separo el contenido en n bits
    for(unsigned int i = 0; i < tamanio; i += n){
        string Bloque = str_binario.substr(i,n);
        //Desplazamiento circular a la derecha
        char ultimoBit = Bloque[n - 1];
        for(int j = n -1; j > 0; j--){
            Bloque[j] = Bloque[j-1];
        }
        Bloque[0] = ultimoBit;
        codificados += Bloque;
    }
    return codificados;
}
string codificar(const int n, string& str_binario,const int metodo){
    string codificado;
    if(metodo == 1){
        codificado = primerMetodo(n,str_binario);
    }
    else if(metodo == 2){
        codificado = segundoMetodo(n,str_binario);
    }
    else{
        cout << "Opcion no valida." << endl;
    }
    return codificado;
}



int main() {
    int n, opcion;
    string fileNameFuente, fileNameOut;
    cout << "Bienvenido al programa de codificacion de archivos." << endl;
    cout << endl << "Ingrese el valor de la semilla para codificar: " << endl;
    cin >> n;
    cout << "Ingrese el metodo de codificacion que desea (1 o 2): " << endl;
    cin >> opcion;
    cout << "Ingresa el nombre del archivo fuente: ";
    cin >> fileNameFuente;
    cout << "Ingresa el nombre del archivo de salida: ";
    cin >> fileNameOut;
    string contenido = caracterToBinario(fileNameFuente);
    cout << contenido;
    string codificado = codificar(n,contenido,opcion);
    escribirArchivo(fileNameOut, codificado, true);
    return 0;
}



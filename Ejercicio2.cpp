#include <iostream>
#include <string>
#include<fstream>
# include <bitset>

using namespace std;
void escribirArchivo(string& fileName, string& texto, bool limpiar=false)
{
    fstream archivo;
    if (limpiar) // Si limpiar es verdadero, se sobreescribe el archivo
    {
        archivo.open(fileName, ios::out | ios::trunc);
    }
    else // Si limpiar es falso, se agrega contenido al final del archivo
    {
        archivo.open(fileName, ios::out | ios::app);
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
string leerArchivoPorCaracter(string nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo\n";
        return "";
    }

    string contenido;
    char c;
    while (archivo.get(c))
    {
        contenido += c;
    }
    archivo.close();

    return contenido;
}
string primerMetodo(const int n,string& contenido, string& original){
    string decodificados;
    unsigned int tamanio = contenido.size();
    bool primerBloque = true;
    string bloqueAnterior;
    //Separo el contenido en n bits
    for(unsigned int i = 0; i < tamanio; i += n){
        string Bloque = contenido.substr(i,n);
        string bloqueOriginal = original.substr(i,n);
        //Decodifico el primer bloque
        if(primerBloque){
            for(char& bit : Bloque){
                bit = (bit == '0') ? '1' : '0';
            }
            primerBloque = false;
        }
        //Decodifico el resto de bloques
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
        decodificados += Bloque;
        bloqueAnterior = bloqueOriginal;
    }

    return decodificados;
}

string segundoMetodo(const int n, string& contenido){
    string decodificados;
    unsigned int tamanio = contenido.size();
    //Separo el contenido en n bits
    for(unsigned int i = 0; i < tamanio; i += n){
        string Bloque = contenido.substr(i,n);
        //Desplazamiento circular a la izquierda
        char primerBit = Bloque[0];
        for(int j = 0; j < n - 1; j++){
            Bloque[j] = Bloque[j + 1];
        }
        Bloque[n - 1] = primerBit;
        decodificados += Bloque;
    }
    return decodificados;
}

string decodificar(const int n, string& contenido, string& original,const int metodo){
    string decodificado;
    if(metodo == 1){
        decodificado = primerMetodo(n,contenido,original);
    }
    else if(metodo == 2){
        decodificado = segundoMetodo(n,contenido);
    }
    else{
        cout << "Opcion no valida." << endl;
    }
    return decodificado;
}


int main()
{
    int n, opcion;
    string fileNameFuente, fileNameOut;
    cout << "Bienvenido al programa de decodificacion de archivos." << endl;
    cout << endl << "Ingrese el valor de la semilla para decodificar: " << endl;
    cin >> n;
    cout << "Ingrese el metodo de decodificacion que desea (1 o 2): " << endl;
    cin >> opcion;
    cout << "Ingresa el nombre del archivo fuente: ";
    cin >> fileNameFuente;
    cout << "Ingresa el nombre del archivo de salida: ";
    cin >> fileNameOut;
    string contenido = leerArchivoPorCaracter(fileNameFuente);
    string decodificado;
    string archivoOriginal;
    cout << "Ingrese el archivo original sin codificar: ";
    cin >> archivoOriginal;
    string original = caracterToBinario(archivoOriginal);
    decodificado = decodificar(n,contenido,original,opcion);
    escribirArchivo(fileNameOut, decodificado, true);
    return 0;
}


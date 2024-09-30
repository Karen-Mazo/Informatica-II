#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
using namespace std;

string** usuarios = nullptr;
int cantidadUsuarios = 0;
//Funcion para conveirtir caracter a binario
string char2binario(string nombreArchivo)
{
    ifstream archivo;
    try
    {
        archivo.open(nombreArchivo);
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

// Funcione de codificacion
string codificar(const int n, string& str_binario){
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
// Funcion para encriptar toda la informacion
string encriptarInformacion(const int n, const string& documento, const string& clave, const string& saldo) {
    string datosConcat = documento + ";" + clave + ";" + saldo;
    string codificado = codificar(n, datosConcat);
    return codificado;
}

// Funcion para guardar la informacion
void guardarUsuariosCodificados(const int n, string** usuarios, int cantidadUsuarios) {
    ofstream archivoSudo("sudo.txt");
    if (!archivoSudo.is_open()) {
        cerr << "Error al abrir el archivo sudo.txt." << endl;
        return;
    }
    for (int i = 0; i < cantidadUsuarios; i++) {
        string documento = usuarios[i][0];
        string clave = usuarios[i][1];
        string saldo = usuarios[i][2];
        string datosCodificados = encriptarInformacion(n, documento, clave, saldo);
        archivoSudo << datosCodificados << endl;
    }

    archivoSudo.close();
}

string** cargarUsuarios(int& cantidadUsuarios, int& capacidad, string&  fileName) {
    ifstream archivo(fileName);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de usuarios." << endl;
        return nullptr;
    }

    string** usuarios = new string*[capacidad];
    for (int i = 0; i < capacidad; i++) {
        usuarios[i] = new string[3];
    }

    string linea;
    cantidadUsuarios = 0;
    while (getline(archivo, linea)) {
        if (cantidadUsuarios == capacidad) {
            capacidad *= 2;
            string** temp = new string*[capacidad];
            for (int i = 0; i < capacidad / 2; i++) {
                temp[i] = usuarios[i];
            }
            for (int i = capacidad / 2; i < capacidad; i++) {
                temp[i] = new string[3];
            }
            delete[] usuarios;
            usuarios = temp;
        }

        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        string cedula, clave, saldo;
        cedula = linea.substr(0, pos1);
        clave = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        saldo = linea.substr(pos2 + 1);

        usuarios[cantidadUsuarios][0] = cedula;
        usuarios[cantidadUsuarios][1] = clave;
        usuarios[cantidadUsuarios][2] = saldo;
        cantidadUsuarios++;
    }

    archivo.close();
    return usuarios;
}

// Funcion para validar la clave del administrador
bool validarAdministrador(const int n,  string& claveIngresada) {
    ifstream archivo("sudo.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo del administrador." << endl;
        return false;
    }
    string claveCodificada;
    getline(archivo, claveCodificada);
    archivo.close();
    string claveIngresadaCodificada = codificar(n, claveIngresada);
    if (claveIngresadaCodificada == claveCodificada){
        cout << "Acceso concedido." << endl;
        return true;
    }
    else{
        cout << "clave incorrecta." << endl;
    }
    return false;
}

//Funcion para guardar el usuario
void guardarUsuarios(string** usuarios, int cantidadUsuarios, string& fileName) {
    ofstream archivo(fileName);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de usuarios." << endl;
        return;
    }

    for (int i = 0; i < cantidadUsuarios; i++) {
        archivo << usuarios[i][0] << ";" << usuarios[i][1] << ";" << usuarios[i][2] << endl;
    }

    archivo.close();
}

// Funcion para registrar un nuevo usuario
void registrarUsuario() {
    string cedula, clave, saldo;
    cout << "Ingrese la cedula: ";
    cin >> cedula;
    cout << "Ingrese la clave: ";
    cin >> clave;
    cout << "Ingrese el saldo inicial: ";
    cin >> saldo;

    // Aumentar el tamaño del arreglo dinamico
    string** nuevoArreglo = new string*[cantidadUsuarios + 1];
    for (int i = 0; i < cantidadUsuarios; i++) {
        nuevoArreglo[i] = usuarios[i];
    }

    nuevoArreglo[cantidadUsuarios] = new string[3];
    nuevoArreglo[cantidadUsuarios][0] = cedula;
    nuevoArreglo[cantidadUsuarios][1] = clave;
    nuevoArreglo[cantidadUsuarios][2] = saldo;

    delete[] usuarios;
    usuarios = nuevoArreglo;
    cantidadUsuarios++;

    cout << "Usuario registrado exitosamente." << endl;
}

// Funcion para validar el acceso del usuario
int validarUsuario(string** usuarios, int cantidadUsuarios, const string& cedula, const string& clave) {
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i][0] == cedula && usuarios[i][1] == clave) {
            return i;
        }
    }
    return -1;
}
// Funcion para consultar el saldo del usuario
void consultarSaldo(string** usuarios, int indiceUsuario) {
    int saldo = stoi(usuarios[indiceUsuario][2]) - 1000;
    usuarios[indiceUsuario][2] = to_string(saldo);
    cout << "Su saldo actual es: " << saldo << " COP" << endl;
}

// Funcion para retirar dinero del usuario
void retirarDinero(string** usuarios, int indiceUsuario, int monto) {
    int saldo = stoi(usuarios[indiceUsuario][2]) - 1000;
    if (saldo >= monto) {
        saldo -= monto;
        usuarios[indiceUsuario][2] = to_string(saldo);
        cout << "Ha retirado: " << monto << " COP. Su saldo actual es: " << saldo << " COP" << endl;
    } else {
        cout << "Fondos insuficientes para realizar el retiro." << endl;
    }
}

// Funcion para actualizar los archivos
void actualizarArchivos(string** usuarios, int n, int cantidadUsuarios,  string& claveAdministrador, string& fileName) {
    guardarUsuarios(usuarios, cantidadUsuarios,fileName);
    ofstream archivoSudo("sudo.txt");
    if (!archivoSudo.is_open()) {
        cout << "Error al abrir el archivo del administrador." << endl;
        return;
    }
    archivoSudo << codificar(n,claveAdministrador) << endl;
    archivoSudo.close();
}

int main(){
    int capacidad = 3;
    int cantidadUsuarios = 0;
    const int n = 4;
    string fileName;
    cout << "\n\nBienvenido al programa del cajero automatico.";
    string** usuarios = cargarUsuarios(cantidadUsuarios, capacidad,fileName);

    string claveAdmin;
    cout << "Ingrese la clave del administrador: ";
    cin >> claveAdmin;

    if (!validarAdministrador(n,claveAdmin)) {
        cout << "Clave de administrador incorrecta." << endl;
        return 1;
    }

    // Menú para usuarios del sistema
    string cedula, clave;
    cout << "Ingrese su cedula: ";
    cin >> cedula;
    cout << "Ingrese su clave: ";
    cin >> clave;

    int indiceUsuario = validarUsuario(usuarios, cantidadUsuarios, cedula, clave);
    if (indiceUsuario == -1) {
        cout << "Usuario o clave incorrectos." << endl;
        return 1;
    }

    int opcion, monto;
    cout << "1. Consultar saldo\n2. Retirar dinero\nIngrese una opcion: ";
    cin >> opcion;

    if (opcion == 1) {
        consultarSaldo(usuarios, indiceUsuario);
    } else if (opcion == 2) {
        cout << "Ingrese el monto a retirar: ";
        cin >> monto;
        retirarDinero(usuarios, indiceUsuario, monto);
    }

    // Actualizar los archivos
    actualizarArchivos(usuarios, n,cantidadUsuarios, claveAdmin,fileName);

    // Liberar memoria
    for (int i = 0; i < capacidad; i++) {
        delete[] usuarios[i];
    }
    delete[] *usuarios;

    return 0;
}


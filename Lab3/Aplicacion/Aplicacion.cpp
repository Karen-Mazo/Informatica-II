#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
using namespace std;

//Definicion arreglo dinamico para los usuarios
string** usuarios = nullptr;
int capacidad = 0;
int cantidadUsuarios = 0;

//Funcion para leer el archivo por linea
string leerArchivoPorLinea(string nombreArchivo)
{
    fstream archivo(nombreArchivo, ios::in);
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo\n";
        return "";
    }

    string contenido;
    string linea;
    while (getline(archivo, linea))
    {
        contenido += linea + "\n";
    }
    archivo.close();

    return contenido;
}

string char2binario(string& texto) {
    string str_binario;
    for(char& bit : texto){
        bitset<8> bits(bit);
        str_binario += bits.to_string();
    }
    return str_binario;
}


void escribirArchivo(const string& fileName, const string& texto, bool limpiar=false)
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

//Funcion para organizar la informacion del usuario
string** estructuraUsuarios(string** usuarios, int& capacidad, int& cantidadUsuarios, const string& contenido) {
    int inicio = 0;
    int fin = contenido.find('\n', inicio);
    while (fin != -1) {
        string linea = contenido.substr(inicio, fin - inicio);
        int pos1 = linea.find(';');
        int pos2 = linea.find(';', pos1 + 1);
        // Si se encuentran los delimitadores
        if (pos1 != -1 && pos2 != -1) {
            string cedula = linea.substr(0, pos1);
            string clave = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            string saldo = linea.substr(pos2 + 1);
            // Expandir del arreglo
            if (cantidadUsuarios >= capacidad) {
                capacidad *= 2;
                string** nuevoArreglo = new string*[capacidad];
                // Copiar los datos al nuevo arreglo
                for (int i = 0; i < cantidadUsuarios; i++) {
                    nuevoArreglo[i] = new string[3];
                    for (int j = 0; j < 3; j++) {
                        nuevoArreglo[i][j] = usuarios[i][j];
                    }
                }
                // Liberar la memoria del arreglo antiguo
                for (int i = 0; i < cantidadUsuarios; i++) {
                    delete[] usuarios[i];
                }
                delete[] usuarios;
                // Apuntar al nuevo arreglo expandido
                usuarios = nuevoArreglo;
            }
            // Agregar el nuevo usuario al arreglo
            usuarios[cantidadUsuarios] = new string[3];
            usuarios[cantidadUsuarios][0] = cedula;
            usuarios[cantidadUsuarios][1] = clave;
            usuarios[cantidadUsuarios][2] = saldo;
            // Incrementar el numero de usuarios
            cantidadUsuarios++;
        }
        // Mover el inicio a la siguiente línea
        inicio = fin + 1;
        fin = contenido.find('\n', inicio);
    }
    return usuarios;
}

//Funcion para codificar
string codificarDos(const int n, string& str_binario){
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

//Funcion para decodificar
string decodificarDos(const int n, string& contenido){
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
/*
//Funcion para saber por cual metodo decodificar
int detectarMetodo(const int n, string& claveEncriptada, string& claveOriginal) {
    string resultadoPrimerMetodo = decodificarUno(n, claveEncriptada, claveOriginal);
    if (resultadoPrimerMetodo == claveOriginal) {
        return 1;
    }
    string resultadoSegundoMetodo = decodificarDos(n, claveEncriptada);
    if (resultadoSegundoMetodo == claveOriginal) {
        return 2;
    }
    return 0;
}
*/
//Funcion para codificar los usuarios
string codificarUsuarios(int n, string& binarioUsuarios) {
    string resultadoCodificado;
    resultadoCodificado = codificarDos(n,binarioUsuarios);
    return resultadoCodificado;
}

//Actualizar el archivo de usuarios
void actualizarArchivoUsuarios(const string& nombreArchivo, string** usuarios, int numUsuarios) {
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }
    for (int i = 0; i < numUsuarios; i++) {
        archivo << usuarios[i][0] << ";" << usuarios[i][1] << ";" << usuarios[i][2] << endl;
    }
    archivo.close();
    cout << "Archivo actualizado." << endl;
}

//Funcion para verificar la clave del administardor
bool verificarAdministrador(const int n, string& claveIngresada) {
    ifstream archivoSudo("sudo.txt");
    string claveEncriptada;
    if (archivoSudo.is_open()) {
        getline(archivoSudo, claveEncriptada);
        archivoSudo.close();
        string claveDesencriptada;
        claveDesencriptada = decodificarDos(n, claveEncriptada);
        return claveDesencriptada == claveIngresada;
    } else {
        cout << "No se pudo abrir el archivo de sudo." << endl;
        return false;
    }
}

//Funcion para consultar el saldo
void consultarSaldo(string** usuarios, int numUsuarios, const string& cedula) {
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i] != nullptr && !usuarios[i][0].empty()){
            if (usuarios[i][0] == cedula) {
                int saldoActual = stoi(usuarios[i][2]);
                cout << "\nSu saldo actual es: " << saldoActual << " COP" << endl;
                saldoActual -= 1000;
                usuarios[i][2] = to_string(saldoActual);
                return;
            }
        }
    }
    cout << "Usuario no encontrado." << endl;
}

// Funcion para retirar dinero
void retirarDinero(string** usuarios, int numUsuarios, const string& cedula, int cantidad) {
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i] != nullptr && !usuarios[i][0].empty()){
            if (usuarios[i][0] == cedula) {
                int saldoActual = stoi(usuarios[i][2]);
                // Verificar si hay suficiente saldo después de la tarifa
                if (cantidad + 1000 > saldoActual) {
                    cout << "\nFondos insuficientes. No puede retirar esta cantidad." << endl;
                } else {
                    saldoActual -= (cantidad + 1000); // Restar cantidad y costo de transacción
                    usuarios[i][2] = to_string(saldoActual);
                    cout << "\nRetiro exitoso. Ha retirado " << cantidad << " COP." << endl;
                    cout << "Nuevo saldo: " << usuarios[i][2] << " COP" << endl;
                    return;
                }
            }
        }
    }
    cout << "Usuario no encontrado." << endl;
}

void menuAdministrador() {
    int opcion;
    while(true){
        cout << "\nMenu de Administrador\n";
        cout << "1. Agregar usuario\n";
        cout << "2. Salir\n";
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:{
            string cedula,clave,saldo;
            cout << "Ingrese cedula: ";
            cin >> cedula;
            cout << "Ingrese clave: ";
            cin >> clave;
            cout << "Ingrese saldo inicial: ";
            cin >> saldo;
            // Agregar usuario
            if (cantidadUsuarios >= capacidad) {
                capacidad *= 2;
                string** nuevoArreglo = new string*[capacidad];
                for (int i = 0; i < cantidadUsuarios; i++) {
                    nuevoArreglo[i] = usuarios[i];
                }
                delete[] usuarios; // Liberar memoria del arreglo antiguo
                usuarios = nuevoArreglo; // Apuntar al nuevo arreglo
            }

            // Agregar el nuevo usuario al arreglo
            usuarios[cantidadUsuarios] = new string[3];
            usuarios[cantidadUsuarios][0] = cedula;
            usuarios[cantidadUsuarios][1] = clave;
            usuarios[cantidadUsuarios][2] = saldo;
            cantidadUsuarios++;
            actualizarArchivoUsuarios("usuarios.txt", usuarios, cantidadUsuarios);
            cout << "Usuario registrado." << endl;
            break;
        }
        case 2:
            cout << "Saliendo del menu de administrador...\n";
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
            break;
        }
        if (opcion == 2){
            break;
        }
    }
}

void menuUsuario(string**usuarios, int cantidadUsuarios,string& cedula) {
    int opcion;
    while(true){
        cout << "\nMenu de Usuario\n";
        cout << "1. Consultar saldo\n";
        cout << "2. Retirar dinero\n";
        cout << "3. Salir\n";
        cout << "Ingrese su opcion: ";
        cin >> opcion;
        switch (opcion) {
        case 1:
            consultarSaldo(usuarios, cantidadUsuarios, cedula);
            actualizarArchivoUsuarios("usuarios.txt",usuarios,cantidadUsuarios);
            break;
        case 2:
            int cantidad;
            cout << "Ingrese cantidad a retirar: ";
            cin >> cantidad;
            retirarDinero(usuarios, cantidadUsuarios, cedula, cantidad);
            actualizarArchivoUsuarios("usuarios.txt",usuarios,cantidadUsuarios);
            break;
        case 3:
            cout << "Saliendo del menu de usuario...\n";
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
            break;
        }
        if (opcion == 3){
            break;
        }
    }
}


int main(){
    capacidad = 1;
    usuarios = new string*[capacidad];
    for (int i = 0; i < capacidad; i++) {
        usuarios[i] = new string[3];
    }
    const int n = 4;
    // Cargar usuarios desde el archivo
    string contenido = leerArchivoPorLinea("usuarios.txt");
    usuarios = estructuraUsuarios(usuarios, capacidad, cantidadUsuarios, contenido);

    while (true) {
        cout << "1. Acceder como administrador" << endl;
        cout << "2. Acceder como usuario" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese su opcion: ";
        int opcion;
        cin >> opcion;

        switch (opcion) {
        case 1:{
            string claveAdmin;
            cout << "Ingrese la clave de administrador: ";
            cin >> claveAdmin;
            string binarioClave = char2binario(claveAdmin);
            bool admin = verificarAdministrador(n,binarioClave);
            if (admin) {
                cout << "Acceso concedido como administrador." << endl;
                menuAdministrador();
            }
            else {
                cout << "Clave incorrecta. Acceso denegado." << endl;
            }
            break;
        }
        case 2:{
            // Acceso como usuario
            string cedula, clave;
            cout << "Ingrese su cedula: ";
            cin >> cedula;
            cout << "Ingrese su clave: ";
            cin >> clave;
            // Validar usuario
            bool usuarioValido = false;
            for (int i = 0; i < cantidadUsuarios; i++) {
                if (usuarios[i][0] == cedula && usuarios[i][1] == clave) {
                    usuarioValido = true;
                    menuUsuario(usuarios,cantidadUsuarios,cedula);
                    break;
                }
            }
            if(!usuarioValido){
                cout << "Credenciales incorrectas." << endl;
            }
            break;
        }
        case 3:
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }
        if (opcion == 3){
            break;
        }
    }
    string contenidoUsuarios = leerArchivoPorLinea("usuarios.txt");
    string binarioUsuarios = char2binario(contenidoUsuarios);
    string usuariosCodificados = codificarUsuarios(n, binarioUsuarios);
    escribirArchivo("usuarioscodificados.bin", usuariosCodificados);

    // Liberar memoria
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i] != nullptr){
            delete[] usuarios[i];
        }
    }
    delete[] usuarios;

    return 0;
}



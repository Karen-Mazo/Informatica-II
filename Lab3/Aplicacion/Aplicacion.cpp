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
                capacidad += 1;
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


//Funciones para codificar
string codificarUno(const int n,string& str_binario){
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

//Funciones para decodificar
string decodificarUno(const int n,string& contenido, string& original){
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

//Funcion para saber por cual metodo deocodificar
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

//Funcion para codificar los usuarios
string codificarUsuarios(int n, string& binarioUsuarios, int metodo) {
    string resultadoCodificado;
    if (metodo == 1){
        resultadoCodificado = codificarUno(n,binarioUsuarios);
    }
    else if (metodo == 2){
        resultadoCodificado = codificarDos(n,binarioUsuarios);
    }
    else{
        cout << "Metodo de codificacion no valido." << endl;
        return "";
    }
    return resultadoCodificado;
}

//Funcion para decodificar clave de administrador
string decodificarClave(int n,string& contenido, string& original, int metodo){
    string claveDecodificada;
    if(metodo == 1){
        claveDecodificada = decodificarUno(n,contenido,original);
    }
    else if(metodo == 2){
        claveDecodificada = decodificarDos(n,contenido);
    }
    else{
        cout << "Metodo de decodificacion no valido." << endl;
        return "";
    }
    return claveDecodificada;
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
        // Verificar el metodo de codificación utilizado para desencriptar la clave
        int metodo = detectarMetodo(n, claveEncriptada, claveIngresada);

        string claveDesencriptada;

        if (metodo == 1) {
            claveDesencriptada = decodificarUno(n, claveEncriptada, claveIngresada);
        } else if (metodo == 2) {
            claveDesencriptada = decodificarDos(n, claveEncriptada);
        } else {
            return false;
        }
        return claveDesencriptada == claveIngresada;
    } else {
        cout << "No se pudo abrir el archivo de sudo." << endl;
        return false;
    }
}

//Funcion para consultar el saldo
void consultarSaldo(string** usuarios, int numUsuarios, const string& cedula) {
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i][0] == cedula) {
            int saldoActual = stoi(usuarios[i][2]);
            saldoActual -= 1000;
            usuarios[i][2] = to_string(saldoActual);
            cout << "Su saldo actual es: " << usuarios[i][2] << " COP" << endl;
            return;
        }
    }
    cout << "Usuario no encontrado." << endl;
}

// Funcion para retirar dinero
void retirarDinero(string** usuarios, int numUsuarios, const string& cedula, int cantidad) {
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i][0] == cedula) {
            int saldoActual = stoi(usuarios[i][2]);
            // Verificar si hay suficiente saldo después de la tarifa
            if (cantidad + 1000 > saldoActual) {
                cout << "Fondos insuficientes. No puede retirar esta cantidad." << endl;
            } else {
                saldoActual -= (cantidad + 1000); // Restar cantidad y costo de transacción
                usuarios[i][2] = to_string(saldoActual);
                cout << "Retiro exitoso. Ha retirado " << cantidad << " COP." << endl;
                cout << "Nuevo saldo: " << usuarios[i][2] << " COP" << endl;
            }
            return;
        }
    }
    cout << "Usuario no encontrado." << endl;
}

void menuAdministrador() {
    int opcion;
    cout << "Menu de Administrador\n";
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
            capacidad += 1;
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
}

void menuUsuario(string**usuarios, int cantidadUsuarios,string& cedula) {
    int opcion;
    cout << "Menu de Usuario\n";
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
}


int main(){
    capacidad = 1;
    usuarios = new string*[capacidad];
    for (int i = 0; i < capacidad; i++) {
        usuarios[i] = new string[3];
    }
    const int n = 4;
    int metodo = 0;
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
            string claveEncriptada = leerArchivoPorLinea("sudo.txt");
            string binarioClave = char2binario(claveAdmin);
            bool admin = verificarAdministrador(n,binarioClave);
            metodo = detectarMetodo(n,claveEncriptada,binarioClave);
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

    if (metodo !=0 ) {
        // Leer el contenido de "usuarios.txt" y convertirlo a binario
        string contenidoUsuarios = leerArchivoPorLinea("usuarios.txt");
        string binarioUsuarios = char2binario(contenidoUsuarios);

        // Codificar los usuarios usando el metodo detectado
        string usuariosCodificados = codificarUsuarios(n, binarioUsuarios,metodo);

        // Guardar los usuarios codificados en "usuarioscodificados.txt"
        escribirArchivo("usuarioscodificados.txt", usuariosCodificados);
    } else {
        cout << "No se codifico la informacion, metodo de codificacion no valido." << endl;
    }

    // Liberar memoria
    for (int i = 0; i < cantidadUsuarios; i++) {
        delete[] usuarios[i];
    }
    delete[] usuarios;

    return 0;
}



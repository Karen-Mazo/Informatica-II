// Escribe un programa que reciba un número y halla
//la suma de todos los números amigables menores al número ingresado.
int sumaDivisores(int num) {
    int suma = 0;
    for (int i = 1; i < num; i++) {
        if (num % i == 0) {
            suma += i;
        }
    }
    return suma;
}

void setup() {
    Serial.begin(9600); 
    while (!Serial) {
    }
    int limite;
    Serial.println("Ingrese un numero: ");
    while (Serial.available() == 0) {
    }
    limite = Serial.parseInt(); 
    
    int sumaAmigables = 0;
    for (int a = 1; a < limite; a++) {
        int b = sumaDivisores(a);  
        
        if (b != a && b < limite && sumaDivisores(b) == a) {
            sumaAmigables += a; 
            Serial.print("Numeros amigables encontrados: ");
            Serial.print(a);
            Serial.print(" y ");
            Serial.println(b);
        }
    }
    Serial.print("El resultado de la suma es: ");
    Serial.println(sumaAmigables);
}

void loop() {
}
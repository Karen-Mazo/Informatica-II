// Se necesita un programa que permita determinar la mínima combinación de billetes y monedas para una
//cantidad de dinero determinada. Los billetes en circulación son de $50.000, $20.000, $10.000, $5.000, $2.000 y
//$1.000, y las monedas son de $500, $200, $100 y $50. Haz un programa que entregue el número de billetes y
//monedas de cada denominación para completar la cantidad deseada. Si por medio de los billetes y monedas
//Universidad de Antioquia · Facultad de Ingeniería disponibles 
//no se puede lograr la cantidad deseada, el sistema deberá decir lo que resta para lograrla. Usa arreglos
//y ciclos para realizar el programa.

unsigned int cantidad;

void setup()
{
  Serial.begin(9600);
  delay(2000);
  Serial.println("Ingrese la cantidad de dinero: ");
}

void loop()
{
  if (Serial.available() > 0){
  	cantidad = Serial.parseInt();
    if (cantidad < 0){
     Serial.println("Cantidad invalida.");
     return;
    }
    unsigned int billetes[] = {50000,20000,10000,5000,2000,1000,500,200,100,50};
    unsigned int cantidadBilletes[10] = {0};
    for (int i = 0; i < 10; i++){
    	cantidadBilletes[i] = cantidad / billetes[i];
      	cantidad  = cantidad % billetes[i];
    }
    for (int i = 0; i < 10; i++){
    	Serial.print(billetes[i]);
      	Serial.print(": ");
      	Serial.println(cantidadBilletes[i]);
    }
    Serial.print("Faltante: ");
    Serial.println(cantidad);
    Serial.println("\nIngrese otra cantidad de dinero: ");
    delay(1000);
  }
}
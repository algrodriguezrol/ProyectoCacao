#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <max6675.h>
#include <SHT1x.h>

#include "millisAlbin.h"
#include "printAlbin.h"

//#define SALIDA_LEDROJO_PIN    1
#define ARRANQUE_PIN          2
//#define PARO_PIN            3
#define SOMAX1_PIN            3
#define CSMAX1_PIN            4
#define SCKMAX1_PIN           5
#define SOMAX2_PIN            6
#define CSMAX2_PIN            7
#define SCKMAX2_PIN           8
//#define CONFIG_TCDO_PIN     4
//#define CONFIG_TCCS_PIN     5
//+#define CONFIG_TCSCK_PIN   6
//#define CONFIG_TCGND_PIN    8
//#define CONFIG_TCVCC_PIN    9
#define clockPin              9
#define dataPin               10
#define DATADHT_PIN           11
#define SALIDA_LEDVERDE_PIN   12
#define SALIDA_MOTOR_PIN      13

#define DHTTYPE DHT11

int arranque=0;       //Arranque de Motor
int enclavamiento=0;  //Enclavamiento de Motor
int paro=0;           //Paro del Modor
int estado=0;         //Estado de comprobacion para el arranque



//String datos;

myMillis MM;
myMillis MM2;
myMillis MM3;
myMillis MM4;
myMillis MM5;


SHT1x sht1x(dataPin, clockPin);

DHT dht(DATADHT_PIN, DHTTYPE);

MAX6675 thermocouple(SCKMAX1_PIN, CSMAX1_PIN, SOMAX1_PIN);
MAX6675 thermocouple2(SCKMAX2_PIN, CSMAX2_PIN, SOMAX2_PIN);

/*struct printAlbin{
  void printDATA(){
     Serial.print(temp_c);
           Serial.print(",");
           Serial.print(temp_f);
           Serial.print(",");
           Serial.print(humidity);
           Serial.print(",");
  };
};
*/
printAlbin printA;


void setup() {
  Serial.begin(9600);
  pinMode(ARRANQUE_PIN,INPUT);
  //pinMode(PARO_PIN, INPUT);
  pinMode(SALIDA_LEDVERDE_PIN, OUTPUT);
  //pinMode(SALIDA_LEDROJO_PIN, OUTPUT);
  pinMode(SALIDA_MOTOR_PIN, OUTPUT);

  dht.begin();

delay(500);
      
}

void loop() {

  arranque=digitalRead(ARRANQUE_PIN);
  //paro=digitalRead(PARO_PIN);
  enclavamiento=estado;

  temp_c = sht1x.readTemperatureC();
  temp_f = sht1x.readTemperatureF();
  humidity = sht1x.readHumidity();
  
  dhth = dht.readHumidity();
  dhtt = dht.readTemperature();
  dhtf = dht.readTemperature(true);
  hif = dht.computeHeatIndex(dhtf, dhth);
  hic = dht.computeHeatIndex(dhtt, dhth, false);

  tempCmax1 = thermocouple.readCelsius();
  tempFmax1 = thermocouple.readFarenheit();
  
  tempCmax2 = thermocouple2.readCelsius();
  tempFmax2 = thermocouple2.readFarenheit();

  //datos = temp_c + "," + temp_f + "," + humidity;

  /*if(isnan(dhth)||isnan(dhtt)||isnan(dhtf)){
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
    };*/
  
if(MM2.get() > 20000){
  if(MM4.get() > 21900000){
    Serial.println("Pasaron 21900 Veces");
    MM2.reset();
  }else{
  if (Serial.available() >= 0 ){
    if(MM.get() > 10000){
      printA.printDATA();
      
      MM.reset();
      };
    };
  };
  }else{
    Serial.println("Tiempo de fermentacion");
    digitalWrite(SALIDA_MOTOR_PIN, LOW);
    digitalWrite(SALIDA_LEDVERDE_PIN, LOW);
    MM.reset();
    MM3.reset();
    MM4.reset();
    //Serial.print(MM.get());
  };


if(arranque==HIGH){
    Serial.println("Arranque encendido");
    estado=1;
};


while (MM3.get() < 200000 && MM3.get() > 100000 ){
  digitalWrite(SALIDA_MOTOR_PIN, HIGH);
  digitalWrite(SALIDA_LEDVERDE_PIN, HIGH);
  printA.printDATAB();
  delay(5000);
};

if(MM3.get() > 200000){
  Serial.println("Pasaron 30 Lecturas");
  digitalWrite(SALIDA_MOTOR_PIN, LOW);
  digitalWrite(SALIDA_LEDVERDE_PIN, LOW);
  Serial.println("Salida del motor low");
  printA.printDATA();
  MM.reset();
  MM3.reset();
}

/*if(estado==1){
    digitalWrite(SALIDA_MOTOR_PIN, LOW); 
    Serial.println("Salida del motor baja");
    delay(7000);
    digitalWrite(SALIDA_MOTOR_PIN, HIGH);
    Serial.println("Salida del motor high"); 
    Serial.println(SALIDA_MOTOR_PIN);
  }
    else {
    digitalWrite(SALIDA_MOTOR_PIN,HIGH);
    //Serial.println("Salida del motor high");
    //Serial.println(SALIDA_MOTOR_PIN);  
 };*/
  if(paro==HIGH){
    estado=0;
    //Serial.println(SALIDA_MOTOR_PIN);
  }

  if(temp_c >= 50){
    digitalWrite(SALIDA_MOTOR_PIN, LOW);
    digitalWrite(SALIDA_MOTOR_PIN, LOW);
    }else{
    digitalWrite(SALIDA_MOTOR_PIN, HIGH);
    digitalWrite(SALIDA_MOTOR_PIN, HIGH); 
   }

//delay(1000);
}  

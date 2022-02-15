import serial
import time
import datetime

arduino = serial.Serial('/dev/ttyACM0',9600)
encabezado = " Timestamp, SHT Temp C°, SHT Temp F°, SHT Hume %, DHT Temp C°, DHT Temp F°, DHT Hume %, I. Calor C°, I. Calor F°, MAX1 Temp C°, MAX1 Temp F°, MAX2 Temp C°, MAX2 Temp F°\n"


def crearArchivoCSV():
  filename = "registroCacao.csv"    
  csv = open(filename, 'w')
  csv.write(encabezado)
  csv.close
  
def crearArchivoTXT():
  filename2 = "registroCacao.txt"    
  file = open(filename2, 'w')
  file.write(encabezado)
  file.close()
  
#ef algoritmoDeAprendizaje():
  
crearArchivoCSV();
crearArchivoTXT();

while True:
  cadena=arduino.readline()
  filename = "registroCacao.csv"
  filename2 = "registroCacao.txt" 
  localtime = time.asctime(time.localtime(time.time()))
  if (cadena.decode() != ''):
    #time.sleep(2)
    csv = open(filename,'a')
    dato = localtime + "," + cadena.decode() #+ "\n"
    csv.write(dato)
    file = open(filename2, 'a')
    file.write(dato)
    print(cadena.decode())
    print("Actual hora local :", localtime)

archivo.close()
arduino.close()
csv.close()      
file.close()


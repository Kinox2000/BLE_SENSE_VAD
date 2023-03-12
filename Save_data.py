#Script para recolectar datos del puerto serie
import keyboard
import serial

samples = 16000
puerto = "COM3"
baud = 115200
nombre_archivo = "Data.pcm"

print("Conectando al arduino")
serial_data = serial.Serial(puerto, baud)
print("Conectado al arduino")
print("Conectado al puerto: "+puerto)


#file = open(nombre_archivo, "a")
#file.close()

print("Archivo creado")
print("Importando Datos")

while True:
    file = open(nombre_archivo, "a+")
    file.write(str(serial_data.readline())[2:][:-5]+"\n")
     #file.close()


    






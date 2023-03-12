
#include <PDM.h>//Library used to manage the microphone
#include <SPI.h>//Library used to enable SPI communication 
#include <SD.h>//Library used to manage SD read and write

uint CS = 4;
static const int sampling_rate = 16000;
static const int segundos = 200;
short sampleBuffer[512];//en donde se almacenan las muestras, cada muestra es de 16 bits. Acá se almacenan 128 muestras de 16 bits.
short audio[16000*1];                       //son 16 bits porque ese es el tamaño de un short
int samplesRead;
int contador = 0;

int speedMaximum = 3200000;

SPISettings mySetting(speedMaximum, MSBFIRST, SPI_MODE0);


//LEDs pin definition
#define RED 22
#define GREEN 23
#define BLUE 24

//File in which audio samples will be stored
File audio_samples;


void setup() {

  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  Serial.println("Inicio del programa");
  Serial.println("Esperando 5 s para comenzar la grabación");
  digitalWrite(RED,LOW);
  digitalWrite(BLUE,LOW);
  digitalWrite(GREEN,HIGH);

  delay(5000);

  
  digitalWrite(RED,HIGH);
  digitalWrite(BLUE,HIGH);
  digitalWrite(GREEN,LOW);

  // configure the data receive callback
  PDM.onReceive(onPDMdata);
  PDM.setBufferSize(512);//tamaño del buffer, está en bytes

  PDM.setGain(0);

  if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    while (1);
  }


  

  // re-open the file for reading:
  //audio_samples = SD.open("Audio.txt");
  //if (audio_samples) {
    //Serial.println("Datos leídos:");

    // read from the file until there's nothing else in it:
    //while (audio_samples.available()) {
      //Serial.write(audio_samples.read());
    //}
    // close the file:
    //audio_samples.close();
  //} else {
    // if the file didn't open, print an error:
    //Serial.println("Error al leer el archivo");
  //}

  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM!");
    while (1);
  }

  audio_samples = SD.open("Audio.txt", FILE_WRITE);
    if (audio_samples) {
    Serial.print("Archivo abierto");
  
    // close the file:
  } else {
  // if the file didn't open, print an error:
  Serial.println("Error al abrir el archivo");
  }
}

void loop() {
  if (samplesRead) { 
    for (int i = 0; i<samplesRead; i++){
      //audio[contador] = sampleBuffer[i];
      //Serial.println(sampleBuffer[i])+32,768;
      audio_samples.write(sampleBuffer[i]);

      contador = contador +1;

    }    
    // clear the read count
    samplesRead = 0;   

  }


  if(contador >= sampling_rate*segundos){
    //PDM.end();
    audio_samples.close();
    digitalWrite(RED,HIGH);
    digitalWrite(BLUE,LOW);
    digitalWrite(GREEN,HIGH);
    while(1);
  }  
}



void onPDMdata() {
  // query the number of bytes available

  int bytesAvailable = PDM.available();//Indica cuántos bytes hay disponibles para leer 

  // read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);//samplebuffer: en donde se guardan las muestras
                                         //bytesAvailable: bytes que se van a leer

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable/2; //Se divide entre dos porque cada muestra es de 16 bits y la función PDM.read devuelve la cantidad de bytes
  //samplesRead = bytesAvailable;

}
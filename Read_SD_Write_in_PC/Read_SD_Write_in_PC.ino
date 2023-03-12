#include <SPI.h>//Library used to enable SPI communication 
#include <SD.h>//Library used to manage SD read and write

uint CS = 4;
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
  Serial.println("Esperando 25 s para comenzar la transmisión");
  digitalWrite(RED,LOW);
  digitalWrite(BLUE,LOW);
  digitalWrite(GREEN,HIGH);

  delay(25000);

  
  digitalWrite(RED,HIGH);
  digitalWrite(BLUE,HIGH);
  digitalWrite(GREEN,LOW);


  if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    while (1);
  }

  audio_samples = SD.open("Audio.txt");

}

void loop() { 
  if (audio_samples) {
    Serial.println("Leyendo:");

    // read from the file until there's nothing else in it:
    while (audio_samples.available()) {
      Serial.println(audio_samples.read());
    }
    digitalWrite(GREEN,HIGH);
    audio_samples.close();
  } else {
      Serial.println("Error al leer el archivo");
  }

}

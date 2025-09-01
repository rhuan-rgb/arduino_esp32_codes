#include <math.h>
#include "AdafruitIO_WiFi.h"

#define pinNTC 34
#define pinLed 14 //pino do led


// CONFIGURÇÕES DA REDE WIFI
#define WIFI_SSID ""
#define WIFI_PASS ""

// Autenticação Adafruit IO
// #define IO_USERNAME ""
// #define IO_KEY ""

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Controle de envio de dados
float temp_atual = 0;
float temp_anterior = -1;

// variavel para referenciar o feed temperatura
AdafruitIO_Feed *temperatura = io.feed("temperatura");


const float Rfixo = 10000.0;  //resistor do projeto
const float Beta = 3950.0;
const float R0 = 10000.0;        //nominal do ntc(sensor)
const float T0_kelvin = 298.15;  //25°C em kelvin
const float Vcc = 3.3;

void setup() {
 
  Serial.begin(115200);
  pinMode(pinLed, OUTPUT);
  pinMode(pinNTC, INPUT);
  delay(1000);

  while (!Serial);
    

  Serial.print("Conectando as Adafruit IO");
  io.connect();

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // mostra status conexão
  Serial.println();
  Serial.println(io.statusText());

  // configuração do CallBack, quando o feed receber(atualizar) um valor
  temperatura -> onMessage(handleTemperatura);
  //registra a função de callback 
  //ela deverá chamada sempre que o feed receber um novo dado
}

void loop() {

  // Manter a conexão com o Adafruit IO ativa
  io.run();
  //publicacao(); //chamada da função publish
  delay(3000);
}

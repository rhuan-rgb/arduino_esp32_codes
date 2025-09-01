#include <math.h>
#include "AdafruitIO_WiFi.h"


// Configurações da rede WIFI
#define WIFI_SSID ""
#define WIFI_PASS ""

// Autenticação Adafruit IO
#define IO_USERNAME ""
#define IO_KEY ""

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#define pinNTC 34

// Controle de envio de dados
float temp_atual = 0;
float temp_anterior = -1;

// Variável / Ponteiro para referenciar o feed temperatura
AdafruitIO_Feed * temperatura = io.feed("temperatura");

const float Rfixo = 10000.0; // resistor do projeto
const float Beta = 3950.0;
const float R0 = 10000.0; // nominal do ntc
const float T0_kelvin = 298.15; // 25°C em Kelvin
const float Vcc = 3.3;

float lerTemperaturaNTC(int pino, int numLeituras){
  long somaLeituras = 0;

  for(int i = 0; i < numLeituras; i++){
    somaLeituras += analogRead(pino);
    delay(5);
  }

  float leituraMedia = somaLeituras / (float)numLeituras;

  float Vout = leituraMedia * (Vcc / 4095.0);

  float Rntc = Rfixo * ((Vcc / Vout) - 1.0);
  
  float tempK = 1.0 / ((1.0 / T0_kelvin) + (1.0 / Beta) * log(Rntc / R0));

  return tempK - 273.15;
}

void setup() {
  pinMode(pinNTC, INPUT);

  Serial.begin(115200);

  while(!Serial);

  Serial.print("Conectando ao Adafruit IO");
  io.connect();

  while(io.status() < AIO_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

  delay(1000);

}

void loop() {

  // Manter a conexão com o Adafruit IO ativa
  io.run();

  temp_atual = lerTemperaturaNTC(pinNTC, 10);

  // Verificando alteração na temperatura
  if(temp_atual == temp_anterior){
    return;
  }


  // Serial.print("Temperatura Analógica: ");
  // Serial.println(analogRead(pinNTC));

  Serial.print(F("Temperatura: "));
  Serial.print(temp_atual, 2);
  Serial.println(F("°C"));

  // Envio / Registro no feed "temperatura" no Adafruit IO
  temperatura -> save(temp_atual);

  temp_anterior = temp_atual;

  delay(3000);

}

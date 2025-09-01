#include <math.h>
#include "AdafruitIO_WiFi.h"


// Configurações da rede WIFI
#define WIFI_SSID "IIIII"
#define WIFI_PASS "bonas231"

// Autenticação Adafruit IO
#define IO_USERNAME ""
#define IO_KEY ""

AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

#define pinLed 14 //Pino do LED

AdafruitIO_Feed *botaoled = io.feed("botaoled");

void setup() {
  pinMode(pinLed, OUTPUT);

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

  // Configuração do callack, quando o feed receber(atualizar) um valor
  botaoled -> onMessage(handleBotaoLed);
  // Registra a função de callback
  // Ela será chamada sempre que o feed receber um novo dado

}

void loop() {

  // Manter a conexão com o Adafruit IO ativa
  io.run();

  // Chamada da função publish
  // publicacao();

  delay(3000);

}
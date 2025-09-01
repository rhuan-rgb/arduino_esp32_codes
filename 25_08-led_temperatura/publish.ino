float lerTemperaturaNTC(int pino, int numLeituras) {
  long somaLeituras = 0;
  for (int i = 0; i < numLeituras; i++) {
    somaLeituras += analogRead(pino);
    delay(5);
  }


  float leituraMedia = somaLeituras / (float)numLeituras;

  float Vout = leituraMedia * (Vcc / 4095.0);

  float Rntc = Rfixo * ((Vcc / Vout) - 1.0);

  float tempK = 1.0 / ((1.0 / T0_kelvin) + (1.0 / Beta) * log(Rntc / R0));

  return tempK - 273.15;
}

void publicacao(){
   temp_atual = lerTemperaturaNTC(pinNTC, 10);

  // verificando alteração na temperatura
  if (temp_atual == temp_anterior){
    return;
  }

    // Serial.print("Temperatura Analógica: ");
    // Serial.println(analogRead(pinNTC));

  Serial.print(F("Temperatura enviada: "));
  Serial.print(temp_atual, 2);
  Serial.println(F("°C"));

  // envio / registro no feed "temperatura" no adafruit io
  temperatura ->save(temp_atual);

  temp_anterior = temp_atual;

}
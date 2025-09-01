// função chamada automaticamente quando o feed recebar atualizações
void handleTemperatura(AdafruitIO_Data *data){
  float temp = data -> toFloat();

  Serial.print(F("Temperatura do feed: "));
  Serial.println(temp, 2);
  Serial.println("°C");

  if(temp <= 0 ){
    digitalWrite(pinLed, HIGH);
  }                                   
  else{
    digitalWrite(pinLed, LOW);
  }
}

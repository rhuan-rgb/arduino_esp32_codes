void handleAlarme(AdafruitIO_Data *data) {
  String valor = data->toString();

  Serial.print(F("valor recebido do feed: "));
  Serial.println(valor);

  if (valor == "true") {
    alarmeAtivo = true;
    Serial.println("Alarme ARMADO pelo dashboard / app");
  } else {
    alarmeAtivo = false;
    Serial.println("Alarme DESARMADO pelo dashboard / app");
  }
}

void ativarAlerta() {
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_ALARME, HIGH);
}

void desligarAlerta() {
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_ALARME, LOW);
}
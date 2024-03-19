#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "MDNSHandler.h"

const char* ssid = "MOITILAS";
const char* password = "caipirinha";
ESP8266WebServer server(80);
MDNSHandler mdnsHandler("esp01");

void handleConfigurar() {
  // Implementar lógica de configuração
  server.send(200, "application/json", "{\"message\": \"Configuração atualizada\"}");
}

void handleStatus() {
  // Implementar lógica de status
  server.send(200, "application/json", "{\"message\": \"Status enviado\"}");
}

void handleControlarBomba() {
  // Implementar controle das bombas
  server.send(200, "application/json", "{\"message\": \"Comando de bomba enviado\"}");
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Definindo rotas
  if (mdnsHandler.begin()){
      server.on("/", HTTP_GET, []() {server.send(200, "text/plain", "Servidor ESP01 ativo!");});
      server.on("/configurar", HTTP_GET, handleConfigurar);
      server.on("/status", HTTP_GET, handleStatus);
      server.on("/controlarBomba", HTTP_GET, handleControlarBomba);
      server.begin();
      Serial.println("Servidor HTTP iniciado");
  }
}

void loop() {
  server.handleClient(); // Manipula clientes do servidor Web
  MDNS.update();  
}


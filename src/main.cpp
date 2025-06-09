#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "MDNSHandler.h"

const char* ssid = "MOITILAS";
const char* password = "caipirinha";
ESP8266WebServer server(80);
MDNSHandler mdnsHandler("lagoMoita");

void handleConfigurar() {
  // Implementar lógica de configuração
  server.send(200, "application/json", "{\"message\": \"Configuração atualizada\"}");
}

void handleStatus() {
  // Implementar lógica de status
  server.send(200, "application/json", "{\"message\": \"Status enviado\"}");
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
  server.on("/", HTTP_GET, []() {server.send(200, "text/plain", "Servidor ESP01 ativo!");});
  server.on("/config", HTTP_POST, handleConfigurar);
  server.on("/status", HTTP_GET, handleStatus);
  server.begin();
  Serial.println("Servidor HTTP iniciado");

  if (!mdnsHandler.begin()) {
      Serial.println("mDNS desativado");
  }
}

void loop() {
  server.handleClient(); // Manipula clientes do servidor Web
  if (mdnsHandler.started()) {
    MDNS.update();
  }
}


#include "MDNSHandler.h"

MDNSHandler::MDNSHandler(const char* hostname) : _hostname(hostname) {}

bool MDNSHandler::begin() {
    if (!MDNS.begin(_hostname)) { // Use _hostname aqui
        Serial.println("Erro ao configurar o mDNS");
        return false;
    }
    Serial.print("mDNS configurado para ");
    Serial.println(_hostname);
    return true;
}

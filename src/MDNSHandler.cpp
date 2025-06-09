#include "MDNSHandler.h"

MDNSHandler::MDNSHandler(const char* hostname) : _hostname(hostname) {}

bool MDNSHandler::begin() {
    _started = MDNS.begin(_hostname);
    if (!_started) {
        Serial.println("Erro ao configurar o mDNS");
        return false;
    }
    Serial.print("mDNS configurado para ");
    Serial.println(_hostname);
    return true;
}

bool MDNSHandler::started() const {
    return _started;
}

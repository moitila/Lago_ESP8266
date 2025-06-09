// MDNSHandler.h
#ifndef MDNSHANDLER_H
#define MDNSHANDLER_H

#include <ESP8266mDNS.h>

class MDNSHandler {
public:
    MDNSHandler(const char* hostname);
    bool begin();
    bool started() const; // indica se o mDNS iniciou corretamente
private:
    const char* _hostname;
    bool _started = false;
};

#endif

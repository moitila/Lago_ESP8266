// MDNSHandler.h
#ifndef MDNSHANDLER_H
#define MDNSHANDLER_H

#include <ESP8266mDNS.h>

class MDNSHandler {
public:
    MDNSHandler(const char* hostname);
    bool begin();
private:
    const char* _hostname;    
};

#endif

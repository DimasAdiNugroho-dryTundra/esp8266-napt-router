#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <ESP8266WiFi.h>
#include <lwip/napt.h>
#include <lwip/dns.h>
#include "ConfigManager.h"

class NetworkManager {
public:
    NetworkManager(ConfigManager& config);

    // Setup interface AP & STA
    void begin();
    
    // Routine check untuk re-enable NAT jika koneksi drop
    void loop();

    // Status helpers
    bool isNatActive();
    String getApIP();
    int getClientCount();

private:
    ConfigManager& _config;
    bool _natConfigured;
    unsigned long _lastCheck;
    
    // Default AP Credentials
    const char* _apSSID = "ESP8266_Repeater";
    const char* _apPass = "12345678";

    // Internal methods
    bool _enableNAT();
};

#endif
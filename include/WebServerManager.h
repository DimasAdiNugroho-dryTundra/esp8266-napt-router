#ifndef WEB_SERVER_MANAGER_H
#define WEB_SERVER_MANAGER_H

#include <ESP8266WebServer.h>
#include "NetworkManager.h"
#include "ConfigManager.h"
#include "WebAssets.h"

class WebServerManager {
public:
    WebServerManager(NetworkManager& netParams, ConfigManager& config);
    
    void begin();
    void handleClient();

private:
    ESP8266WebServer _server;
    NetworkManager& _netParams;
    ConfigManager& _config;

    // Route Handlers
    void _handleRoot();
    void _handleSave();
    void _handleScan();
    void _handleRestart();
    
    // Template Processor
    String _processor(const String& var);
};

#endif
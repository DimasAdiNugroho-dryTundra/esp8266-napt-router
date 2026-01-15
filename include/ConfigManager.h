#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <Arduino.h>
#include <LittleFS.h>

struct SystemConfig {
    String sta_ssid;
    String sta_pass;
};

class ConfigManager {
public:
    SystemConfig data;

    // Inisialisasi filesystem
    void begin();
    
    // Load config dari non-volatile memory
    void load();
    
    // Simpan config baru dan commit ke flash
    void save(const String& ssid, const String& pass);

private:
    const char* _configFile = "/cfg.txt";
};

#endif
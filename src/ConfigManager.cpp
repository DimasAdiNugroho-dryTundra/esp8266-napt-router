#include "ConfigManager.h"

void ConfigManager::begin() {
    if (!LittleFS.begin()) {
        // Format ulang jika mounting gagal (corruption safety)
        LittleFS.format();
        LittleFS.begin();
    }
}

void ConfigManager::load() {
    if (LittleFS.exists(_configFile)) {
        File f = LittleFS.open(_configFile, "r");
        if (f) {
            data.sta_ssid = f.readStringUntil('\n');
            data.sta_pass = f.readStringUntil('\n');
            
            // Sanitasi string dari karakter whitespace sisa
            data.sta_ssid.trim();
            data.sta_pass.trim();
            f.close();
        }
    }
}

void ConfigManager::save(const String& ssid, const String& pass) {
    File f = LittleFS.open(_configFile, "w");
    if (f) {
        f.printf("%s\n%s", ssid.c_str(), pass.c_str());
        f.close();
    }
}
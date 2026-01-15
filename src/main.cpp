/**
 * ESP8266 NAT Router Pro
 * Modularized Architecture
 * * Entry point untuk inisialisasi sistem.
 */

#include <Arduino.h>
#include "ConfigManager.h"
#include "NetworkManager.h"
#include "WebServerManager.h"

// Instansiasi Global Objects
ConfigManager configManager;
NetworkManager networkManager(configManager);
WebServerManager webServer(networkManager, configManager);

void setup()
{
  // Setup Serial untuk debugging
  Serial.begin(115200);
  delay(100);
  Serial.println("\n[SYS] Booting ESP8266 NAT Router Pro...");

  // 1. Load Konfigurasi
  configManager.begin();
  configManager.load();

  // 2. Setup Jaringan (L3 Switching & NAT)
  networkManager.begin();

  // 3. Setup Web Dashboard
  webServer.begin();

  Serial.println("[SYS] System Ready.");
}

void loop()
{
  // Main Loop: Handle HTTP request & Network maintenance
  webServer.handleClient();
  networkManager.loop();
}
#include "NetworkManager.h"

#define NAPT_TABLE_SIZE 1000
#define NAPT_PORT_RANGE 10

NetworkManager::NetworkManager(ConfigManager& config) 
    : _config(config), _natConfigured(false), _lastCheck(0) {}

void NetworkManager::begin() {
    // Optimasi PHY Layer untuk throughput maksimal
    WiFi.setPhyMode(WIFI_PHY_MODE_11N);
    WiFi.mode(WIFI_AP_STA);

    // Konfigurasi Subnetting Class A (10.x.x.x)
    // Digunakan untuk menghindari collision dengan subnet router umum (192.168.x.x)
    IPAddress apIP(10, 10, 10, 1);
    IPAddress apGateway(10, 10, 10, 1);
    IPAddress apSubnet(255, 255, 255, 0);

    WiFi.softAPConfig(apIP, apGateway, apSubnet);
    WiFi.softAP(_apSSID, _apPass);

    Serial.printf("[NET] AP Started: %s | IP: %s\n", _apSSID, WiFi.softAPIP().toString().c_str());

    // Inisiasi koneksi ke Uplink jika kredensial tersedia
    if (_config.data.sta_ssid.length() > 0) {
        WiFi.begin(_config.data.sta_ssid.c_str(), _config.data.sta_pass.c_str());
        Serial.println("[NET] Connecting to Uplink...");
    }
}

bool NetworkManager::_enableNAT() {
    if (WiFi.status() != WL_CONNECTED) return false;

    // Reset NAT table jika sudah pernah dikonfigurasi
    if (_natConfigured) {
        ip_napt_enable_no(SOFTAP_IF, 0);
    }

    // Inisialisasi LwIP NAPT
    ip_napt_init(NAPT_TABLE_SIZE, NAPT_PORT_RANGE);

    // Aktifkan forwarding dari SoftAP -> STA
    if (ip_napt_enable_no(SOFTAP_IF, 1) == ERR_OK) {
        _natConfigured = true;
        Serial.printf("[NAT] Layer 3 Forwarding Active. Routing via: %s\n", WiFi.localIP().toString().c_str());
        return true;
    }
    return false;
}

void NetworkManager::loop() {
    // Non-blocking check setiap 3 detik
    if (millis() - _lastCheck > 3000) {
        _lastCheck = millis();
        
        if (WiFi.status() == WL_CONNECTED) {
            if (!_natConfigured) _enableNAT();
        } else {
            _natConfigured = false;
        }
    }
}

// Getters untuk keperluan UI
bool NetworkManager::isNatActive() { return _natConfigured; }
String NetworkManager::getApIP() { return WiFi.softAPIP().toString(); }
int NetworkManager::getClientCount() { return WiFi.softAPgetStationNum(); }
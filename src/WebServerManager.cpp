#include "WebServerManager.h"

WebServerManager::WebServerManager(NetworkManager &netParams, ConfigManager &config)
    : _server(80), _netParams(netParams), _config(config) {}

void WebServerManager::begin()
{
    // Binding method class ke callback server menggunakan lambda
    _server.on("/", HTTP_GET, [this]()
               { _handleRoot(); });
    _server.on("/save", HTTP_POST, [this]()
               { _handleSave(); });
    _server.on("/scan", HTTP_GET, [this]()
               { _handleScan(); });
    _server.on("/restart", HTTP_POST, [this]()
               { _handleRestart(); });

    _server.begin();
    Serial.println("[WEB] HTTP Server Listening on Port 80");
}

void WebServerManager::handleClient()
{
    _server.handleClient();
}

String WebServerManager::_processor(const String &var)
{
    if (var == "STA_SSID")
        return WiFi.status() == WL_CONNECTED ? WiFi.SSID() : "Disconnected";
    if (var == "STA_IP")
        return WiFi.status() == WL_CONNECTED ? WiFi.localIP().toString() : "0.0.0.0";
    if (var == "RSSI")
        return WiFi.status() == WL_CONNECTED ? String(WiFi.RSSI()) : "-";
    if (var == "CLIENTS")
        return String(_netParams.getClientCount());
    if (var == "STATUS_CLASS")
        return WiFi.status() == WL_CONNECTED ? "status-connected" : "status-disconnected";
    if (var == "NAT_STATUS")
        return _netParams.isNatActive() ? "Active" : "Inactive";
    if (var == "AP_IP")
        return _netParams.getApIP();
    if (var == "CURRENT_SSID")
        return _config.data.sta_ssid;
    return String();
}

void WebServerManager::_handleRoot()
{
    String html = FPSTR(INDEX_HTML);
    // Replace placeholders secara manual (lebih efisien memory dibanding regex kompleks)
    html.replace("%STA_SSID%", _processor("STA_SSID"));
    html.replace("%STA_IP%", _processor("STA_IP"));
    html.replace("%RSSI%", _processor("RSSI"));
    html.replace("%CLIENTS%", _processor("CLIENTS"));
    html.replace("%STATUS_CLASS%", _processor("STATUS_CLASS"));
    html.replace("%NAT_STATUS%", _processor("NAT_STATUS"));
    html.replace("%AP_IP%", _processor("AP_IP"));
    html.replace("%CURRENT_SSID%", _processor("CURRENT_SSID"));
    _server.send(200, "text/html", html);
}

void WebServerManager::_handleSave()
{
    if (_server.hasArg("ssid") && _server.hasArg("pass"))
    {
        _config.save(_server.arg("ssid"), _server.arg("pass"));
        _server.send(200, "text/html", "Saved. Rebooting...<script>setTimeout(()=>window.location.href='/', 5000)</script>");
        delay(500);
        ESP.restart();
    }
    else
    {
        _server.send(400, "text/plain", "Bad Request");
    }
}

void WebServerManager::_handleScan()
{
    String html = "<html><body style='background:#1a1a1a;color:#ddd;font-family:monospace;padding:20px;'><h2>Scan Results</h2>";
    int n = WiFi.scanNetworks();
    for (int i = 0; i < n; ++i)
    {
        html += "<div><strong>" + WiFi.SSID(i) + "</strong> (" + String(WiFi.RSSI(i)) + "dBm)</div><hr style='border:1px solid #333'>";
    }
    html += "<br><button onclick=\"location.href='/'\" style='padding:10px;'>Back</button></body></html>";
    _server.send(200, "text/html", html);
}

void WebServerManager::_handleRestart()
{
    _server.send(200, "text/plain", "System Rebooting...");
    delay(100);
    ESP.restart();
}
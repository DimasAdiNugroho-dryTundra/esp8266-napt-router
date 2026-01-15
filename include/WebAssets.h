#ifndef WEB_ASSETS_H
#define WEB_ASSETS_H

#include <Arduino.h>

// Raw Literal string untuk dashboard HTML/CSS
// Menggunakan PROGMEM untuk menghemat RAM
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>ESP NAT Manager</title>
<style>
    :root { --bg:#1a1a1a; --card:#2d2d2d; --text:#e0e0e0; --accent:#00d4ff; --danger:#ff4d4d; }
    body { font-family: 'Segoe UI', monospace; background: var(--bg); color: var(--text); margin: 0; padding: 20px; }
    .container { max-width: 500px; margin: auto; }
    .card { background: var(--card); padding: 20px; border-radius: 8px; box-shadow: 0 4px 6px rgba(0,0,0,0.3); margin-bottom: 20px; }
    h2 { border-bottom: 1px solid #444; padding-bottom: 10px; margin-top: 0; color: var(--accent); }
    .stat-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 10px; }
    .stat-item { background: #333; padding: 10px; border-radius: 4px; font-size: 0.9em; }
    input { width: 100%; padding: 10px; margin: 5px 0 15px; background: #444; border: 1px solid #555; color: white; box-sizing: border-box; }
    button { width: 100%; padding: 12px; border: none; border-radius: 4px; cursor: pointer; font-weight: bold; transition: 0.2s; }
    .btn-save { background: var(--accent); color: #000; }
    .btn-scan { background: #555; color: white; margin-bottom: 15px; }
    .btn-reboot { background: var(--danger); color: white; margin-top: 10px; }
    label { font-size: 0.85em; text-transform: uppercase; letter-spacing: 1px; color: #888; }
    .status-indicator { width: 10px; height: 10px; border-radius: 50%; display: inline-block; margin-right: 5px; }
    .status-connected { background: #00ff00; }
    .status-disconnected { background: #ff4d4d; }
</style>
</head>
<body>
<div class="container">
    <div class="card">
        <h2>Network Status</h2>
        <div class="stat-grid">
            <div class="stat-item">
                <span class="status-indicator %STATUS_CLASS%"></span>
                <strong>Uplink:</strong> <span id="ssid">%STA_SSID%</span>
            </div>
            <div class="stat-item"><strong>IP:</strong> <span id="ip">%STA_IP%</span></div>
            <div class="stat-item"><strong>RSSI:</strong> <span id="rssi">%RSSI%</span> dBm</div>
            <div class="stat-item"><strong>Clients:</strong> <span id="clients">%CLIENTS%</span></div>
        </div>
        <div style="margin-top: 15px; font-size: 0.8em; color: #888;">
            <strong>NAT Status:</strong> %NAT_STATUS% | <strong>AP IP:</strong> %AP_IP%
        </div>
    </div>
    <div class="card">
        <h2>Configuration</h2>
        <form action="/save" method="POST">
            <label>Uplink SSID</label>
            <input type="text" name="ssid" placeholder="Target WiFi SSID" value="%CURRENT_SSID%" required>
            <label>Uplink Password</label>
            <input type="password" name="pass" placeholder="Password">
            <button type="button" class="btn-scan" onclick="location.href='/scan'">Scan Networks</button>
            <button type="submit" class="btn-save">Save & Connect</button>
        </form>
        <form action="/restart" method="POST">
            <button type="submit" class="btn-reboot">Reboot System</button>
        </form>
    </div>
</div>
<script>setTimeout(() => location.reload(), 10000);</script>
</body>
</html>
)rawliteral";

#endif
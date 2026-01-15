# ESP8266 NAPT Router

![PlatformIO](https://img.shields.io/badge/PlatformIO-Core-orange) ![ESP8266](https://img.shields.io/badge/Device-ESP8266-blue) ![License](https://img.shields.io/badge/License-MIT-green) ![Status](https://img.shields.io/badge/Status-Stable-success)

**High-Performance Network Address Translation (NAPT) Implementation for Embedded Systems.**

Proyek ini adalah implementasi *Wi-Fi Range Extender* dengan kemampuan Layer 3 Routing (NAT) pada mikrokontroler ESP8266. Berbeda dengan repeater standar, proyek ini dibangun dengan arsitektur modular (*Separation of Concerns*), manajemen memori yang ketat, dan optimasi *low-level networking stack* (LwIP v2) untuk memaksimalkan *throughput* dan stabilitas koneksi streaming.

---

## 🚀 Key Features

* **Optimized Network Stack:** Menggunakan LwIP v2 High Bandwidth dengan tuning TCP_MSS (1360 bytes) untuk mencegah fragmentasi paket dan *bottleneck* CPU.
* **Overclocked Performance:** Berjalan pada clock speed **160MHz** untuk menangani *packet forwarding* beban tinggi.
* **Modular Architecture:** Kode dipisahkan berdasarkan tanggung jawab (Network, Storage, Web UI) memudahkan maintenance dan skalabilitas.
* **Persistent Configuration:** Penyimpanan kredensial menggunakan **LittleFS** (bukan EEPROM) untuk reliabilitas data jangka panjang.
* **Secure Subnetting:** Menggunakan isolasi subnet Class A (10.10.10.x) untuk menghindari konflik IP dengan router upstream.
* **Responsive Dashboard:** Antarmuka web modern (Dark Mode) tanpa ketergantungan internet eksternal (*embedded CSS/HTML*).

---

## 📂 Project Structure

Struktur direktori dirancang mengikuti standar *Clean Architecture* untuk C++ Embedded:

```
esp8266-napt-router-pro/
├── include/               # Header Files (Interface Definitions)
│   ├── ConfigManager.h    # Abstraksi FileSystem & Config
│   ├── NetworkManager.h   # Core Networking & NAT Logic
│   ├── WebServerManager.h # HTTP Request Handlers
│   └── WebAssets.h        # Static Assets Declaration
├── src/                   # Implementation Files
│   ├── ConfigManager.cpp
│   ├── NetworkManager.cpp
│   ├── WebServerManager.cpp
│   ├── WebAssets.cpp      # Raw Literal HTML/CSS Storage
│   └── main.cpp           # Application Entry Point & Orchestration
├── platformio.ini         # Environment & Build Configuration
└── README.md              # Documentation
```

---

## 🛠️ Technical Specifications

* **Hardware:** ESP8266 (NodeMCU v2 / Wemos D1 Mini)
* **Framework:** Arduino Core for ESP8266
* **Filesystem:** LittleFS
* **Build System:** PlatformIO
* **Network Protocol:** IPv4 NAPT (Network Address Port Translation) with DNS Forwarding.

### Build Flags Optimization

Konfigurasi berikut diterapkan pada platformio.ini untuk performa maksimal:

```ini
-D PIO_FRAMEWORK_ARDUINO_LWIP2_HIGHER_BANDWIDTH  ; Maximize buffer size
-D LWIP_NAPT=1                                   ; Enable NAT feature
-D LWIP_DNS_FORWARD=1                            ; Enable DNS Proxy
-D TCP_MSS=1360                                  ; Optimize packet size
```

---

## 📦 Installation & Setup

### Prerequisites

* VS Code dengan ekstensi **PlatformIO**.
* Board ESP8266 (NodeMCU 1.0 atau sejenisnya).

### Steps

1. **Clone Repository:**
   ```bash
   git clone https://github.com/DimasAdiNugroho-dryTundra/esp8266-napt-router.git
   ```

2. **Open Project:** Buka folder proyek menggunakan VS Code.

3. **Build & Upload:**
   * Sambungkan ESP8266 via USB.
   * Klik tombol **PlatformIO: Upload** (Tanda Panah Kanan) di toolbar bawah.

4. **Monitor:**
   * Buka Serial Monitor (Baudrate: 115200) untuk melihat log inisialisasi.

---

## 🖥️ Usage Guide

1. **Connect:** Cari jaringan Wi-Fi bernama **ESP8266_Repeater** dan sambungkan dengan password **12345678**.

2. **Access Dashboard:** Buka browser dan akses alamat IP Gateway:
   > **http://10.10.10.1**

3. **Configure:**
   * Klik **Scan Networks**.
   * Pilih SSID Wi-Fi sumber (Uplink).
   * Masukkan password dan klik **Save & Connect**.

4. **Status:** Perangkat akan melakukan *reboot*. Setelah menyala kembali, perangkat akan otomatis melakukan *routing* trafik internet dari Uplink ke Client.

---

## ⚠️ Troubleshooting

* **Koneksi Lambat:** Pastikan menggunakan kabel USB berkualitas dan sumber daya minimal **1A**.
* **Gagal Build:** Lakukan *Clean Project* di PlatformIO sebelum build ulang untuk memastikan flag LwIP diterapkan.

---

## 📄 License

Project ini didistribusikan di bawah lisensi **MIT**. Silakan gunakan dan modifikasi untuk keperluan pribadi maupun komersial.
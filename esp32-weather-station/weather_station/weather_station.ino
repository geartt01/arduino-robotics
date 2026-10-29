// ESP32 Weather Station (ACEBOTT QE011 kit)
// Reads temperature, humidity, air pressure, PM2.5, UV, wind, light and rain,
// shows them on the 128x64 OLED and prints them to Serial every 2 seconds.
// Pin numbers and sensor libraries follow the ACEBOTT kit wiring.

#include <Wire.h>
#include <WiFi.h>
#include <U8g2lib.h>
#include <ACB_DHT11.h>
#include <ACB_Atmospheric.h>
#include <ACB_PM25.h>
#include <ACB_Ultraviolet_V2.h>
#include <ACB_WindCup.h>

// --- WiFi (optional): the station works offline if it can't connect ---
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const unsigned long WIFI_TIMEOUT_MS = 10000;

// --- Pins (ACEBOTT QE011 shield) ---
#define DHT_PIN 23
#define UV_PIN 33
#define WIND_PIN 32
#define LIGHT_PIN 36
#define RAIN_PIN 39
#define PM25_RX 17
#define PM25_TX 16

// --- Sensor objects ---
ACB_DHT11 dht(DHT_PIN);
ACB_Atmospheric BMP;
ACB_Ultraviolet uv;
ACB_PM25 PM25;
ACB_WindCup wind;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void connectWifi() {
  WiFi.begin(ssid, password);
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < WIFI_TIMEOUT_MS) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("\nWiFi connected: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi not connected, running offline");
  }
}

void setup() {
  Serial.begin(115200);

  // OLED
  u8g2.setI2CAddress(0x3C * 2);
  u8g2.begin();

  // Sensors
  pinMode(LIGHT_PIN, INPUT);
  pinMode(RAIN_PIN, INPUT);
  pinMode(DHT_PIN, INPUT);
  uv.setpin(UV_PIN);
  BMP.Atmospheric_init();
  PM25.setpin(PM25_RX, PM25_TX);
  wind.setpin(WIND_PIN);

  connectWifi();
}

void loop() {
  // Read sensor data
  int temp = dht.get_Temperature_Data();
  int hum = dht.get_Humidity_Data();
  int pm25 = PM25.read();
  float pressure = BMP.read("Press");
  int uvLevel = uv.read("level");
  float windSpeed = wind.read();
  int light = analogRead(LIGHT_PIN);
  int rain = analogRead(RAIN_PIN);

  // Display on OLED
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.drawStr(0, 10, "Weather Station");

    u8g2.setCursor(0, 25);
    u8g2.print("Temp: "); u8g2.print(temp); u8g2.print("C");

    u8g2.setCursor(0, 40);
    u8g2.print("Hum:  "); u8g2.print(hum); u8g2.print("%");

    u8g2.setCursor(0, 55);
    u8g2.print("PM2.5: "); u8g2.print(pm25);

    u8g2.setCursor(70, 25);
    u8g2.print("Wind: "); u8g2.print(windSpeed, 1);

    u8g2.setCursor(70, 40);
    u8g2.print("UV: "); u8g2.print(uvLevel);

    u8g2.setCursor(70, 55);
    u8g2.print("P: "); u8g2.print((int)pressure);
  } while (u8g2.nextPage());

  // Serial log
  Serial.printf("T=%dC H=%d%% P=%.1f PM2.5=%d UV=%d Wind=%.1f Light=%d Rain=%d\n",
                temp, hum, pressure, pm25, uvLevel, windSpeed, light, rain);

  delay(2000);  // update every 2 seconds
}

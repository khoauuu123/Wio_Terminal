#include "TFT_eSPI.h"
TFT_eSPI tft;

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D1
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("Begin Wio Terminal");

  sensors.begin();
  pinMode(LED_BUILTIN, OUTPUT);

  tft.begin();
  tft.setRotation(3);
  digitalWrite(LCD_BACKLIGHT, HIGH);  // turn on the backlight
  tft.fillScreen(TFT_BLACK);
  tft.drawRoundRect(5, 5, 310, 230, 4, TFT_WHITE);
}

uint32_t TIME_RUN_LED;
uint32_t TINE_RUN_ND = 3000;
int TT_sensors, TT_sensors_ol;
void loop() {
  if (millis() - TIME_RUN_LED > 1000) {
    TIME_RUN_LED = millis();
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  if (millis() - TINE_RUN_ND > 3000) {
    TINE_RUN_ND = millis();

    sensors.requestTemperatures();
    float temperatureC = sensors.getTempCByIndex(0);
    Serial.print(temperatureC);
    Serial.println("ºC");

    int NHIETDO = int(temperatureC);

    // KT sensors
    if (NHIETDO != -127) {
      TT_sensors = 1;
    } else {
      TT_sensors = 0;
    }

    // xóa ô hiên thị
    if (TT_sensors != TT_sensors_ol) {
      TT_sensors_ol = TT_sensors;
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setTextSize(10);
      tft.setCursor(60, 100);
      tft.print("      ");
    }

    // hiên thị sensors
    if (TT_sensors) {
      int x = 90, y = 100;
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setTextSize(10);
      tft.setCursor(x, y);
      tft.print(String(NHIETDO));
      tft.setCursor(x + 85, y - 8);
      tft.setTextSize(4);
      tft.print("o");
      tft.setCursor(x + 113, y);
      tft.setTextSize(10);
      tft.print("C");
    } else {
      int x = 67, y = 100;
      tft.setTextColor(TFT_WHITE, TFT_BLACK);
      tft.setTextSize(3);
      tft.setCursor(x, y);
      tft.print("No Sensors!");
    }
  }
}
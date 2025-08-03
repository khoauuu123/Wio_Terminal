//! xóa thư viện TFT_eSPI trong libraries trong bộ cài Board đã có sảng thư viện "TFT_eSPI.h"
#include "TFT_eSPI.h"
TFT_eSPI tft;

void setup() {
  Serial.begin(115200);
  delay(200);
  pinMode(LED_BUILTIN, OUTPUT);

  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_RED);
  //digitalWrite(LCD_BACKLIGHT, HIGH);  // turn on the backlight

}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
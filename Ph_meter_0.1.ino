#include <LiquidCrystal.h>

// Структура для хранения данных канала pH
struct PHChannel {
  float k;
  float b;
  int analogPin;
};

const int samples = 10; // Число измерений
const float adc_resolution = 1024.0;

PHChannel channels[5] = {
  {-5.7, 23.55, A0},
  {-5.7, 23.55, A1},
  {-5.7, 23.55, A2},
  {-5.7, 23.55, A3},
  {-5.7, 23.55, A4}
};

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
  lcd.begin(8, 1);
  lcd.setCursor(0,0);
  lcd.print(" OFI-pH");
  delay(2000);
  lcd.clear();
  lcd.print("PressBtn");
  Serial.begin(9600);
}

float ph(float voltage, float k, float b) {
    return k * voltage + b;
}

float voltage(int analogPin) {
  int adcPH = 0;
  for (int i = 0; i < samples; i++) {
    adcPH += analogRead(analogPin);
  }
  return (adcPH / (float)samples) * (5.0 / adc_resolution);
}

void loop() {
  int ph_key = analogRead(A7) / 100; 

  if (ph_key >= 1 && ph_key <= 5) {
    int channelIndex = 5 - ph_key;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("pH" + String(ph_key) + "=");
    lcd.setCursor(4,0);
    lcd.print(ph(voltage(channels[channelIndex].analogPin), channels[channelIndex].k, channels[channelIndex].b));
  }
}

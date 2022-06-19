#include <LiquidCrystal.h>

//калибровочные значения датчиков (y = k*x + b)
float k[5] = {-5.7, -5.7, -5.7, -5.7, -5.7};
float b[5] = {23.55, 23.55, 23.55, 23.55, 23.55};

int samples = 10; //число измерений
float adc_resolution = 1024.0;

int ph_key;
//float voltagePH[5] = {}; //массив напряжений аналоговых датчиков
//int pHSense[5] = {}; //массив сырых значений аналоговых входов
byte analogPin[5] = {A0, A1, A2, A3, A4};
//static const uint8_t analogPin[5] = {A0,A1,A2,A3,A4};

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  //пины к которым подключен экран
 
void setup()
{
 lcd.begin(8, 1);  // Инициализируем LCD 8x1
 lcd.setCursor(0,0);
 lcd.print(" OFI-pH");
 delay(2000);
 lcd.clear();
 lcd.print("PressBtn");
 Serial.begin(9600);
}


float ph (float voltage, float k, float b)
{
    return k * voltage + b;
}

float voltage(int analogPin) 
{
   int adcPH=0;
   for (int i = 0; i < samples; i++)
      {
        adcPH += analogRead(analogPin);
        delay(10);
      }
   return (adcPH / samples) * (5.0 / adc_resolution);
}
 
void loop()
{

if (analogRead(A7)<1000) //обработка аналоговых кнопок
   {
      ph_key = (analogRead(A7)+120)/100; 
      lcd.clear();
   }

//Для отладки  
//for (int i = 0; i < 5; i++)
//   {
//       voltagePH[i] = voltage(analogPin[i]);
//   }
//
//for (int i = 0; i < 5; i++)
//   {
//       pHSense[i] = analogRead(analogPin[i]);
//   }
//   


switch (ph_key)
    {
       case 8:
           lcd.setCursor(0,0);
           lcd.print("pH1=");
           lcd.setCursor(4,0);
           lcd.print(ph(voltage(analogPin[0]), k[0], b[0]));
       break;  
       case 7:
           lcd.setCursor(0,0);
           lcd.print("pH2=");
           lcd.setCursor(4,0);
           lcd.print(ph(voltage(analogPin[1]), k[1], b[1]));
       break;
       case 6:
           lcd.setCursor(0,0);
           lcd.print("pH3=");
           lcd.setCursor(4,0);
           lcd.print(ph(voltage(analogPin[2]), k[2], b[2]));
       break;
       case 4:
           lcd.setCursor(0,0);
           lcd.print("pH4=");
           lcd.setCursor(4,0);
           lcd.print(ph(voltage(analogPin[3]), k[3], b[3]));
       break;
       case 1:
           lcd.setCursor(0,0);
           lcd.print("pH5=");
           lcd.setCursor(4,0);
           lcd.print(ph(voltage(analogPin[4]), k[4], b[4]));
       break;
       default:
       break;
  }
  
  
}

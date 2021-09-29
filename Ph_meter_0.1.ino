// E0 = 6.3 буферный раствор в датчике

#include <LiquidCrystal.h>

int ph_key;
float voltagePH5;
float voltagePH1;
int pHSense1 = A0;
int pHSense2 = A1;
int pHSense3 = A2;
int pHSense4 = A3;
int pHSense5 = A4; 

int samples = 10;
float adc_resolution = 1024.0;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);  //пины к которым подключен экран
 
void setup()
{
 lcd.begin(8, 1);  // Инициализирует LCD 8x1
 lcd.setCursor(0,0);
 lcd.print(" OFI-pH");
 delay(2000);
 lcd.clear();
 lcd.print("PressBtn");
 Serial.begin(9600);
}


float ph (float voltage)
{
    //return 7 + ((2.5 - voltage) / 0.18);
    return -5.7 * voltage + 23.55;
}

float voltagePH(int pHSense) 
{
   int adcPH=0;
   for (int i = 0; i < samples; i++)
      {
        adcPH += analogRead(pHSense);
        delay(10);
      }
   return (adcPH / samples) * (5.0 / adc_resolution);
}
 
void loop()
{

if (analogRead(A7)<1000)
   {
      ph_key = (analogRead(A7)+120)/100;
      lcd.clear();
   }
  
    
voltagePH1 = voltagePH(pHSense1);
voltagePH5 = voltagePH(pHSense5);

switch (ph_key)
    {
       case 8:
           lcd.setCursor(0,0);
           lcd.print("pH1=");
           lcd.setCursor(4,0);
           lcd.print(ph(voltagePH(pHSense1)));
       break;  
       case 7:
           lcd.setCursor(0,0);
           lcd.print("pH2=");
           lcd.setCursor(4,0);
           lcd.print(ph(voltagePH(pHSense2)));
       break;
       case 6:
           lcd.setCursor(0,0);
           lcd.print("pH3=");
           lcd.setCursor(4,0);
           lcd.print(ph(voltagePH(pHSense3)));
       break;
       case 4:
           lcd.setCursor(0,0);
           lcd.print("pH4=");
           lcd.setCursor(4,0);
           lcd.print(ph(voltagePH(pHSense4)));
       break;
       case 1:
           lcd.setCursor(0,0);
           lcd.print("pH5=");
           lcd.setCursor(4,0);
           lcd.print(ph(voltagePH(pHSense5)));
       break;
       default:
       break;
  }
  
         
  Serial.println(voltagePH5);
  
}
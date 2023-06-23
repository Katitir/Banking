#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
                                      //
const int pins[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
bool pin1s, pin2s, pin3s, pin4s, pin5s, pin6s, pin7s, pin8s, pin9s, pin10s, pin11s, pin12s, sOn, sOff;
bool systemOn = false;
bool systemOff = false;

void banking();
bool wyePrimary(), deltaPrimary(), wyeSecondary(), deltaSecondary();

void setup() {

    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.setCursor(2, 0);
    lcd.print("Transformer");
    lcd.setCursor(1, 1);
    lcd.print("Bank Simulator");

    for (int i = 0; i < 13; i++)
    {
      pinMode(pins[i], INPUT_PULLUP);
    }

    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);

    delay(1000);
    
}

void loop() {

  // Switch
    sOn = digitalRead(A0);
    sOff = digitalRead(A1);
  // Primary 
    pin1s = digitalRead(pins[0]);
    pin2s = digitalRead(pins[1]);
    pin3s = digitalRead(pins[2]);
    pin4s = digitalRead(pins[3]);
    pin5s = digitalRead(pins[4]);
    pin6s = digitalRead(pins[5]);
  // Secondary
    pin7s = digitalRead(pins[6]);
    pin8s = digitalRead(pins[7]);
    pin9s = digitalRead(pins[8]);
    pin10s = digitalRead(pins[9]);
    pin11s = digitalRead(pins[10]);
    pin12s = digitalRead(pins[11]);
   
   if (sOn == LOW && !systemOn)
    {
      systemOff = false;
      systemOn = true;
    }

    if (sOff == LOW && !systemOff && systemOn)
    {
      systemOff = true;
      systemOn = false;
    }

   if (systemOn)
    {
      banking();
    }
  
   if (systemOff)
   {
    lcd.setCursor(0, 0);
    lcd.print("Rewiring...");
   }

   delay(1000);

   lcd.clear();

}

void banking(){

    if (wyePrimary() && wyeSecondary())
    {
      lcd.setCursor(0, 0);
      lcd.print("Wye - Wye");
      lcd.setCursor(4, 1);
      lcd.print("Connection");
    }
    else if (deltaPrimary() && wyeSecondary())
    {
      lcd.setCursor(0, 0);
      lcd.print("Delta - Wye");
      lcd.setCursor(4, 1);
      lcd.print("Connection");
    }
    else if (wyePrimary() && deltaSecondary ())
    {
      lcd.setCursor(0, 0);
      lcd.print("Wye - Delta");
      lcd.setCursor(4, 1);
      lcd.print("Connection");
    }
    else if (deltaPrimary() && deltaSecondary())
    {
      lcd.setCursor(0, 0);
      lcd.print("Delta - Delta");
      lcd.setCursor(4, 1);
      lcd.print("Connection");
    }
    else {
      lcd.setCursor(0,0);
      lcd.print("Connection Error");
  }

}

bool wyePrimary(){

    if ((pin1s == LOW && pin3s == LOW && pin5s == LOW && pin2s && pin4s && pin6s) || (pin2s == LOW && pin4s == LOW && pin6s == LOW && pin1s && pin3s && pin5s ))
    {
      return true;

    } else { return false; }
}

bool deltaPrimary(){

     if (pin1s == LOW && pin6s == LOW && pin2s == LOW && pin3s == LOW && pin4s == LOW && pin5s == LOW)
    {
      return true;

    } else { return false; }
}

bool wyeSecondary(){
 
    if ((pin7s == LOW && pin9s == LOW && pin11s == LOW && pin8s && pin10s && pin12s) || (pin8s == LOW && pin10s == LOW && pin12s == LOW && pin7s && pin9s && pin11s ))
    {
      return true;

    } else { return false; }
}

bool deltaSecondary(){
  
    if (pin7s == LOW && pin8s == LOW && pin9s == LOW && pin10s == LOW && pin11s == LOW && pin12s == LOW)
    {
      return true;

    } else { return false; }

}






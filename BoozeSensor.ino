/*
  Booze sensor
  using MQ-3 and Sparkfun Breakout PCB
  
  Connections:
   - (GND TO Ground)
   - (A1 TO +5V)
   - (H1 TO +5V)
   - [B1 TO (10kohm to ground) AND TO (Analog pin)].
 
 */
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

int threshold = 500;

int maxValue = 0;

boolean recalibrating = false;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin,INPUT);
  
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue);
  delay(100); //Just here to slow down the output.  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  if (sensorValue < threshold){
    if (sensorValue+20 < threshold){
      recalibrating=false;
    }
    if (!recalibrating){
      lcd.clear();
      lcd.print("standby");
      maxValue = 0;
    }
  }else{
    if (sensorValue > maxValue){
      if (!recalibrating){
        lcd.clear();
        lcd.print("Measuring");
      }
      maxValue = sensorValue;
    }else if (sensorValue + 100 < maxValue){
      if (!recalibrating){
        lcd.clear();
        lcd.print(maxValue);
        delay(3000);
        lcd.clear();
        lcd.print("Recalibrating");
        recalibrating=true;
      }
    }
  }
  
}

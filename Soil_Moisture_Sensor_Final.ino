#define AOUT_PIN A0 // Arduino pin that connects to AOUT pin of moisture sensor
#define THRESHOLD 680 // CHANGE YOUR THRESHOLD HERE
#define wet 876
#define dry 0 // 876
#include <LiquidCrystal.h>
#include <Servo.h> // Tells the arduino to use commands from a pre-made library

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Servo Servo1; // Creates a servo object named "Servo1"

int servoPin = 9; // Connected to pin 9

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  Servo1.attach(9);
}

void loop()
{
  int value = analogRead(AOUT_PIN);
  lcd.setCursor(0,1);
  String text = "";
  Servo1.write(0);
  int pre = map(value, wet, dry, 100, 0);
  lcd.setCursor(0,1);
  lcd.print(pre);
  lcd.print("%");
  lcd.print("--");
  if (value > THRESHOLD && value >= 0) {
    delay(8000); // Wait 8 Seconds for the Robot to turn around
  Servo1.write(90); // Turns servo open for water to come out
    delay(5000); // Waits 5 seconds for the water to water the soil
  Servo1.write(0); // Turns servo close for water to stop 
      text += "DRY: "; // Tells the Dry Value
  } else if (value <= THRESHOLD) {
      text += "WET: "; // Tells the Wet Value
  }
  text += value; 
  lcd.print(text);
  Serial.println(text);
  delay(500);
  lcd.clear();
}

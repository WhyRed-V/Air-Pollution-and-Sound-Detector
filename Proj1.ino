#include <LiquidCrystal_I2C.h>
#include "MQ135.h"

#define ANALOGPIN A2    
#define RZERO 206.85   
#define SensorPin A0

// Setting Up gas sensor
MQ135 gasSensor = MQ135(ANALOGPIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool sensorReady = false;
bool flashDisplay = false;

void setup() {
  lcd.init(); 
  lcd.begin(16, 2);
  lcd.backlight();
  pinMode(SensorPin, INPUT);
  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Pollution");
  lcd.setCursor(0, 1);
  lcd.print("Detection System");
  Serial.println("Heating up gas sensor...");
  delay(10000); // Longer warm-up time (adjust as needed)
  float rzero = gasSensor.getRZero();
  Serial.print("MQ135 RZERO Calibration Value : ");
  Serial.println(rzero);
  sensorReady = true;
}

void loop() {
  if (sensorReady) {
    // Read multiple samples and calculate the average for more accurate results
    const int numSamples = 10;
    float sumPPM = 0.0;
    int sumSoundVal = 0;
    for (int i = 0; i < numSamples; ++i) {
      sumPPM += gasSensor.getPPM();
      sumSoundVal += analogRead(SensorPin);
      delay(10); // Delay between samples
    }
    float avgPPM = sumPPM / numSamples;
    int avgSoundVal = sumSoundVal / numSamples;

    Serial.print("CO2 ppm value : ");
    Serial.println(avgPPM);
    lcd.clear();
    if (!flashDisplay) {
      lcd.setCursor(0, 0);
      lcd.print("CO2 : ");
      lcd.print(avgPPM);
      lcd.print(" PPM");

      lcd.setCursor(0, 1);
      lcd.print("Noise: ");
      lcd.print(avgSoundVal);
      lcd.print(" Db");
    } else {
      if (avgPPM > 1000) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("CO2 Pollution");
        lcd.setCursor(0, 1);
        lcd.print("Detected");
        delay(500); // Display CO2 pollution detected message for 0.5 seconds
      }
      if (avgSoundVal > 200) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Noise Pollution");
        lcd.setCursor(0, 1);
        lcd.print("Detected");
        delay(500); // Display noise pollution detected message for 0.5 seconds
      }
    }

    if (avgPPM > 1000 || avgSoundVal > 200) { // Adjust thresholds as needed
      flashDisplay = !flashDisplay; // Toggle flashDisplay flag
    }
  }

  delay(1000);
}


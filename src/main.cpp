#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <PulseSensorPlayground.h>
#include <Wire.h>


#define I2C_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2


#define REPORTING_PERIOD_MS 1000

const uint8_t &SDA_PIN = D2;
const uint8_t &SCL_PIN = D1;


LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLUMNS, LCD_ROWS);


const int PulseWire = A0;
const int LED = LED_BUILTIN;
int Threshold = 550;

PulseSensorPlayground pulseSensor;


void setup() {
  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.begin(LCD_COLUMNS, LCD_ROWS);
  lcd.backlight();

  pulseSensor.analogInput(PulseWire);
  pulseSensor.blinkOnPulse(LED);
  pulseSensor.setThreshold(Threshold);

  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");
  }
}

void loop() {
  if (pulseSensor.sawStartOfBeat()) {
    int myBPM = pulseSensor.getBeatsPerMinute();
    Serial.println("♥  A HeartBeat Happened ! ");
    Serial.print("BPM: ");
    Serial.println(myBPM);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.printf("BPM: %d", myBPM);
  }

  delay(20);
}

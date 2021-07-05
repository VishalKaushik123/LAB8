/*
 * Project LAB8
 * Description:
 * Author:
 * Date:
 */
#include <Wire.h>
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include "oled-wing-adafruit.h"
SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);
OledWingAdafruit display;
VCNL4040 proximitySensor;
// setup() runs once, when the device is first turned on.
void setup()
{
  // Put initialization like pinMode and begin functions here.
  Serial.begin(9600);
  pinMode(D8, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  Wire.begin();
  display.setup();
  display.clearDisplay();
  display.display();
  proximitySensor.begin();
  proximitySensor.powerOnProximity();
  proximitySensor.powerOnAmbient();

  if (proximitySensor.begin() == false)
  {
    Serial.println("Device not found. Please check wiring.");
    while (1); //Freeze!
  }
}
// loop() runs over and over again, as quickly as it can execute.
void loop()
{
  display.loop();

  // The core of your code will likely live here.

  // variables
  unsigned int proxValue = proximitySensor.getProximity();
  unsigned int ambientValue = proximitySensor.getAmbient();
  unsigned int id = proximitySensor.getID();

  Serial.println(proxValue);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  //blinks blue if far
  if (proxValue < 10)
  {
    digitalWrite(D8, HIGH);
    digitalWrite(D7, LOW);
    digitalWrite(D6, LOW);
  } 

  // blinks green if kind of close
  else if ( proxValue > 10 && proxValue < 1000)
  {
    digitalWrite(D8, LOW);
    digitalWrite(D7, HIGH);
    digitalWrite(D6, LOW);
  }

  // blinks yellow if really close
  else
  {
    digitalWrite(D8, LOW);
    digitalWrite(D7, LOW);
    digitalWrite(D6, HIGH);
  }

  // prox value on oled
  if (display.pressedA())
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(proxValue);
    display.display();
  }

  // light fixture value on oled
  if (display.pressedB())
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(ambientValue);
    display.display();
  }

  // id on oled
  if (display.pressedC())
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.print(id);
    display.display();
  }
}
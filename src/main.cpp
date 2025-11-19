#include <Arduino.h>
#include <helpers.h>

#define PUSH_BUTTON_PIN 4 // GPIO pin for the push button

bool checkHealthBell = false; // Variable to track health status

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PUSH_BUTTON_PIN, INPUT_PULLDOWN); // Use internal pull-up resistor
  connectWifi();
}

void loop()
{
  if (!checkHealthBell && WiFi.status() == WL_CONNECTED)
  {
    
    checkHealthBell = postRequest();
  }

  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(PUSH_BUTTON_PIN);
  if (buttonState == HIGH)
  {
    //  Serial.println("Button Pressed!");
    ringTheBell();
  }
  else
  {
    // Serial.println("Button Released!");
  }
  // delay(3000); // Debounce delay
}
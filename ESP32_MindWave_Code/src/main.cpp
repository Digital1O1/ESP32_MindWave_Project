// https://www.programmingelectronics.com/serial-read/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define LED_PIN 2
#define RC_CAR_PIN 5
//  Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const unsigned int MAX_MESSAGE_LENGTH = 12;
// int LED_PIN = 2;
int incoming_Data;
// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

void setup()
{
  Serial.begin(115200);
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  pinMode(RC_CAR_PIN, OUTPUT);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED_PIN, ledChannel);

  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  OLED.clearDisplay();

  OLED.setTextSize(1);
  OLED.setTextColor(WHITE);
}
void loop()
{
  // Check to see if anything is available in the serial receive buffer
  while (Serial.available() > 0)
  {
    // Create a place to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;

    // Read the next available byte in the serial receive buffer
    char inByte = Serial.read();

    // Message coming in (check not terminating character) and guard for over message size
    if (inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1))
    {
      // Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
    }
    // Full message received...
    else
    {
      OLED.clearDisplay();
      OLED.setCursor(0, 10);
      OLED.print("Attention : ");
      OLED.setCursor(0, 40);
      OLED.print("PWM value : ");
      // OLED.setCursor(80, 10);

      // Add null character to string
      message[message_pos] = '\0';

      // Print the message (or do other things)
      Serial.println(message);
      OLED.setCursor(80, 10);
      OLED.print(message);

      // Convert char to int for PWM signal
      int pwm_value = atoi(message) * 1;
      if (pwm_value > 70)
      {
        digitalWrite(RC_CAR_PIN, HIGH);
        Serial.println("ON");
      }
      else
      {
        digitalWrite(RC_CAR_PIN, LOW);
      }
      OLED.setCursor(80, 40);
      OLED.print(pwm_value);

      ledcWrite(ledChannel, pwm_value);

      OLED.display();
      // Reset for the next message
      message_pos = 0;
    }
  }
}
// https://www.programmingelectronics.com/serial-read/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 5        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define LED_PIN 2
#define RC_CAR_PIN 5
#define PWM_MUTIPLIER 1.5
#define SAMPLE_SIZE 10
#define ARRAY_SIZE 10
const unsigned int MAX_MESSAGE_LENGTH = 12;
int eeg_sample_data_count = 0;
int eeg_array[10];
int count = 0;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

int incoming_value;
int value_array[10];
int old_attention_value = 0;
bool sample_flag = false;
bool set_threshold = false;
bool drive_car = false;
int sample_counter = 0;
int running_sum = 0;
int threshold_average = 0;
int eeg_array_size = sizeof(eeg_array) / sizeof(eeg_array[0]);
// Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  Serial.begin(115200);
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  pinMode(RC_CAR_PIN, OUTPUT);

  // attach the channel to the GPIO to be controlled
  // ledcAttachPin(LED_PIN, ledChannel);
  ledcAttachPin(RC_CAR_PIN, ledChannel);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setTextColor(WHITE);

  oled.setCursor(0, 0);
  oled.print("ESP32");
  oled.setCursor(0, 20);
  oled.print("READY");
  oled.display();
  Serial.println("PROGRAM STARTED");
  ledcWrite(ledChannel, 255);
}
void loop()
{

  // Check to see if anything is available in the serial receive buffer || ONLY THE ATTENTION VALUES ARE BEING SENT
  while (Serial.available() > 0)
  {
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.print("FOCUS!!!");
    // oled.setCursor(0, 40);
    // oled.print("DATA");
    oled.display();

    // Create a place to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;

    // Read the next available byte in the serial receive buffer
    char incoming_byte = Serial.read();

    // Message coming in (check not terminating character) and guard for over message size
    if (incoming_byte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1))
    {
      // Add the incoming byte to our message
      message[message_pos] = incoming_byte;
      message_pos++;

      // oled.clearDisplay();
      // oled.setCursor(0, 0);
      // oled.print("SAMPLING");
      // oled.setCursor(0, 20);
      // oled.print("INCOMING");
      // oled.setCursor(0, 20);
      // oled.print("DATA");
      // oled.display();
    }

    // Full message received DO STUFF HERE
    else
    {
      drive_car = true;
      // Add null character to string
      message[message_pos] = '\0';

      int attention_value = atoi(message);
      int pwm_attention_value = attention_value * PWM_MUTIPLIER;

      // oled.setCursor(0, 0);
      // oled.print("Attention  : ");
      // oled.setCursor(80, 0);
      // // Attention value
      // oled.print(attention_value);

      // oled.setCursor(0, 55);
      // oled.print("PWM value : ");
      // oled.setCursor(80, 55);
      // oled.print(pwm_attention_value);
      // oled.display();

      if (attention_value > 0)
      {
        ledcWrite(ledChannel, 0);
      }
      else
      {
        attention_value = -1;
        ledcWrite(ledChannel, 255);
      }
      message_pos = 0;
    }
    // drive_car = false;
  }
  drive_car = false;
}
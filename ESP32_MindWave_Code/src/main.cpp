// https://www.programmingelectronics.com/serial-read/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // oled display width, in pixels
#define SCREEN_HEIGHT 64 // oled display height, in pixels
#define LED_PIN 2
#define RC_CAR_PIN 5
#define PWM_MUTIPLIER 1.5
#define SAMPLE_SIZE 10
#define ARRAY_SIZE 10
const unsigned int MAX_MESSAGE_LENGTH = 12;
int eeg_sample_data_count = 0;
int eeg_array[ARRAY_SIZE];
int count = 0;

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;

bool sampling_flag = false;

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
  Serial.begin(115200);
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  pinMode(RC_CAR_PIN, OUTPUT);
  // pinMode(LED_PIN,OUTPUT);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED_PIN, ledChannel);

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
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
    char incoming_byte = Serial.read();

    // Message coming in (check not terminating character) and guard for over message size
    if (incoming_byte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1))
    {
      // Add the incoming byte to our message
      message[message_pos] = incoming_byte;
      message_pos++;
    }

    // Full message received DO STUFF HERE
    else
    {
      // Display values on oled
      // oled.clearDisplay();
      // oled.setCursor(0, 0);
      // oled.print("Attention : ");
      // oled.setCursor(0, 20);
      // oled.print("Sample Counter : ");
      // oled.setCursor(0, 40);
      // oled.print("PWM value : ");
      // oled.setCursor(80, 10);

      oled.clearDisplay();
      oled.setCursor(0, 0);
      oled.print("Attention : ");

      oled.setCursor(0, 20);
      oled.print("Sample Counter : ");

      oled.setCursor(0, 50);
      oled.print("PWM value : ");

      oled.setCursor(0, 30);
      oled.print("Sample Average : ");

      // Add null character to string
      message[message_pos] = '\0';

      // Print the message/attention value (or do other things)
      Serial.println(message);
      oled.setCursor(80, 0);
      oled.print(message); // Attention value
      int old_message = atoi(message);

      // Convert char to int for PWM signal
      int pwm_attention_value = atoi(message) * PWM_MUTIPLIER;
      oled.setCursor(80, 50);
      oled.print(pwm_attention_value);

      /*
        Count 10 attention values that are above 0

        Store 10 attention values in an array

        Take the average of that array

        Use the mentioned average as the 'threshold'

        Control whatever peripheral once that threshold is reached
      */
      while (sampling_flag == false)
      {
        ledcWrite(ledChannel, 0);

        // digitalWrite(LED_PIN,LOW);
        if (atoi(message) > 0 && old_message != atoi(message))
        {
          eeg_array[count] = pwm_attention_value;
          // printf("EEG Attention Value : %d \r\n", eeg_array[count]);
          oled.setCursor(0, 40);
          oled.print("Sampled value : ");
          oled.setCursor(100, 40);
          oled.print(eeg_array[count]);
          count++;

          oled.setCursor(100, 20);
          oled.print(count);
          oled.display();
        }
        if (count == 10)
        {
          ledcWrite(ledChannel, 255);

          while (true)
            ;
        }
      }

      // Sample average
      oled.setCursor(100, 30);
      oled.print("555");

      ledcWrite(ledChannel, pwm_attention_value);

      oled.display();
      // Reset for the next message
      message_pos = 0;
    }
  }
}

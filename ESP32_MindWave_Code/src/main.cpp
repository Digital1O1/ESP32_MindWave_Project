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
int sample_counter = 0;
int running_sum = 0;
int threshold_average = 0;
int eeg_array_size = sizeof(eeg_array) / sizeof(eeg_array[0]);
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup()
{
  Serial.begin(115200);
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  pinMode(RC_CAR_PIN, OUTPUT);

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
  // Check to see if anything is available in the serial receive buffer || ONLY THE ATTENTION VALUES ARE BEING SENT
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
      // Add null character to string
      message[message_pos] = '\0';
      oled.clearDisplay();

      int attention_value = atoi(message);
      int pwm_attention_value = attention_value * PWM_MUTIPLIER;

      oled.setCursor(0, 0);
      oled.print("Attention  : ");
      oled.setCursor(80, 0);
      // Attention value
      oled.print(attention_value);

      oled.setCursor(0, 55);
      oled.print("PWM value : ");
      oled.setCursor(80, 55);
      oled.print(pwm_attention_value);
      oled.display();

      // Store previous value here
      // old_attention_value = attention_value;
      // Reset for the next message
      ledcWrite(ledChannel, pwm_attention_value);

      message_pos = 0;
    }
  }
}
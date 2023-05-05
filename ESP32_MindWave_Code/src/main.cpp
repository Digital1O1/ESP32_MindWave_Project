// https://www.programmingelectronics.com/serial-read/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
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

Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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
      // Display values on OLED
      OLED.clearDisplay();
      OLED.setCursor(0, 0);
      OLED.print("Attention : ");

      OLED.setCursor(0, 20);
      OLED.print("Sample Counter : ");

      OLED.setCursor(0, 40);
      OLED.print("PWM value : ");
      // OLED.setCursor(80, 10);

      // Add null character to string
      message[message_pos] = '\0';

      // Print the message (or do other things)
      Serial.println(message);
      OLED.setCursor(80, 0);
      OLED.print(message); // Attention value

      // Convert char to int for PWM signal
      int incoming_attention_value = atoi(message) * PWM_MUTIPLIER;
      OLED.setCursor(80, 40);
      OLED.print(incoming_attention_value);

      /*
        Count 10 attention values that are above 0

        Store 10 attention values in an array

        Take the average of that array

        Use the mentioned average as the 'threshold' 

        Control whatever peripheral once that threshold is reached 
      */

      if(incoming_attention_value > 0)
      {
        eeg_array[count] = incoming_attention_value;
        printf("EEG Attention Value : %d \r\n",eeg_array[count]);

        count++;
        
        OLED.setCursor(100, 20);
        OLED.print(count);

        // if(count == 10)
        // {
        //   while(true)
        //   {
        //     printf("FLAG\r\n");
        //   }
        // }
      }



      // if (incoming_attention_value > 70)
      // {
      //   digitalWrite(RC_CAR_PIN, HIGH);
      //   Serial.println("ON");
      // }
      // else
      // {
      //   digitalWrite(RC_CAR_PIN, LOW);
      // }

      // OLED.setCursor(80, 40);
      // OLED.print(incoming_attention_value);

      ledcWrite(ledChannel, incoming_attention_value);

      OLED.display();
      // Reset for the next message
      message_pos = 0;
    }
  }
}
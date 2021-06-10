#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

#define DHTPIN 33
#define DHTTYPE DHT22
#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14
#define VOLTPIN A13

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
float sensorValue = 0;

void setup() {
  //while (!Serial) {delay(10);}
  //Serial.begin(115200);

  //Serial.println("OLED FeatherWing test");
  // delay 1s for led won's start immediately after powered up
  delay(1000);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32
  //Serial.println("OLED begun");

  // Initialize dht device.
  dht.begin();

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(1000);

  // Clear the buffer.
  display.clearDisplay();
  display.display();

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);

  // text display tests
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  // Delay between measurements.
  delay(delayMS);
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    //Serial.println(F("Error reading temperature!"));
  }
  else {
    float temp = event.temperature;
    display.print(F("Celsius: "));
    display.print(temp);
    display.println(F(" C"));
    display.print(F("Fahrenheit: "));
    display.print(temp * 1.8 + 32);
    display.println(F(" F"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    //Serial.println(F("Error reading humidity!"));
  }
  else {
    display.print(F("Humidity: "));
    display.print(event.relative_humidity);
    display.println(F("%"));
  }
  
  if(!digitalRead(BUTTON_A)) display.print("A");
  if(!digitalRead(BUTTON_B)) display.print("B");
  if(!digitalRead(BUTTON_C)) display.print("C");

  sensorValue = analogRead(VOLTPIN)*2/1000.0;
  display.print(F("Power Supply: "));
  display.print(sensorValue);
  display.print(F("V"));
  display.setCursor(0,0);
  display.display();
}

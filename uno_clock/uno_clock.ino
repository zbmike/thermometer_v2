#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 15
#define DHTTYPE DHT11
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
int lcd_key     = 0;
int adc_key_in  = 0;
int runloop = 20;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
byte degree[8] = {
  0b00110,
  0b01001,
  0b01001,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1500) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 500)  return btnLEFT; 
 if (adc_key_in < 700)  return btnSELECT;   
 return btnNONE;  // when all others fail, return this...
}

DHT_Unified dht(DHTPIN, DHTTYPE);
int h=0,m=0,s=0, ms=0;
// For accurate Time reading, use Arduino Real Time Clock and not just delay()
static uint32_t now = 0, next = 0; // RTC

void setup() {
  //if (!Serial) {delay(10);}
  //Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  dht.begin();
  lcd.begin(16, 2);
  lcd.createChar(0, degree);
  // pin 10 is backlight control, levels are 0 to 255 where 0 is off
  analogWrite(10,40);
  now=millis();
}

void loop() {
  if (runloop == 20) {
    runloop = 0;
    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    float fahrenheit = event.temperature * 9 / 5 + 32;
    
    if (isnan(event.temperature)) {
      //Serial.println(F("Error reading temperature!"));
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print(round(event.temperature));
      lcd.write((byte)0);
      lcd.print(F("C/"));
      lcd.print(round(fahrenheit));
      lcd.write((byte)0);
      lcd.print(F("F"));
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      //Serial.println(F("Error reading humidity!"));
    }
    else {
  //    lcd.setCursor(0, 1);
      lcd.print(F(" H:"));
      lcd.print(round(event.relative_humidity));
      lcd.print(F("%"));
    }
  }
  runloop = runloop + 1;
  
  lcd_key = read_LCD_buttons();
  switch (lcd_key)               // depending on which button was pushed, we perform an action
  {
   case btnRIGHT:
   {
     if (runloop % 2 == 0) {h = h - 1;}
     if (h < 0) { h = h +24;}
     break;
   }
   case btnLEFT:
   {
     if (runloop % 2 == 0) {h = h + 1;}
     break;
   }
   case btnUP:
   {
     if (runloop % 2 == 0) {m = m + 1;
     s = 0;}
     break;
   }
   case btnDOWN:
   {
     if (runloop % 2 == 0) {m = m - 1;
     if (m < 0) { m = m + 60;}
     s = 0;}
     ms = 0;
     break;
   }
   case btnSELECT:
   {
     if (runloop % 2 == 0) {h = h + 12;}
     break;
   }
   case btnNONE:
   {
     break;
   }
 }
  
  next = millis();
  ms = next - now + ms;
  now = next;

  s = s + ms / 1000;
  ms = ms % 1000;
  if (s > 59) {
    s = s - 60;
    m = m + 1;
  }
  if (m > 59) {
    m = m - 60;
    h = h + 1;
  }
  if (h > 23) {
    h = h - 24;    
  }
  bool pm = false;
  lcd.setCursor(3, 1);
  if (h == 0) {
    lcd.print(12);
  } else if (h < 12) {
    if (h < 10) {lcd.print(0);}
    lcd.print(h); 
  } else if ( h > 12) {
    if (h < 22) {lcd.print(0);}
    lcd.print(h-12);
    pm = true;
  } else if ( h == 12) {
    lcd.print(h);
    pm = true;
  }
  lcd.print(F(":"));
  if (m < 10) {lcd.print(0);}
  lcd.print(m);
  lcd.print(F(":"));
  if (s < 10) {lcd.print(0);}
  lcd.print(s);
  if (pm == true) { lcd.print(F("PM")); }
  else { lcd.print(F("AM")); }
//  lcd.print(F("."));
//  lcd.print(ms);
  // Delay between measurements.
  delay(100);
}

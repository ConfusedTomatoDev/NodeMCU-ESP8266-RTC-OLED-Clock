//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

RTC_DS3231 rtc;

int tempC;
int tempF;

char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tues", "Wed", "Thurs", "Fri", "Sat"};
 
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET    -1  // Reset pin # (or -1 if sharing reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
void setup() 
{
 
Serial.begin(115200);
 
if (! rtc.begin()) {
Serial.println("Couldn't find RTC");
while (1);
}
 
if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
{ 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
}
    // Remove or comment out below lines once you set the date & time on the RTC.
    // Following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // Uncomment below to see all full digits for date and time.
    // rtc.adjust(DateTime(2020, 12, 12, 12, 12, 12));
    
// display.setRotation(3); // Rotate display 90  
 display.display();
 delay(2);
 display.clearDisplay();
//

display.clearDisplay();
display.setTextColor(BLACK,WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print("Booting...");
display.setTextColor(WHITE);
display.display();
delay(3000);

}
 
void loop()
{

DateTime now = rtc.now();

display.clearDisplay();

//
// Show Time //
//

// Show the hours
display.setTextSize(2);
display.setCursor(0,16);
display.println(now.hour(), DEC);

// Split hours and minutes 
display.setTextSize(2);
display.setCursor(0,32);
display.println("--");

// Show the minutes
display.setTextSize(2);
display.setCursor(0,48);
display.println(now.minute(), DEC);

// Show the seconds
display.setTextSize(1);
display.setCursor(32,36);
display.println(now.second(), DEC);

//
// Show Date //
//

// Show the Month
display.setTextSize(2);
display.setCursor(74,16);
display.println(now.month(), DEC);

// Show a split
display.setTextSize(2);
display.setCursor(94,16);
display.println("-");

// Show the day
display.setTextSize(2);
display.setCursor(104,16);
display.println(now.day(), DEC);

// Show a split
display.setTextSize(2);
display.setCursor(80,32);
display.println("----");

// Show the year
display.setTextSize(2);
display.setCursor(80,48);
display.println(now.year(), DEC);

//
// Show Title, Weekday, and Temp
//

// Show the weekday 
display.setTextSize(2);
display.setCursor(34,16);
display.print(daysOfTheWeek[now.dayOfTheWeek()]);

// Show tempurature
display.setTextSize(2);
display.setCursor(34,48);
//display.print("Temp:");
tempC = rtc.getTemperature();
tempF = (tempC * 1.8) + 32.0;
display.print(tempF);    // Comment this line out and uncomment next line for Celsius
//display.print(tempC); 
display.setTextSize(1);
display.print("F");

// Show the Title
display.setTextColor(BLACK,WHITE);
display.setTextSize(2);
display.setCursor(0,0);
display.print("   Time   ");
display.setTextColor(WHITE);

display.display(); 
}

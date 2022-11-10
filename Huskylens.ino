/*
This Project use NodeMCU v.3 as a microcontroller but any esp32 would work for the project. I use 1 UART for LCD and 1 I2C for Huskylens. Huskylens is AI module that can easily be configured.
*/

#include "HUSKYLENS.h"
#include "Wire.h"
#include <TridentTD_LineNotify.h>
#include <SoftwareSerial.h>
#include <TimeLib.h> 

#define SSID        "--------------------"  // generate via line
#define PASSWORD    "--------------------"
#define LINE_TOKEN  "--------------------"


#define txPin 2
SoftwareSerial LCD = SoftwareSerial(0, txPin);

const int voice 4;
const int LCDdelay=10;
const int mag 3;
HUSKYLENS huskylens;

void setname(String newname,uint8_t ID)
{
  while (!huskylens.setCustomName(newname, ID))
   {
     Serial.println(F("Set customname failed!")); 
     delay(100);  
   }

void lcdPosition(int row, int col) 
{
LCD.write(0xFE); //command flag
LCD.write((col + row*64 + 128));
}  
    
void clearLCD()
{
LCD.write(0xFE); //command flag
LCD.write(0x01); //clear command.
delay(LCDdelay);
}
                      
void backlightOn()
{
//turns on the backlight
LCD.write(0x7C); //command flag for backlight stuff
LCD.write(157); //light level.
delay(LCDdelay);
}
            
void backlightOff() {
//turns off the backlight
LCD.write(0x7C); //command flag for backlight stuff
LCD.write(128); //light level for off.
delay(LCDdelay);
}

                            
        
void setup()
{
   Serial.begin(115200);
    Wire.begin();
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
    }
   setname ("Jatupone",1);
   setname ("Kriengsak",2);
   setname ("Ratchanon",3);
   //.... Insert name in the "" and you can extend the list.

  Serial.println(LINE.getVersion());
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
  LINE.setToken(LINE_TOKEN);

  pinMode(sound,OUTPUT);
  
pinmode(mag,OUTPUT);
pinMode(txPin, OUTPUT);
LCD.begin(9600);
backlightOn() ;
clearLCD();
lcdPosition(0,0);
digitalWrite(mag,HIGH);
        
}

void loop
{
  String Face = result.ID;
  println(F("ID = ")+result.ID);
  
  if(result.ID != 0)
  {
    LINE.notify(Face + "attend work at"+ hour()+","+minute());
    digitalWrite(mag,LOW);
    digitalWrite(voice,HIGH);
    clearLCD();
    LCD.print(Face + "attend work at"+ hour()+","+minute());
    for (int i = 0; i <= 1000; i++) 
      {
    delay(1);
    if (Face != Face)
        {
          break;
        }
      }
    digitalWrite(voice,LOW);
    digitalWrite(mag,HIGH);        
  }
  else 
  {
    LCD.print("face recognition work attend check list");
    clearLCD();
  }
  
}

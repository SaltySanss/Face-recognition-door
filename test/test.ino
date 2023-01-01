#include "HUSKYLENS.h"
#include "Wire.h"
#include <SoftwareSerial.h>

#define Relay 7

String Name;
SoftwareSerial Ard(2,3); //Rx,Tx
HUSKYLENS huskylens;

void printResult(HUSKYLENSResult result);

void setname(String newname,uint8_t ID)
{
  while (!huskylens.setCustomName(newname, ID))
   {
     Serial.println(F("Set customname failed!")); 
     delay(100);  
   }
}

void setup()
{
   Serial.begin(115200);
    Wire.begin();
    huskylens.writeAlgorithm(ALGORITHM_FACE_RECOGNITION);
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        delay(100);
    }
   delay(100);
   setname ("Jatupone",1);
   setname ("Ratchanon",2);
   setname ("Kriengsak",3);
   Ard.begin(9600);
  pinMode(Relay,OUTPUT);
}



void loop()
{
  if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    else if(!huskylens.available()) Serial.println(F("No block or arrow appears on the screen!"));
    else
    {
        while (huskylens.available())
        {
            HUSKYLENSResult result = huskylens.read();
            printResult(result);
            Serial.println(Name);
            Ard.println(Name);
            digitalWrite(Relay,HIGH);//..............................................................แก้
            delay(500);
        }    
    }
    digitalWrite(Relay,LOW);
}

void printResult(HUSKYLENSResult result)
{    
   if (result.command == COMMAND_RETURN_BLOCK){
        switch (result.ID)
        {
          case 1:
          Name = "Jatupone";
          break;
          case 2:
          Name = "Ratchanon";
          break;
          case 3:
          Name = "Kriengsak";
          break;
          default:
          break;
          /*case n:
          Name = "";
          break;
         Insert name in the "" , number in n and you can extend the list.*/
        }
        //Serial.println(String()+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    } 
}

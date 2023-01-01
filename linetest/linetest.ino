/* 
 * ไลบรารี่ TridentTD_LineNotify version 2.1
 * ใช้สำหรับ ส่ง แจ้งเตือนไปยัง LINE สำหรับ ESP8266 และ ESP32
 * สามารถส่งได้ทั้ง ข้อความ , สติกเกอร์ และรูปภาพ(ด้วย url)
 * -----------------------------------------------------
 * ให้ save เป็น file ต่างหากก่อนถึงจะส่ง Line Notify ภาษาไทยได้
 */

#include <TridentTD_LineNotify.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial MCU(D3,D4); //RX,TX

#define SSID        "Pongsak30_2.4G"  // name of the WiFi
#define PASSWORD    "0860127060" // WiFi password
#define LINE_TOKEN  "qJUyOK0YohGyFp78GpRj8rWsDXUgswRonDQ07EdYtwv" // generate via line

String prevName;

void setup() {
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  
  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
  
  MCU.begin(9600);
  pinMode(D3,INPUT);
  pinMode(D4,OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Face recognition");
  lcd.setCursor(4, 1);
  lcd.print("doorlock");
}

void loop() {
  String nowName = MCU.readStringUntil('\n');
  
  if (nowName != prevName)
  {
    Serial.println(nowName);
    LINE.notify(nowName);
    int pos = ((16 - nowName.length())/2) ;
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("Welcome");
    lcd.setCursor(pos, 1);
    lcd.print(nowName);
    delay(2000); //..............................................................แก้
    prevName = nowName;
    nowName = MCU.readStringUntil('\n');
  }
  else
  {
    nowName = MCU.readStringUntil('\n');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Face recognition");
    lcd.setCursor(4, 1);
    lcd.print("doorlock");
  }
}

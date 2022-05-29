#include <SPI.h>
#include "RF24.h"


#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

RF24 myRadio (10, 9);
byte addresses[][6] = {"0"};
char buff[33]; unsigned char menu_choose;
struct package {
  int id = 1;
  float kelembaban = 0;
  int buttonRead = 0;
  float PPM1_High = 0;
  float PIR = 0;
  float Suhu = 0;
  //  int high_CEL = 0;
  //  int low_CEL = 0;
  int Hum = 0;
  char  text[300] = "Bismillah TA ne lancar";

};

typedef struct package Package;
Package data;

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  delay(1000);
  pinMode(2, OUTPUT);

  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_HIGH);
  myRadio.setDataRate( RF24_250KBPS );

  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop()  {
  myRadio.read( &data, sizeof(data) );
  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.PPM1_High);
  Serial.println(data.buttonRead);
  Serial.println(data.kelembaban);
  Serial.println(data.Suhu);
  Serial.println(data.PIR);
  Serial.println(data.Hum);
  Serial.println(data.text);
  //  if ( myRadio.available()) {
  //    while (myRadio.available()) {
  //      myRadio.read( &data, sizeof(data) );
  //
  //    }
  //    Serial.print("\nPackage:");
  //    Serial.print(data.id);
  //    Serial.print("\n");
  //    Serial.println(data.PPM1_High);
  //    Serial.println(data.buttonRead);
  //    Serial.println(data.kelembaban);
  //    Serial.println(data.Suhu);
  //    Serial.println(data.PIR);
  //    Serial.println(data.Hum);
  //    Serial.println(data.text);
  //  }
}

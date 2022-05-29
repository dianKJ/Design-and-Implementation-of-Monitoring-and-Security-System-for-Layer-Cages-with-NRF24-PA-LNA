#include <SPI.h>
#include "RF24.h"
#include "DHT.h"

// Define untuk sensor Mq-135 //
#define RL 10 //nilai RL =10 pada sensor
#define m -0.417 //hasil perhitungan gradien
#define b 0.425 //hasil perhitungan perpotongan
//#define Ro 7.19 //hasil pengukuran RO
#define Ro 2.78 //hasil pengukuran RO udara bersih
#define MQ1_sensor A6 //definisi variabel

const int numReadings = 5;//nilai penambilan sample pembacaan sebesar 5 kali
float readings[numReadings];
int readIndex = 0;
float total = 0;
float average = 0;

// Parameter kelembaban tanah //
int sensorPin = A3;  // pin sensor
int powerPin = 7;    // untuk pengganti VCC
//float ppm;


// Parameter kelembaban udara //
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


RF24 myRadio (10, 9);
byte addresses[][6] = {"0"};

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
  delay(1000);
  pinMode(A7, INPUT);
  pinMode(7, INPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  digitalWrite(powerPin, LOW);
  dht.begin();
  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_HIGH);
  myRadio.setDataRate( RF24_250KBPS );
  myRadio.openWritingPipe(addresses[0]);
}

void loop() {
  MQ_1();
  int readButton = analogRead(A7);
  //  float Amonia = MQ_1();
  //Parsing nilai float dari pembacaan senor MQ1
  //  average = average * 10;
  //  int high = (ppm1 & 0b11111111);8
  //  int low = (ppm1 >> 8);
  //Parsing nilai float dari pembacaan senor DHT11
  float Celcius = DHT11_Cel();
  //  uint16_t Suhu_Kirim = Suhu * 1000;
  //  int high_Cel = (Suhu_Kirim & 0b11111111);
  //  int low_Cel = (Suhu_Kirim >> 8);

  int humidity = DHT11_Hum();


  uint8_t byte = 9;

  data.id = data.id + 1;
  data.PPM1_High = average;
  data.buttonRead = readButton;
  data.kelembaban =  bacaKelembaban();
  data.Suhu = Celcius;
  data.Hum = humidity;
  data.PIR = digitalRead(A0);
  delay(5);
  myRadio.write(&data, sizeof(data));

  Serial.print("\nPackage:");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.PPM1_High);
  Serial.println(data.buttonRead);
  Serial.println(data.kelembaban);
  Serial.println(data.Suhu);
  Serial.println(data.PIR);
  Serial.println(humidity);
  Serial.println(data.text);
  delay(1000);
}


int bacaKelembaban() {
  //  digitalWrite(powerPin, LOW);
  //  delay(100);
  //  digitalWrite(powerPin, HIGH);
  int nilaiSensor = analogRead(sensorPin);
  delay(10);
  //  digitalWrite(powerPin, LOW);
  return nilaiSensor;
}

void MQ_1() {

  float VRL; //Voltage drop across the MQ sensor
  float Rs; //Sensor resistance at gas concentration
  float ratio; //Define variable for ratio


  VRL = analogRead(MQ1_sensor) * (5 / 1023.0); //konversi analog ke tegangan
  Rs = (5.0 / VRL - 1) * 10 ; //rumus untuk RS
  ratio = Rs / Ro; // rumus mencari ratio
  float ppm = pow(10, ((log10(ratio) - b) / m)); //rumus mencari ppm

  //  total = total - readings[readIndex];
  //
  //  readings[readIndex] = ppm;
  //
  //  total = total + readings[readIndex];
  //
  //  readIndex = readIndex + 1;
  //
  //
  //  if (readIndex >= numReadings) {
  //
  //    readIndex = 0;
  //  }
  //
  //  average = (total / numReadings);
  average = ppm;
  //    Serial.println(average);
  //  Serial.println(average);
  //  Serial.print("NH3 (ppm) = "); //Display a ammonia in ppm
  //  Serial.print(ppm);
  //  Serial.print("Voltage = "); //Display a intro message
  //  Serial.println(VRL);

  delay(100);
}


float DHT11_Cel() {
  delay(20);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  //  Serial.print(F("%  Temperature: "));
  //  Serial.print(t);
  //  Serial.println(F("°C "));
  return t;
}


int DHT11_Hum() {
  delay(20);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)


  // Check if any reads failed and exit early (to try again).
  if (isnan(h)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  //  Serial.print(F("Humidity: "));
  //  Serial.println(h);
  return h;

}

#include <Arduino.h>
#include "HX711.h"
#include "DHT.h"
#include <SPI.h>
#include <SD.h>

File myFile;

#define DHTPIN 6    
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);
float reference_temperature;
const float compensation_factor =4.64;  
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;


HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  dht.begin();
  reference_temperature = dht.readTemperature();
  Serial.println(reference_temperature);
  //scale.set_gain(64);
  
  while (!Serial) {
  }
  
  while(scale.is_ready()==0){ 
    }
if(scale.is_ready()==1) {
    //scale.set_gain(32);
    scale.set_scale();
    long reading1 = scale.get_units(15);
    Serial.print("Result: ");
    Serial.println(reading1);
    //scale.set_gain(32);    
    Serial.println("Tare... remove any weights from the scale.");
    delay(5000);    
    scale.tare();
    Serial.println("Tare done...");
    Serial.print("Place a known weight on the scale...;");
    delay(8000);   
    long reading = scale.get_units(10);   
    Serial.print("Result: ");
    Serial.println(reading);
    scale.set_scale(reading/131); 
    //scale.tare();                        
    //Serial.println("WEIGHING MACHINE");    
  }
}
void loop() {
  //scale.set_scale();
  long rawValue = scale.get_units();
  float current_temperature = dht.readTemperature(); 

 // Apply temperature compensation
  int compensated_value = compensateValue(rawValue, current_temperature);
  Serial.print("Raw Value: ");
  Serial.println(rawValue);
  Serial.print("Temperature: ");
  Serial.print(current_temperature);
  Serial.println(" °C");
  Serial.print("Compensated Value: ");
  Serial.println(compensated_value);
  long reading1 = scale.get_units(15);
  Serial.print("Result: ");
  Serial.println(reading1);
  float t = dht.readTemperature();
  //Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(',');
  long readd=scale.read();
  Serial.print(readd);
  Serial.print(',');
  long adc=scale.get_value(5);
  Serial.print(adc);
  Serial.print(',');
  long value=scale.get_units(15);
  //Serial.print(" Weight: ");
  Serial.print(value);
  Serial.print(',');
  Serial.println(compensated_value);

    if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }

  myFile = SD.open("AT64GAIN.csv", FILE_WRITE);

  if (myFile) {
    myFile.print(t);
    myFile.print(',');
    myFile.print(readd);
    myFile.print(',');
    myFile.print(adc);
    myFile.print(',');
    myFile.print(value);
    myFile.print(',');
    myFile.println(compensated_value);
    myFile.close();
  } else {
    Serial.println("error opening test.txt");
  }
  //delay(1000);
  
}
float compensateValue(int raw_value, float temperature) {
  float compensation = compensation_factor * (temperature - reference_temperature);
  float compensated_value = raw_value-compensation;
  return compensated_value;
}

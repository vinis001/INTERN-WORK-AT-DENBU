// Written by John Boxall from http://tronixstuff.com

#include "Wire.h"
#define RTC_ADDRESS 0x68
// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val){
  return( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val){
  return( (val/16*10) + (val%16) );
}
void setup(){
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);

  Serial.println("Enter the time in the format: ss mm hh d dd mm yy");

  while (!Serial.available()); // Wait for user input
  delay(100); // Delay for stable input

  // Read the time input from the user
  String timeInput = Serial.readString();
  int values[7]; // Array to store the time components

  // Split the input into individual time components
  int count = 0;
  String value = "";
  for (int i = 0; i < timeInput.length(); i++) {
    if (timeInput[i] == ' ') {
      values[count] = value.toInt();
      Serial.println(values[count]);
      value = "";
      count++;
    } else {
      value += timeInput[i];
    }
  }
  values[count] = value.toInt();
  setDS3231time(values[0], values[1], values[2], values[3], values[4], values[5], values[6]);
  //setDS3231time(30,42,16,5,13,10,16);
}
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte
dayOfMonth, byte month, byte year){
  // sets time and date data to DS3231
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0x00); // select register
  Wire.write(decToBcd(second)& 0x7F); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte& second,
byte& minute,
byte& hour,
byte& dayOfWeek,
byte& dayOfMonth,
byte& month,
byte& year){
  Wire.beginTransmission(RTC_ADDRESS);
  Wire.write(0x00); // set DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(RTC_ADDRESS, 7);
  // request seven bytes of data from DS3231 starting from register 00h
  second = bcdToDec(Wire.read() & 0x7f);
  minute = bcdToDec(Wire.read());
  hour = bcdToDec(Wire.read());
  dayOfWeek = bcdToDec(Wire.read());
  dayOfMonth = bcdToDec(Wire.read());
  month = bcdToDec(Wire.read());
  year = bcdToDec(Wire.read());
}
void displayTime(){
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(second, minute, hour, dayOfWeek, dayOfMonth, month,year);
  // send it to the serial monitor
  Serial.print(hour, DEC);
  // convert the byte variable to a decimal number when displayed
  Serial.print(":");
  if (minute<10){
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second<10){
    Serial.print("0");
  }
  Serial.print(second, DEC);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/");
  Serial.print(year, DEC);
  Serial.print(" Day of week: ");
  switch(dayOfWeek){
  case 1:
    Serial.println("Sunday");
    break;
  case 2:
    Serial.println("Monday");
    break;
  case 3:
    Serial.println("Tuesday");
    break;
  case 4:
    Serial.println("Wednesday");
    break;
  case 5:
    Serial.println("Thursday");
    break;
  case 6:
    Serial.println("Friday");
    break;
  case 7:
    Serial.println("Saturday");
    break;
  }
}
void loop(){
  displayTime(); // display the real-time clock data on the Serial Monitor,
  delay(10000); // every second
}

//unsigned int bcdToDec(unsigned int bcdValue){
//  unsigned int result = 0;
//  unsigned int multiplier = 1;
//
//  while (bcdValue > 0) {
//    result += (bcdValue % 16) * multiplier;
//    bcdValue /= 16;
//    multiplier *= 10;
//  }
//
//  return result;
//}
//
//
//unsigned int decToBcd(unsigned int decimalValue){
//  unsigned int result = 0;
//  unsigned int multiplier = 1;
//
//  while (decimalValue > 0) {
//    result += (decimalValue % 10) * multiplier;
//    decimalValue /= 10;
//    multiplier *= 16;
//  }
//
//  return result;
//}

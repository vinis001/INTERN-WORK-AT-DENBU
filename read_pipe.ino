const int analogPin = A5;
int count=0;
void setup() 
{
  Serial.begin(115200);
  pinMode(analogPin, INPUT);
}

void loop() {
  if (Serial.available())
  {
    String receivedData=Serial.readString();
    int dat=receivedData.indexOf("Count = ");
    if (dat>=0){
      count++;
      receivedData.remove(0,8);
      //Serial.println(receivedData);
      int sensorValue=analogRead(analogPin);
      float voltage=sensorValue*(5.0/1023.0);
      Serial.print(count);
      Serial.print(",");      
      Serial.println(voltage,5);
      
      //delay(1000); 
    }
  }
   
  }


//int value = receivedData.substring(receivedData.indexOf('=') + 1).toInt();
//    String combinedData="";
//    int count=0;
//    for (int i=0;i<receivedData.length();i++) 
//    {
//      char currentChar=receivedData.charAt(i);
//      if (isDigit(currentChar)) 
//      {
//        combinedData+=currentChar;
//        count++;
//        if(count%1==0 || count%2==0 || count%3==0 || count%4==0 || count%5==0) {
//          combinedData +="";
//        }
//      }
//    }

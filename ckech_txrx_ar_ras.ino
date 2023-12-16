void setup() {
  Serial.begin(9600); 
}

void loop() {
  if (Serial.available()) {
    String data_received = Serial.readString();
    Serial.print("Received from Raspberry Pi: ");
    Serial.println(data_received);
    String dataTOsend = "Data received!";
    Serial.println(dataTOsend);
  }
}


//import serial
//
//ser = serial.Serial('/dev/ttyS0', 9600)  
//
//while True:
//    data_to_send = "HI FROM RASBERRY PI TO ARDUINO!"  
//    ser.write(data_to_send.encode())
//    data_received = ser.readline().decode().rstrip()
//    print("Received from Arduino:", data_received)
//    
//
//
//equals_pos = received_string.find('=') //receuved string from either the coaster module or the arduino, it finds equals position and extracts the data after the equals
//
//weight = received_string[equals_pos + 1:]
//
//weight = weight.strip()
//
//substance_weight=int(weight)
//
//print(substance_weight)

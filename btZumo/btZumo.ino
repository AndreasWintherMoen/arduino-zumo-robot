#include <PLabBTSerial.h>
#include <SoftwareSerial.h>

#define txPin 6
#define rxPin 4
PLabBTSerial Bluetooth(txPin, rxPin);
int ledPin = 8; // Test-LED
int Data;

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  Serial.println("Waiting for command...");
  Bluetooth.println("Waiting for command...");
  pinMode(ledPin, OUTPUT); // Test-LED
}

void loop() {
  BTupdate();
}

void BTupdate() {
  if (Bluetooth.available()){ //wait for data received
    Data=Bluetooth.read();
    if(Data=='0'){  
      function0();
    }
    else if(Data=='1'){
      function1();
    }
    else if(Data=='2'){
      function2();
    }
    else if(Data=='3'){
      function3();
    }
    else if(Data=='4'){
      function4();
    }
    else if(Data=='5'){
      function5();
    }
    else if(Data=='6'){
      function6();
    }  
    else{;}
  }
}

void function0() {
  digitalWrite(ledPin, LOW);
  Serial.println("LED Off!");
  Bluetooth.println("LED Off!");
}

void function1() {
  digitalWrite(ledPin,HIGH);
  Serial.println("LED On!");
  Bluetooth.println("LED On!");
}

void function2() {
  Serial.println("Function 2 called");
  Bluetooth.println("Function 2 called");
}

void function3() {
  Serial.println("Function 3 called");
  Bluetooth.println("Function 3 called");
}

void function4() {
  Serial.println("Function 4 called");
  Bluetooth.println("Function 4 called");
}

void function5() {
  Serial.println("Function 5 called");
  Bluetooth.println("Function 5 called");
}

void function6() {
  Serial.println("Function 6 called");
  Bluetooth.println("Function 6 called");
}

#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <PLabBTSerial.h>
#include <SoftwareSerial.h>

#define txPin 6
#define rxPin 3
PLabBTSerial Bluetooth(txPin, rxPin);
int Data;

#define buzzPin 2

ZumoMotors motors;
ZumoReflectanceSensorArray reflectanceSensors;

const int SURFACE_THRESHOLD = 750;
const int DISTANCE_THRESHOLD = 100;
const int FULL_SPEED = 500; //500
const int BACK_DURATION = 130;
const int SMALL_BACK_DURATION = 150;
const int TURN_DURATION = 230;
const int RANDOMNESS = 50;
const boolean TURN_STRATEGY = true;

unsigned int sensorValues[6];
unsigned long currentMillis;
unsigned long moveMillis;

boolean hasReceivedBluetooth = false;
Pushbutton button(ZUMO_BUTTON);
boolean finished = false;

void setup()
{
  Serial.begin(9600);
  Bluetooth.begin(9600);
  reflectanceSensors.init();
  pinMode(buzzPin, OUTPUT);
  /*while (hasReceivedBluetooth == false)
  {
    BTupdate();
  }*/
  button.waitForButton();
}

void loop()
{
  if (finished == false) 
  {
    currentMillis = millis();
  
    reflectanceSensors.read(sensorValues);
    moveWithoutEcho();
    
    BTupdate();
    
    delay(10);
  }
}

void playChargeFanfare()
{
  motors.setSpeeds(0,0);
  tone(buzzPin, 392, 700/3);
  delay(700/3+50);
  tone(buzzPin, 523, 700/3);
  delay(700/3+50);
  tone(buzzPin, 659, 700/3);
  delay(700/3+50);
  tone(buzzPin, 784, 700/4*3);
  delay(700/4*3+50);
  tone(buzzPin, 659, 700/4);
  delay(700/4+50);
  tone(buzzPin, 784, 700*2);
  delay(700*2+50);
  hasReceivedBluetooth = true;
  finished = true;
}

void BTupdate() {
  if (Bluetooth.available()){ //wait for data received
    Data=Bluetooth.read();
    Serial.println(Data);
    if(Data=='0'){  
      playChargeFanfare();
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
  Serial.println("LED Off!");
  Bluetooth.println("LED Off!");
}

void function1() {
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

void moveWithoutEcho()
{
  if (sensorValues[1] < SURFACE_THRESHOLD && sensorValues[5] < SURFACE_THRESHOLD)
  {
    motors.setSpeeds(-FULL_SPEED, -FULL_SPEED);
    delay(BACK_DURATION + random(0, RANDOMNESS / 2));
    if (random(0,100) > 50)
    {
      motors.setSpeeds(FULL_SPEED, -FULL_SPEED);
      moveMillis = millis() + TURN_DURATION + random(0,RANDOMNESS); 
    }
    else
    {
      motors.setSpeeds(-FULL_SPEED, FULL_SPEED);
      moveMillis = millis() + TURN_DURATION + random(0,RANDOMNESS); 
    }
    
  }
  else if (moveMillis > currentMillis) return;
  else if (sensorValues[1] < SURFACE_THRESHOLD)
  {
    motors.setSpeeds(-FULL_SPEED, -FULL_SPEED * 0.6);
    delay(SMALL_BACK_DURATION);
    motors.setSpeeds(-FULL_SPEED, FULL_SPEED);
    moveMillis = millis() + TURN_DURATION + random(0,RANDOMNESS);
  }
  else if (sensorValues[5] < SURFACE_THRESHOLD)
  {
    motors.setSpeeds(-FULL_SPEED * 0.6, -FULL_SPEED);
    delay(SMALL_BACK_DURATION);
    motors.setSpeeds(-FULL_SPEED, FULL_SPEED);
    moveMillis = millis() + TURN_DURATION + random(0,RANDOMNESS);
  }
  else
  {
    if (TURN_STRATEGY)
    {
      motors.setSpeeds(FULL_SPEED * 0.6, FULL_SPEED);
    }
    else
    {
      motors.setSpeeds(FULL_SPEED, FULL_SPEED);
    }
  }
}

void printSensors()
{
  Serial.print("Left: ");
  Serial.println(sensorValues[1]);
  
  Serial.print("Right: ");
  Serial.println(sensorValues[4]);
}

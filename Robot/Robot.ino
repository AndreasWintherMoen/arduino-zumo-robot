

#include <ZumoMotors.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <NewServo.h>

NewServo myServo;
ZumoMotors motors;
ZumoReflectanceSensorArray reflectanceSensors;

const int SURFACE_THRESHOLD = 750;
const int DISTANCE_THRESHOLD = 100;
const int FULL_SPEED = 500;
const int SLOW_SPEED = 300;

const int SERVO_PIN = 6;
const int ECHO_PIN = 3;
const int TRIGGER_PIN = 2;

unsigned int sensorValues[6];

unsigned long currentMillis;
unsigned long moveMillis;
unsigned long echoMillis;

int servoPosition = 90;
boolean servoTurningDirection = true; // true for right, false for left
const int SERVO_TURN_PER_TICK = 15;


void setup()
{
  Serial.begin(9600);
  reflectanceSensors.init();
  initializeServo();
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop()
{
  currentMillis = millis();

  //reflectanceSensors.read(sensorValues);
  //printSensors();
  //move();
  
  delay(50);
  searchForEnemy();
}



void initializeServo()
{
  myServo.attach(SERVO_PIN);
  myServo.write(servoPosition);
  delay(50);
}

boolean searchForEnemy()
{
  // TODO: Get distance from ultrasound sensor without blocking program execution
  turnProxSensor();
}


void ping()
{
  //Serial.println("pinging");
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  digitalWrite(ECHO_PIN, HIGH);
  
  echoMillis = millis();
}

void printDistance()
{
  Serial.println(millis() - echoMillis);
}

float getDistance()
{
  return 0;
}

void turnProxSensor()
{
  int newPos;
  if (servoTurningDirection) 
  {
    newPos = servoPosition + SERVO_TURN_PER_TICK;
    if (newPos >= 180)
    {
      newPos = 180;
      servoTurningDirection = !servoTurningDirection;
    }
  }
  else 
  {
    newPos = servoPosition - SERVO_TURN_PER_TICK;
    if (newPos <= 0)
    {
      newPos = 0;
      servoTurningDirection = !servoTurningDirection;
    }
  }
  servoPosition = newPos;
  myServo.write(newPos);
}

void move()
{
  if (moveMillis > currentMillis) return;
  
  if (sensorValues[0] > SURFACE_THRESHOLD || sensorValues[5] > SURFACE_THRESHOLD) backwards();
  else forwards();
}

void printSensors()
{
  Serial.print("Left: ");
  Serial.println(sensorValues[0]);
  
  Serial.print("Right: ");
  Serial.println(sensorValues[5]);
}

void turnLeft()
{
  motors.setSpeeds(-FULL_SPEED, FULL_SPEED);
  moveMillis = millis() + 150;
}

void turnRight()
{
  motors.setSpeeds(FULL_SPEED, -FULL_SPEED);
  moveMillis = millis() + 150;
}

void forwards()
{
  motors.setSpeeds(SLOW_SPEED, SLOW_SPEED);
}

void backwards()
{
  boolean willTurnRight = (sensorValues[0] > SURFACE_THRESHOLD);
  
  motors.setSpeeds(-FULL_SPEED,-FULL_SPEED);
  delay(150);
  if (willTurnRight) turnRight();
  else turnLeft();
}

void stop()
{
  motors.setSpeeds(0,0);
}

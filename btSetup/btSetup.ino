#include <PLabBTSerial.h>
#include <SoftwareSerial.h>

#define txPin 6
#define rxPin 3
PLabBTSerial Bluetooth(txPin, rxPin);

char BTName[] = "Gruppe4Test";
char ATCommand[] = "AT+NAMEPlab_";

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
}

void loop() {
  Serial.print("Setting new name for device to: PLab_");
  Serial.println(BTName);

  Bluetooth.write(ATCommand);
  Bluetooth.write(BTName);
  Bluetooth.write(0x0D);
  Bluetooth.write(0x0A);
  delay(1000);
}

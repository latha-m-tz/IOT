#include "arduino_secrets.h"
#include "thingProperties.h"
#include <Servo.h>  // Include Servo library

Servo myServo;  // Create Servo object to control the motor

void setup() {
  Serial.begin(9600);
  delay(1500);  // Wait for Serial Monitor to open
  
  initProperties();  // Initialize IoT properties

  ArduinoCloud.begin(ArduinoIoTPreferred  Connection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  myServo.attach(D2);  // Attach the servo to pin D2
}

void loop() {
  ArduinoCloud.update();
}

/*
  This function is called whenever the 'servo' property changes in the IoT Cloud.
*/
void onServoChange() {
  myServo.write(servo);  // Move the servo to the specified angle (0-180)
  Serial.print("Servo moved to: ");
  Serial.println(servo);  // Print the servo angle to Serial Monitor
}

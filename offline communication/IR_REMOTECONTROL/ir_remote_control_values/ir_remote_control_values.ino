#include <IRremote.h>

int IR_Recv = 11;   // IR Receiver Pin
int bluePin = 10;
int greenPin = 9;
int yellowPin = 8;

IRrecv irrecv(IR_Recv);
decode_results results;

void setup() {
  Serial.begin(9600);          // Starts serial communication
  irrecv.enableIRIn();         // Starts the receiver
  pinMode(bluePin, OUTPUT);     // Sets the digital pin as output
  pinMode(greenPin, OUTPUT);    // Sets the digital pin as output
  pinMode(yellowPin, OUTPUT);   // Sets the digital pin as output
}

void loop() {
  // Decodes the infrared input
  if (irrecv.decode(&results)) { 
    long int decCode = results.value;
    Serial.println(results.value);
    
    // Switch case to use the selected remote control button
    switch (results.value) {
      case 3772784863: // When you press the 1 button on Samsung remote
        digitalWrite(bluePin, HIGH);
        break;   
      case 3772780783: // When you press the 4 button on Samsung remote
        digitalWrite(bluePin ,LOW);   
        break;
      case 3772817503: // When you press the 2 button on Samsung remote
        digitalWrite(greenPin, HIGH);
        break;           
      case 3772813423: // When you press the 5 button on Samsung remote
        digitalWrite(greenPin, LOW);
        break;       
      case 3772801183: // When you press the 3 button on Samsung remote
        digitalWrite(yellowPin, HIGH);
        break;        
      case 3772797103: // When you press the 6 button on Samsung remote
        digitalWrite(yellowPin, LOW);
        break;
    }
    irrecv.resume(); // Receives the next value from the button you press
  }
  delay(10);
}

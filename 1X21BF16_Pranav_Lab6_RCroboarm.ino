#include <IRremote.h>
#include <Servo.h>

const int IR_PIN = 11;
IRrecv irrecv(IR_PIN);
Servo arm1;  
Servo arm2;   
Servo gripper;  

bool rightButtonPressed = false;
bool leftButtonPressed = false;
bool upButtonPressed = false;
bool downButtonPressed = false;
bool openGripperPressed = false;
bool closeGripperPressed = false;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  arm1.attach(4);
  arm2.attach(5);
  gripper.attach(6);
  arm1.write(90);
  arm2.write(90);
  gripper.write(90);  
}

void loop() {
  if (irrecv.decode()) {
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
    switch (irrecv.decodedIRData.decodedRawData) {
      case 0xBC43FF00: // Right button
        rightButtonPressed = true;
        break;
      case 0xBB44FF00: // Left button
        leftButtonPressed = true;
        break;
      case 0xB946FF00: // Up button
        upButtonPressed = true;
        break;
      case 0xEA15FF00: // Down button
        downButtonPressed = true;
        break;
      case 0xE619FF00: // Gripper open
        openGripperPressed = true;
        break;
      case 0xE916FF00: // Gripper close
        closeGripperPressed = true;
        break;
    }
    irrecv.resume();
  }

  if (rightButtonPressed) {
    arm1.write(arm1.read() - 10); // Rotate anticlockwise
  } else if (leftButtonPressed) {
    arm1.write(arm1.read() + 10); // Rotate clockwise
  } else if (upButtonPressed) {
    arm2.write(arm2.read() + 10); // Rotate clockwise
  } else if (downButtonPressed) {
    arm2.write(arm2.read() - 10); // Rotate anticlockwise
  } else if (openGripperPressed) {
    gripper.write(gripper.read() + 10); // Open gripper
  } else if (closeGripperPressed) {
    gripper.write(gripper.read() - 10); // Close gripper
  }

  if (!irrecv.decode()) {
    rightButtonPressed = false;
    leftButtonPressed = false;
    upButtonPressed = false;
    downButtonPressed = false;
    openGripperPressed = false;
    closeGripperPressed = false;
  }
  delay(10);
}

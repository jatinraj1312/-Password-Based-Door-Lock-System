#include <Keypad.h>
#include <Servo.h>

// Servo setup
#define SERVO_PIN 10
Servo lockServo;

// Define 4x3 Keypad layout
const byte ROWS = 4;
const byte COLS = 3;

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};  // ROW0 to ROW3
byte colPins[COLS] = {5, 4, 3};     // COL0 to COL2

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password configuration
const String correctPassword = "1234";
String enteredPassword = "";

void setup() {
  Serial.begin(9600);
  lockServo.attach(SERVO_PIN);
  lockServo.write(0); // Locked position
  Serial.println("🔐 4x3 Keypad Door Lock System Ready");
  Serial.println("Enter 4-digit password:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("*"); // Mask input
    enteredPassword += key;

    if (enteredPassword.length() == 4) {
      Serial.println(); // New line after password entry
      if (enteredPassword == correctPassword) {
        Serial.println("✅ Access Granted");
        unlockDoor();
      } else {
        Serial.println("❌ Incorrect Password");
        lockDoor();
      }
      enteredPassword = ""; // Reset after each attempt
      Serial.println("Enter 4-digit password:");
    }
  }
}

void unlockDoor() {
  lockServo.write(90);
  Serial.println("🔓 Door Unlocked");
  delay(5000); // Stay unlocked for 5 seconds
  lockDoor();
}

void lockDoor() {
  lockServo.write(0);
  Serial.println("🔒 Door Locked");
}

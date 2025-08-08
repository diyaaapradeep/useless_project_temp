const int irSensorPin = 7;   // IR sensor output pin
const int servoPin = 9;      // Servo motor signal pin

// Function to send servo to a specific angle
void moveServo(int angle) {
  // Map angle (0-180) to pulse width (500-2500 microseconds)
  int pulseWidth = map(angle, 0, 180, 500, 2500);

  // Send 50 pulses for smooth movement
  for (int i = 0; i < 50; i++) {
    digitalWrite(servoPin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(servoPin, LOW);
    delayMicroseconds(20000 - pulseWidth); // 20ms period
  }
}

void setup() {
  pinMode(irSensorPin, INPUT);
  pinMode(servoPin, OUTPUT);
  Serial.begin(9600);

  moveServo(0); // Start at 0 degrees
}

void loop() {
  int sensorValue = digitalRead(irSensorPin);

  if (sensorValue == LOW) { // Object detected
    moveServo(90);
    Serial.println("Object Detected - Servo at 90°");
  } else { // No object detected
    moveServo(0);
    Serial.println("No Object - Servo back to 0°");
  }

  delay(200); // Small delay for stability
}

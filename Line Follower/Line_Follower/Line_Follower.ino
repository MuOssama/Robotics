// Pin definitions for the motor driver
#define EnA 3
#define in1 7
#define in2 8

#define in3 6
#define in4 5
#define EnB 9

// Pin definitions for the IR sensors
#define L_S A2  // Left sensor
#define R_S A1  // Right sensor
#define Mid_S A0 // Middle sensor

// PID variables
int Kp = 50;  // Proportional constant
int error = 0;
int baseSpeed = 150;  // Base speed of the robot

// Timer variables
unsigned long previousTime = 0;
unsigned long currentTime = 0;
bool turning = false;

void setup() {
  pinMode(EnA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(EnB, OUTPUT);

  pinMode(L_S, INPUT);
  pinMode(R_S, INPUT);
  pinMode(Mid_S, INPUT);

  Serial.begin(9600);  // Start serial communication for debugging
}

void loop() {
  int leftSensor = digitalRead(L_S);
  int rightSensor = digitalRead(R_S);
  int midSensor = digitalRead(Mid_S);

  // Determine the error based on the sensor readings
  if (midSensor == HIGH && leftSensor == LOW && rightSensor == LOW) {
    // Line detected in the middle
    error = 0;
    turning = false;
  } else if (midSensor == LOW && leftSensor == HIGH && rightSensor == LOW) {
    // Line is slightly to the left
    error = -1;
    turning = false;
  } else if (midSensor == LOW && leftSensor == LOW && rightSensor == HIGH) {
    // Line is slightly to the right
    error = 1;
    turning = false;
  } else if (leftSensor == HIGH && midSensor == LOW && rightSensor == LOW) {
    // Line far to the left
    error = -2;
    turning = true;
  } else if (rightSensor == HIGH && midSensor == LOW && leftSensor == LOW) {
    // Line far to the right
    error = 2;
    turning = true;
  } else {
    // Line lost
    error = 0;
    turning = true;
  }

  // Calculate the motor speeds using proportional control
  int correction = Kp * error;
  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  // Limit the motor speeds to a maximum value
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // If the line is lost, turn the robot
  if (turning) {
    currentTime = millis();
    if (currentTime - previousTime > 2000) {
      // Stop the robot if it has been turning for more than 2 seconds without finding the line
      stopMotors();
      Serial.println("Line lost, stopping...");
      return;
    } else {
      if (error > 0) {
        turnRight();
        Serial.println("Turning right...");
      } else if (error < 0) {
        turnLeft();
        Serial.println("Turning left...");
      }
    }
  } else {
    previousTime = millis();  // Reset the timer
    // Set motor speeds
    analogWrite(EnA, leftSpeed);
    analogWrite(EnB, rightSpeed);

    // Drive motors forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    Serial.print("Left Speed: ");
    Serial.print(leftSpeed);
    Serial.print("  Right Speed: ");
    Serial.println(rightSpeed);
  }
}

void turnLeft() {
  analogWrite(EnA, baseSpeed);
  analogWrite(EnB, baseSpeed);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  analogWrite(EnA, baseSpeed);
  analogWrite(EnB, baseSpeed);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stopMotors() {
  analogWrite(EnA, 0);
  analogWrite(EnB, 0);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

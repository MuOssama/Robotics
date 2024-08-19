#define EnA 3
#define in1 7
#define in2 8

#define in3 5
#define in4 6
#define EnB 9

// IR Sensors Definitions
#define L_S   A2
#define R_S   A1
#define Mid_s A0

int Kp = 1;
int error = 0;
int baseSpeed = 100 ;// Initial Speed for motors to move

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);

  pinMode(L_S, INPUT);
  pinMode(R_S, INPUT);
  pinMode(Mid_s, INPUT);

  Serial.begin(9600);
}

void loop() {
  int leftSensorValue = digitalRead(L_S);
  int rightSensorValue = digitalRead(R_S);
  int middleSensorValue = digitalRead(Mid_s);
 if (leftSensorValue == 0 && rightSensorValue == 0 && middleSensorValue == 1) {
    error = 0; // On the line
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if (leftSensorValue == 1 && rightSensorValue == 1 && middleSensorValue == 1) {
    error = 0; // On the line
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(50);
    stop();
    
  }
  else if (leftSensorValue == 1 && middleSensorValue == 0) {
    error = -1; // Line is on the left
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  } else if (rightSensorValue == 1 && middleSensorValue == 0) {
    error = 1; // Line is on the right
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else if (rightSensorValue == 1 && middleSensorValue == 1) {
    error = 1; // Line is on the right
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else if (leftSensorValue == 1 && middleSensorValue == 1) {
    error = -1; // Line is on the left
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }  else if (leftSensorValue == 0 && rightSensorValue == 0 && middleSensorValue == 0) {
    error = 0; // Line lost, stop the robot
    stop();
    return;
  }

  int correction = Kp * error;

  int leftMotorSpeed = baseSpeed - correction;
  int rightMotorSpeed = baseSpeed + correction;

  setMotorSpeed(leftMotorSpeed, rightMotorSpeed);

  delay(10); // Small delay to stabilize readings
}

void setMotorSpeed(int leftSpeed, int rightSpeed) {
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  analogWrite(EnA, leftSpeed);
  analogWrite(EnB, rightSpeed);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(EnA, 0);
  analogWrite(EnB, 0);
}

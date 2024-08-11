// Pin Definitions
const int IN1 = 8;
const int IN2 = 7;

const int IN3 = 5;
const int IN4 = 6;

// defines pins numbers
const int trigPin = 13;
const int echoPin = 12;
// defines variables
long duration;
int distance;

// Direction Constants
const int FORWARD = 1;
const int BACKWARD = 0;

void setup() {
  // Set all the motor control pins to output
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  if(distance > 30 && distance < 400){
    forward();
    delay(80); 

    }

  else if(distance<=30){
    stop();
    right();
    delay(40);  
    stop();
    }


}

// Function to move the car forward
void forward() {
  runMotorA(FORWARD);
  runMotorB(FORWARD);
}

// Function to move the car backward
void backward() {
  runMotorA(BACKWARD);
  runMotorB(BACKWARD);
}

// Function to turn the car left
void left() {
  runMotorA(BACKWARD);
  runMotorB(FORWARD);
}

// Function to turn the car right
void right() {
  runMotorA(FORWARD);
  runMotorB(BACKWARD);
}

// Function to stop the car
void stop() {
  stopMotorA();
  stopMotorB();
}

// Function to run Motor A
void runMotorA(int direction) {
  if (direction == FORWARD) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
}

// Function to run Motor B
void runMotorB(int direction) {
  if (direction == FORWARD) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}

// Function to stop Motor A
void stopMotorA() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

// Function to stop Motor B
void stopMotorB() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

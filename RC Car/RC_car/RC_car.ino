#define EnA 3
#define in1 7
#define in2 8

#define in3 6
#define in4 5
#define EnB 9
#define Buzzer 10
#define LEDs 11

// Auxiliary pins
#define Aux1 12
#define Aux2 13

// Variables for light and buzzer state
bool lightState = false;
bool buzzerState = false;
bool aux1State = false;
bool aux2State = false;

// Function to move the car forward
void moveForward(int speed) {
  analogWrite(EnA, speed);
  analogWrite(EnB, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to move the car backward
void moveBackward(int speed) {
  analogWrite(EnA, speed);
  analogWrite(EnB, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Function to move the car right
void moveRight(int speed) {
  analogWrite(EnA, speed);
  analogWrite(EnB, speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Function to move the car left
void moveLeft(int speed) {
  analogWrite(EnA, speed);
  analogWrite(EnB, speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Function to stop the car
void stopCar() {
  analogWrite(EnA, 0);
  analogWrite(EnB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(EnA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(LEDs, OUTPUT);

  // Initialize auxiliary pins
  pinMode(Aux1, OUTPUT);
  pinMode(Aux2, OUTPUT);
  
  // Set initial states for auxiliaries
  digitalWrite(Aux1, LOW);
  digitalWrite(Aux2, LOW);
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readString();

    if (command.startsWith("Speed")) {
      int speed = command.substring(5).toInt() * 255 / 100;
      Serial.print("Speed set to: ");
      Serial.println(speed);
    }

    // Move Forward
    else if (command == "u") {
      moveForward(255);
      Serial.println("Moving forward");
    }
    
    // Move Backward
    else if (command == "d") {
      moveBackward(255);
      Serial.println("Moving backward");
    }
    
    // Move Right
    else if (command == "r") {
      moveRight(255);
      Serial.println("Turning right");
    }
    
    // Move Left
    else if (command == "l") {
      moveLeft(255);
      Serial.println("Turning left");
    }
    
    // Stop the car
    else if (command == "b") {
      stopCar();
      Serial.println("Car stopped");
    }
    
    // Toggle Lights
    else if (command == "L") {
      lightState = !lightState;
      digitalWrite(LEDs, lightState ? HIGH : LOW);
      Serial.print("Light toggled: ");
      Serial.println(lightState ? "ON" : "OFF");
    }
    
    // Toggle Buzzer
    else if (command == "B") {
      buzzerState = !buzzerState;
      digitalWrite(Buzzer, buzzerState ? HIGH : LOW);
      Serial.print("Buzzer toggled: ");
      Serial.println(buzzerState ? "ON" : "OFF");
    }
    
    // Toggle Aux1
    else if (command == "q") {
      aux1State = !aux1State;
      digitalWrite(Aux1, aux1State ? HIGH : LOW);
      Serial.print("Aux1 toggled: ");
      Serial.println(aux1State ? "ON" : "OFF");
    }
    
    // Toggle Aux2
    else if (command == "w") {
      aux2State = !aux2State;
      digitalWrite(Aux2, aux2State ? HIGH : LOW);
      Serial.print("Aux2 toggled: ");
      Serial.println(aux2State ? "ON" : "OFF");
    }
  }
}

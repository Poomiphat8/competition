
#define ENA 9
#define IN1 8
#define IN2 7

#define ENB 3
#define IN3 5
#define IN4 4

#define out_front A1
#define out_left A3
#define out_right A0

#define SPEED 80
#define FRONT_THRESHOLD 120
#define LEFT_THRESHOLD  150
#define RIGHT_THRESHOLD 120

#define TURN_TIME 170
#define BACK_TIME 340

int readSensor(int pin) {
  return analogRead(pin);
}

void stopMotor() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);
}

void turnRight() {
  stopMotor();

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);

  delay(TURN_TIME);
  stopMotor();
}

void turnLeft() {
  stopMotor();

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);

  delay(TURN_TIME);
  stopMotor();
}

void turnBack() {
  stopMotor();

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, SPEED);
  analogWrite(ENB, SPEED);

  delay(BACK_TIME);
  stopMotor();
}

void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotor();

  Serial.println("Maze Robot Started");
}


void loop() {

  int front = readSensor(out_front);
  int left = readSensor(out_left);
  int right = readSensor(out_right);

  bool wallFront = front <= FRONT_THRESHOLD;
  bool wallLeft = left <= LEFT_THRESHOLD;
  bool wallRight = right <= RIGHT_THRESHOLD;

  Serial.print("Front: ");
  Serial.print(front);

  Serial.print(" | Left: ");
  Serial.print(left);

  Serial.print(" | Right: ");
  Serial.println(right);

  if (!wallRight) {

    Serial.println("MOVE RIGHT");
    turnRight();

  }

  else if (!wallFront) {

    Serial.println("MOVE FORWARD");
    forward();

  }

  else if (!wallLeft) {

    Serial.println("MOVE LEFT");
    turnLeft();

  }

  else {

    Serial.println("MOVE BACK");
    turnBack();

  }

  delay(100);
}

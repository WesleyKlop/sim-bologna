#define MOTOR_1 10
#define MOTOR_2 11
#define MOTOR_3 12

int turn_time = 250;

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_3, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  TurnEngine(MOTOR_1);
  delay(10000);
}

void TurnEngine(int enginePin){
  digitalWrite(enginePin, LOW);
  delay(turn_time);                       
  digitalWrite(enginePin, HIGH);
}
#define MOTOR_1 9
#define MOTOR_2 10
#define MOTOR_3 11

#define BUTTON_1_PIN 2
#define BUTTON_2_PIN 3
#define BUTTON_3_PIN 4
#define BUTTON_4_PIN 5
#define BUTTON_5_PIN 6
#define BUTTON_6_PIN 7

int buttonPins[6] = {
    BUTTON_1_PIN,
    BUTTON_2_PIN,
    BUTTON_3_PIN,
    BUTTON_4_PIN,
    BUTTON_5_PIN,
    BUTTON_6_PIN,
};

void setupPins()
{
  for (int i = 0; i < 6; i++)
  {
    pinMode(buttonPins[i], INPUT);
  }
  pinMode(MOTOR_1, OUTPUT);
  pinMode(MOTOR_2, OUTPUT);
  pinMode(MOTOR_3, OUTPUT);
  //Set relays to high to turn them off
  digitalWrite(MOTOR_1, HIGH);
  digitalWrite(MOTOR_2, HIGH);
  digitalWrite(MOTOR_3, HIGH);
}

int turn_time = 250;

// the setup function runs once when you press reset or power the board
void setup() {
  setupPins();
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(BUTTON_1_PIN) == HIGH){
    TurnEngine(MOTOR_1);
    delay(1000);
  }
  else if (digitalRead(BUTTON_2_PIN) == HIGH){
    TurnEngine(MOTOR_2);
    delay(1000);
  }
  else if (digitalRead(BUTTON_3_PIN) == HIGH){
    TurnEngine(MOTOR_3);
    delay(1000);
  }
}

void TurnEngine(int enginePin){
  digitalWrite(enginePin, LOW);
  delay(turn_time);                       
  digitalWrite(enginePin, HIGH);
}
#define BUTTON_1_PIN 2
#define BUTTON_2_PIN 3
#define BUTTON_3_PIN 4
#define BUTTON_4_PIN 5
#define BUTTON_5_PIN 6
#define BUTTON_6_PIN 7

/*
 * 1. User presses a button
 * 2. Program validates input
 * 2.1 If input is correct, continue
 * 2.2 Else, ring the buzzer, go to next level
 * 3. Repeat.
 */

class Level
{
private:
  int buttons[6];
  int currentMove;

public:
  Level(int levelLayout[]);
  bool isFinished();
  bool doMove(int button);
};

Level::Level(int levelLayout[]) : buttons(levelLayout)
{
  buttons = levelLayout;
}

bool Level::isFinished()
{
  return currentMove == 5;
}

bool Level::doMove(int button)
{
  return buttons[currentMove] == button;
}

int buttonPins[6] = {
    BUTTON_1_PIN,
    BUTTON_2_PIN,
    BUTTON_3_PIN,
    BUTTON_4_PIN,
    BUTTON_5_PIN,
    BUTTON_6_PIN,
};

int levels[3][6] = {
    {1, 4, 6, 1, 0, 0},
    {2, 5, 3, 1, 6, 0},
    {4, 5, 3, 2, 3, 1},
};

int moves[5][6] = {};

int currentLevel = 1;

bool checkLevel(int levelToCheck)
{
  // Step through each given number and verify that it is the correct one
  for (int i = 0; i < 6 && levels[levelToCheck][i] != 0; i++)
  {
    int spot = levels[levelToCheck][i];
  }
}

void setupPins()
{
  for (int i = 0; i < 6; i++)
  {
    pinMode(buttonPins[i], INPUT);
  }
}

void setup()
{
  Serial.begin(9600);
  // Set output led
  pinMode(13, OUTPUT);

  setupPins();
}

void loop()
{
  bool on = false;
  // Check for any button press
  for (int i = 0; !on && i < 6; i++)
  {
    on = digitalRead(buttonPins[i]) == HIGH;
  }
  digitalWrite(13, on ? HIGH : LOW);
}

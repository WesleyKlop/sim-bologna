#define BUTTON_1_PIN 2
#define BUTTON_2_PIN 3
#define BUTTON_3_PIN 4
#define BUTTON_4_PIN 5
#define BUTTON_5_PIN 6
#define BUTTON_6_PIN 7
#define BUTTON_COUNT 6

#define LEVEL_1_PIN 9
#define LEVEL_2_PIN 10
#define LEVEL_3_PIN 11

#define BUZZER_PIN 12
#define DEBOUNCE_DELAY 50

/*
 * 1. User presses a button
 * 2. Program validates input
 * 2.1 If input is correct, continue
 * 2.2 Else, ring the buzzer, go to next level
 * 3. Repeat.
 */

int buttonPins[BUTTON_COUNT] = {
    BUTTON_1_PIN,
    BUTTON_2_PIN,
    BUTTON_3_PIN,
    BUTTON_4_PIN,
    BUTTON_5_PIN,
    BUTTON_6_PIN,
};
/**
 * Button state per pin. Structure is { { PREV, CURR }, ...}
 */
int buttonStates[BUTTON_COUNT][2] = {};
unsigned long lastDebounceTimes[BUTTON_COUNT] = {};

/**
 * Level layout. Numbers correspond to buttons
 */
int levels[3][BUTTON_COUNT] = {
    {1, 4, 6, 1, 0, 0},
    {2, 5, 3, 1, 6, 0},
    {4, 5, 3, 2, 3, 1},
};

int currentLevel = 0;
int currentStep = 0;

bool checkMove(int levelToCheck, int step, int pressedButton)
{
  return levels[levelToCheck][step] == pressedButton;
}

/**
 * Returns true if the current step in a level is 0
 */
bool isLevelFinished(int levelToCheck, int step)
{
  return levels[levelToCheck][step] == 0;
}

void setupPins()
{
  pinMode(13, OUTPUT);
  pinMode(LEVEL_1_PIN, OUTPUT);
  pinMode(LEVEL_2_PIN, OUTPUT);
  pinMode(LEVEL_3_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  for (int i = 0; i < 6; i++)
  {
    pinMode(buttonPins[i], INPUT);
  }
}

bool checkButtonPress(int buttonIndex)
{
  int reading = digitalRead(buttonPins[buttonIndex]);
  if (buttonStates[buttonIndex][0] != reading)
  {
    lastDebounceTimes[buttonIndex] = millis();
  }

  if ((millis() - lastDebounceTimes[buttonIndex]) > DEBOUNCE_DELAY)
  {
    if (reading != buttonStates[buttonIndex][1])
    {
      buttonStates[buttonIndex][1] = reading;

      // return true when the state changed to high
      if (reading == HIGH)
      {
        return true;
      }
    }
  }

  buttonStates[buttonIndex][0] = reading;
  return false;
}

void setup()
{
  Serial.begin(9600);

  setupPins();
}

void nextLevel()
{
  Serial.println("! Going to next level");
  currentLevel++;
  currentStep = 0;
}

void buzz(int t = 1000)
{
  tone(BUZZER_PIN, 500);
  delay(t);
  noTone(BUZZER_PIN);   
}

void loop()
{
  for (int i = 0; i < BUTTON_COUNT; i++)
  {
    int button = buttonPins[i];
    // Check if the user pressed a button this turn, if true, do a thing
    if (!checkButtonPress(i))
    {
      continue;
    }

    Serial.println((String) "User pressed button " + button);

    if (checkMove(currentLevel, currentStep, button))
    {
      Serial.println("  Which was correct!");
      // Was correct!
      currentStep++;
      if (!isLevelFinished(currentLevel, currentStep))
      {
        continue;
      }

      // Go to next level and reset steps also start motor to drop the kralen
      nextLevel();
      if (currentLevel == 3)
      {
        Serial.println("Game finished!!");
        // Finished!!!!!!!!
        // Dunno what we should do :shrug:
      }
    }
    else
    {
      Serial.println("  Which was wrong!");
      // Wrong!
      buzz(200);
      nextLevel();
    }
  }
}

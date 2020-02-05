/*
Program to controls a totem with pads that executes an "excercise" routine

created by Ben_Camelo
*/

// includes
#include <Keyboard.h>

// constants
#define ROUTINE_LENGTH 50
#define LEDS_POWER 6
#define UP_PAD_PIN A2    // TOP LEFT + WHITE
#define DOWN_PAD_PIN A1  // TOP RIGHT + RED
#define LEFT_PAD_PIN A0  // BOTTOM LEFT + GREEN
#define RIGHT_PAD_PIN A3 // BOTTOM RIGHT + BLACK
#define HAND_LEFT_PAD_PIN A4
#define HAND_RIGHT_PAD_PIN A5
#define PLAY_PAD_PIN 0
#define LED_UP_PAD_PIN 1    // TOP LEFT + WHITE
#define LED_DOWN_PAD_PIN 2  // TOP RIGHT + RED
#define LED_LEFT_PAD_PIN 4  // BOTTOM LEFT + GREEN
#define LED_RIGHT_PAD_PIN 7 // BOTTOM RIGHT + BLACK
#define LED_HAND_LEFT_PAD_PIN 9
#define LED_HAND_RIGHT_PAD_PIN 12
#define LED_PLAY_PAD_PIN 8
#define WELCOME_SCREEN 0
#define VIDEO_SCREEN 1
#define INSTRUCTION_SCREEN 2
#define ROUTINE_SCREEN 3
#define SCORE_SCREEN 4
#define WAIT_SCREEN 5
#define TILT 0
#define INTERCALATED 1
#define LOOP 2
#define RANDOM 3
#define BLINK_TIME 20

// global variables
int pointer = 0;
int currentScreen = 0;
char Routine[ROUTINE_LENGTH] = {'w','a','q','w','a','s','a','e','a','d','q','e','d','e','a','d','e','q','s','a','d','q','w','a','q','w','a','s','a','e','a','d','q','e','d','e','a','d','e','q','s','a','d','q','w'};
int resetCounter = 0;
bool buttonPressNoReboundFlag = true;
int score = 0;
int animation = TILT;
int timeout = 0;
int count = 0;
int playTime = 100;
int lightsOn = true;
int blinkTime = BLINK_TIME;
/// intialize
void setup()
{
  /* initialize LED OUTPUTS */
  // Serial Open
  Serial.begin(9600);
  // LED up
  pinMode(LED_UP_PAD_PIN, OUTPUT);
  digitalWrite(LED_UP_PAD_PIN, LOW);
  // LED down
  pinMode(LED_DOWN_PAD_PIN, OUTPUT);
  digitalWrite(LED_DOWN_PAD_PIN, LOW);
  // LED left
  pinMode(LED_LEFT_PAD_PIN, OUTPUT);
  digitalWrite(LED_LEFT_PAD_PIN, LOW);
  // LED right
  pinMode(LED_RIGHT_PAD_PIN, OUTPUT);
  digitalWrite(LED_RIGHT_PAD_PIN, LOW);
  // LED hand left
  pinMode(LED_HAND_LEFT_PAD_PIN, OUTPUT);
  digitalWrite(LED_HAND_LEFT_PAD_PIN, LOW);
  // LED hand right
  pinMode(LED_HAND_RIGHT_PAD_PIN, OUTPUT);
  digitalWrite(LED_HAND_RIGHT_PAD_PIN, LOW);
  // LED play
  pinMode(LED_PLAY_PAD_PIN, OUTPUT);
  digitalWrite(LED_PLAY_PAD_PIN, LOW);

  /* initialize LED OUTPUTS */

  // initialize button pads INPUTS
  pinMode(UP_PAD_PIN, INPUT_PULLUP);         // up
  pinMode(DOWN_PAD_PIN, INPUT_PULLUP);       // down
  pinMode(LEFT_PAD_PIN, INPUT_PULLUP);       // left
  pinMode(RIGHT_PAD_PIN, INPUT_PULLUP);      // right
  pinMode(HAND_LEFT_PAD_PIN, INPUT_PULLUP);  // hand left
  pinMode(HAND_RIGHT_PAD_PIN, INPUT_PULLUP); // hand right
  pinMode(PLAY_PAD_PIN, INPUT_PULLUP);       // play

  pinMode(LEDS_POWER, OUTPUT);
  digitalWrite(LEDS_POWER, LOW);
}

/// Activates LED in pad and reads the pad press
void activatePad(int padPin, int ledPin, char action)
{
  digitalWrite(ledPin, LOW);
  if (digitalRead(padPin) == LOW)
  {
    Keyboard.press(action);
    Keyboard.releaseAll();
    digitalWrite(ledPin, HIGH);
    score++;
  }
  playTime--;
}

void turnOn()
{
  digitalWrite(LED_UP_PAD_PIN, LOW);
  digitalWrite(LED_DOWN_PAD_PIN, LOW);
  digitalWrite(LED_LEFT_PAD_PIN, LOW);
  digitalWrite(LED_RIGHT_PAD_PIN, LOW);
  digitalWrite(LED_HAND_LEFT_PAD_PIN, LOW);
  digitalWrite(LED_HAND_RIGHT_PAD_PIN, LOW);
  digitalWrite(LED_PLAY_PAD_PIN, LOW);
}

void turnOff()
{
  digitalWrite(LED_UP_PAD_PIN, HIGH);
  digitalWrite(LED_DOWN_PAD_PIN, HIGH);
  digitalWrite(LED_LEFT_PAD_PIN, HIGH);
  digitalWrite(LED_RIGHT_PAD_PIN, HIGH);
  digitalWrite(LED_HAND_LEFT_PAD_PIN, HIGH);
  digitalWrite(LED_HAND_RIGHT_PAD_PIN, HIGH);
  digitalWrite(LED_PLAY_PAD_PIN, HIGH);
}

/// Activates LED in pad and reads the pad press
void toggleLeds()
{
  blinkTime--;
  if (blinkTime < 1)
  {
    lightsOn = !lightsOn;
    blinkTime = BLINK_TIME;
  }
  if (lightsOn)
    turnOn();
  else
    turnOff();
}

void toggleLed(int ledPin)
{
  blinkTime--;
  if (blinkTime < 1)
  {
    lightsOn = !lightsOn;
    blinkTime = BLINK_TIME;
  }
  if (lightsOn)
    digitalWrite(ledPin, LOW);
  else
    digitalWrite(ledPin, HIGH);
}

/// main
void loop()
{
  delay(10);
  if (count > 100)
  {
    count = 0;
    //Serial.println(String("Screen: ") + currentScreen);
  }
  count++;
  switch (currentScreen)
  {
  case WELCOME_SCREEN:
    turnOn();
    toggleLed(LED_PLAY_PAD_PIN);
    if (digitalRead(PLAY_PAD_PIN) == LOW)
    {
      if (buttonPressNoReboundFlag)
      {
        Keyboard.press('z');
        Keyboard.releaseAll();
        currentScreen = VIDEO_SCREEN;
        timeout = 1500;
      }
      buttonPressNoReboundFlag = false;
    }
    else if (digitalRead(PLAY_PAD_PIN) == HIGH)
    {
      buttonPressNoReboundFlag = true;
    }
    break;
  case VIDEO_SCREEN:
    turnOn();
    timeout--;
    if (timeout < 2)
    {
      currentScreen = INSTRUCTION_SCREEN;
      timeout = 0;
    }
    break;
  case INSTRUCTION_SCREEN:
    turnOn();
    toggleLed(LED_PLAY_PAD_PIN);
    if (digitalRead(PLAY_PAD_PIN) == LOW)
    {
      if (buttonPressNoReboundFlag)
      {
        Keyboard.press('z');
        Keyboard.releaseAll();
        currentScreen = WAIT_SCREEN;
        timeout = 600;
      }
      buttonPressNoReboundFlag = false;
    }
    else if (digitalRead(PLAY_PAD_PIN) == HIGH)
    {
      buttonPressNoReboundFlag = true;
    }
    break;
  case WAIT_SCREEN:
    turnOn();
    timeout--;
    if (timeout < 2)
    {
      currentScreen = ROUTINE_SCREEN;
      turnOff();
      timeout = 2000;
    }
    break;
  case ROUTINE_SCREEN:
    timeout--;
    // select pad
    switch (Routine[pointer])
    {
    case 'w':
      activatePad(UP_PAD_PIN, LED_UP_PAD_PIN, 'w');
      break;
    case 's':
      activatePad(DOWN_PAD_PIN, LED_DOWN_PAD_PIN, 's');
      break;
    case 'a':
      activatePad(LEFT_PAD_PIN, LED_LEFT_PAD_PIN, 'a');
      break;
    case 'd':
      activatePad(RIGHT_PAD_PIN, LED_RIGHT_PAD_PIN, 'd');
      break;
    case 'q':
      activatePad(HAND_LEFT_PAD_PIN, LED_HAND_LEFT_PAD_PIN, 'q');
      break;
    case 'e':
      activatePad(HAND_RIGHT_PAD_PIN, LED_HAND_RIGHT_PAD_PIN, 'e');
      break;
    }
    if (playTime < 1)
    {
      pointer++;
      playTime = 100;
      turnOff();
    }
    // if end of routine back to initial state
    if (Routine[pointer] == '\0' || timeout < 2)
    {
      pointer = 0;
      currentScreen = SCORE_SCREEN;
      timeout = 2000;
    }
    break;
  case SCORE_SCREEN:
    // Serial.println(score);
    toggleLeds();
    timeout--;
    if (digitalRead(PLAY_PAD_PIN) == LOW || timeout < 2)
    {
      if (buttonPressNoReboundFlag)
      {
        Keyboard.press('z');
        Keyboard.releaseAll();
        currentScreen = WELCOME_SCREEN;
      }
      buttonPressNoReboundFlag = false;
    }
    else if (digitalRead(PLAY_PAD_PIN) == HIGH)
      buttonPressNoReboundFlag = true;
    break;
  }

  if (digitalRead(PLAY_PAD_PIN) == LOW)
  {
    // Serial.print(String("Play"));
    //Serial.println(resetCounter);
    resetCounter++;
    if (resetCounter > 400)
    {
      pointer = 0;
      score = 0;
      playTime = 100;
      resetCounter = 0;
      currentScreen = WELCOME_SCREEN;
      turnOn();
      Keyboard.press('r');
      Keyboard.releaseAll();
      buttonPressNoReboundFlag = false;
    }
  }
  else
  {
    resetCounter = 0;
  }
}

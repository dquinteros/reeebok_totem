/*
Program to controls a totem with pads that executes an "excercise" routine

created by Ben_Camelo
*/

// includes
#include <Keyboard.h>

// constants
#define ROUTINE_LENGTH 20

// global variables
char Routine[ROUTINE_LENGTH];
int pointer = 0;
bool isRouineActive = false;

/// intialize
void setup() {
  Routine[0] = 0;
  // open the serial port:
  Serial.begin(9600);
  // initialize control over the keyboard:
  Keyboard.begin();
  
  // initialize LED OUTPUTS
  
  // LED up
  pinMode(0, OUTPUT);
  digitalWrite(0, HIGH);
  // LED down
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  // LED left
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  // LED right
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  // LED hand left
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  // LED hand right
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH);
  // LED play
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  
  // initialize button pads INPUTS
  pinMode(7, INPUT_PULLUP); // up
  pinMode(8, INPUT_PULLUP); // down
  pinMode(9, INPUT_PULLUP); // left
  pinMode(10, INPUT_PULLUP); // right
  pinMode(11, INPUT_PULLUP); // hand left
  pinMode(12, INPUT_PULLUP); // hand right
  pinMode(13, INPUT_PULLUP); // play
  
  // initialize routine
  for(int i = 0; i < ROUTINE_LENGTH; i++) {
    char availableCommands[7] = {'w','a','s','d','q','e','z'};
        Routine[i] = availableCommands[random(0, 5)];
  } 
}

/// Activates LED in pad and reads the pad press
void activatePad(int padPin, int ledPin, char action) {
  digitalWrite(ledPin, LOW);
  for (int timer = 0; timer < 20; timer++){
    if (digitalRead(padPin) == LOW) {
      Serial.flush();
      Serial.println("Point");
      Keyboard.press(action);
      Keyboard.releaseAll();
      digitalWrite(ledPin, HIGH);
      break;
    }
    delay(100);
  }
  Serial.println("Finished Pad");
  digitalWrite(ledPin, HIGH);
  delay(500);
}

/// main
void loop() {

    // if up input press w
  if (digitalRead(7) == LOW && isRouineActive == false) {
      Keyboard.press('w');
      Keyboard.releaseAll();
    }
      // if down input press s
  if (digitalRead(8) == LOW && isRouineActive == false) {
      Keyboard.press('s');
      Keyboard.releaseAll();
    }
      // if play input press a
  if (digitalRead(9) == LOW && isRouineActive == false) {
      Keyboard.press('a');
      Keyboard.releaseAll();
    }
      // if play input press d
  if (digitalRead(10) == LOW && isRouineActive == false) {
      Keyboard.press('d');
      Keyboard.releaseAll();
    }
      // if play input press q
  if (digitalRead(11) == LOW && isRouineActive == false) {
      Keyboard.press('q');
      Keyboard.releaseAll();
    }
      // if play input press e
  if (digitalRead(12) == LOW && isRouineActive == false) {
      Keyboard.press('e');
      Keyboard.releaseAll();
    }
  // if play input start routine
  if (digitalRead(13) == LOW && isRouineActive == false) {
    isRouineActive = true;
    }
      
  // if routine then execute pad
  if (strlen(Routine) > 0 && isRouineActive == true) {
    
    // read next step in routine:
    char routineChar = Routine[pointer];
    
    // select pad
    switch (routineChar) {
      case 'w':
        Serial.println(routineChar);
        activatePad(5, 3, 'w');
        break;
      case 's':
        Serial.println(routineChar);
        activatePad(5, 3, 's');
        break;
      case 'a':
        Serial.println(routineChar);
        activatePad(5, 3, 'a');
        break;
      case 'd':
        Serial.println(routineChar);
        activatePad(5, 3, 'd');
        break;
      case 'q':
        Serial.println(routineChar);
        activatePad(5, 3, 'q');
        break;
      case 'e':
        Serial.println(routineChar);
        activatePad(5, 3, 'e');
        break;
      default:
        Serial.println(routineChar);
        break;
    }
    pointer++;
    
    // if end of routine back to initial state
    if (Routine[pointer] == '\0') {
      // memset(Routine, 0, sizeof(integerArray));
      pointer = 0;
      isRouineActive = false;
    }
  }
}

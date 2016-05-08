//PINS
const int led[] = {13, 12, 11, 10, 9, 8, 7, 6, 5}; //CHANGE
const int speaker = 2;
const int highscorebutton = 4;
const int restart = 3;

//constants
const int threshold = 200;
const int winDuration = 75;
const int winDelayDuration = 75;
const int winPitch = 1500;
const int missPitch = 500;
const int missDuration = 100;

//global variables
int timeOn = 2000;
int highscore = 0;
int score = 0;
int missed = 0;

int startDelay[] = {((timeOn*2)/3), ((timeOn*6)/3), ((timeOn*8)/3)};
unsigned long frogTime[] = {0, 0, 0};
unsigned long timeAlive[] = {0, 0, 0};
int frog[] = { -1, -1, -1};

boolean setStartDelay[] = {true, true, true};
boolean setFrogTime[] = {true, true, true};
boolean touch[] = {false, false, false, false, false, false};

void setup() {
  //LED's
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  pinMode(led[4], OUTPUT);
  pinMode(led[5], OUTPUT);
  pinMode(led[6], OUTPUT);
  pinMode(led[7], OUTPUT);
  pinMode(led[8], OUTPUT);

  //Other
  pinMode(speaker, OUTPUT);
  pinMode(highscorebutton, INPUT);
  pinMode(restart, INPUT);

  //touch areas
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  Serial.begin(9600);  // connect to the serial port
  randomSeed(121); // random number generator seed
}

void loop () {
  //reset touch variables
  for (int i = 0; i < 6; i++) {
    touch[i] = false;
  }

  //detect game over state
  if (missed > 3) {
    tone(speaker,400,800);
    delay(1000);
    gameover(true, true);
  }
  //detect high score state
  if (digitalRead(highscorebutton)) {
    gameover(false, true);
  }
  //detect restart state
  if (digitalRead(restart)) {
    gameover(false, false);
  }

  //if we need to start frog1
  if (setFrogTime[0]) {
    //delay the appearance
    if (setStartDelay[0]) {
      frogTime[0] = millis();
      setStartDelay[0] = false;
    }
    else {
      //turn on the frog
      if ((millis() - frogTime[0]) > startDelay[0]) {
        startDelay[0] = ((timeOn*2)/3);
        setStartDelay[0] = true;
        //prevents double assign
        while(true) {
          int r = random(0,5);
          if((frog[1] != r) & (frog[2] != r)){
            frog[0] = r;
            break;
          }
        }
        digitalWrite(led[frog[0]], HIGH);
        timeAlive[0] = millis();
        setFrogTime[0] = false;
      }
    }
  }
  else {
    int timetmp = millis() - timeAlive[0];
    //if the frog has been alive too long, turn off and count a miss
    if (timetmp > timeOn) {
      tone(speaker, missPitch, missDuration);
      digitalWrite(led[missed + 6], HIGH);
      missed += 1;
      setFrogTime[0] = true;
      digitalWrite(led[frog[0]], LOW);
    }
  }

  //see comments aboce
  if (setFrogTime[1]) {
    if (setStartDelay[1]) {
      frogTime[1] = millis();
      setStartDelay[1] = false;
    }
    else {
      if ((millis() - frogTime[1]) > startDelay[1]) {
        setStartDelay[1] = true;
        startDelay[1] = ((timeOn*2)/3);
        while(true) {
          int r = random(0,5);
          if((frog[0] != r) & (frog[2] != r)){
            frog[1] = r;
            break;
          }
        }
        digitalWrite(led[frog[1]], HIGH);
        timeAlive[1] = millis();
        setFrogTime[1] = false;
      }
    }
  }
  else {
    int timetmp = millis() - timeAlive[1];
    if (timetmp > timeOn) {
      tone(speaker, missPitch, missDuration);
      digitalWrite(led[missed + 6], HIGH);
      missed += 1;
      setFrogTime[1] = true;
      digitalWrite(led[frog[1]], LOW);
    }
  }

  //see comments above
  if (setFrogTime[2]) {
    if (setStartDelay[2]) {
      frogTime[2] = millis();
      setStartDelay[2] = false;
    }
    else {
      if ((millis() - frogTime[2]) > startDelay[2]) {
        setStartDelay[2] = true;
        startDelay[2] = ((timeOn*2)/3);
        while(true) {
          int r = random(0,5);
          if((frog[0] != r) & (frog[1] != r)){
            frog[2] = r;
            break;
          }
        }
        digitalWrite(led[frog[2]], HIGH);
        timeAlive[2] = millis();
        setFrogTime[2] = false;
      }
    }
  }
  else {
    int timetmp = millis() - timeAlive[2];
    if (timetmp > timeOn) {
      tone(speaker, missPitch, missDuration);
      digitalWrite(led[missed + 6], HIGH);
      missed += 1;
      setFrogTime[2] = true;
      digitalWrite(led[frog[2]], LOW);
    }
  }

  //detect touches
  if (analogRead(A0) > threshold) {
    touch[0] = true;
  }
  else if (analogRead(A1) > threshold) {
    touch[1] = true;
  }
  else if (analogRead(A2) > threshold) {
    touch[2] = true;
  }
  else if (analogRead(A3) > threshold) {
    touch[3] = true;
  }
  else if (analogRead(A4) > threshold) {
    touch[4] = true;
  }
  else if (analogRead(A5) > threshold) {
    touch[5] = true;
  }

  //check if one of the touches matches one of the frogs
  for (int i = 0; i < 6; i++) {
    if(!setFrogTime[0]) checkHit(i, 0);
    if(!setFrogTime[1]) checkHit(i, 1);
    if(!setFrogTime[2]) checkHit(i, 2);
  }
}//end of loop

void checkHit(int i, int frogNum) {
  //if we have a hit turn off the frog, let it start again at a new random 
  //spot, increase the speed of the game
  if (touch[i] & (frog[frogNum] == i)) {
    digitalWrite(led[frog[frogNum]], LOW);
    setStartDelay[frogNum] = true;
    score += 1;
    if(timeOn > 1000) {
      timeOn += -40;
    }
    else if(timeOn > 500) {
      timeOn += -10;
    }
    setFrogTime[frogNum] = true;
  }
}

void gameover(boolean showScore, boolean showHigh) {
  //reset all variables and states
  boolean skipHigh = false;
  timeOn = 3000;
  startDelay[0] = ((timeOn*2)/3);
  startDelay[1] = ((timeOn*6)/3);
  startDelay[2] = ((timeOn*8)/3);
  setStartDelay[0] = true;
  setStartDelay[1] = true;
  setStartDelay[2] = true;
  setFrogTime[0] = true;
  setFrogTime[1] = true;
  setFrogTime[2] = true;
  frogTime[0] = 0;
  frogTime[1] = 0;
  frogTime[2] = 0;
  timeAlive[0] = 0;
  timeAlive[1] = 0;
  timeAlive[2] = 0;
  frog[0] = -1;
  frog[1] = -1;
  frog[2] = -1;
  
  missed = 0;
  if (showScore) {
    //beat the high score
    if (score > highscore) {
      skipHigh = true;
      highscore = score;
      tone(speaker, winPitch, winDuration);
      delay(winDelayDuration);
      noTone(speaker);
      delay(winDelayDuration);
      tone(speaker, winPitch, winDuration);
      delay(winDelayDuration);
      noTone(speaker);
      delay(winDelayDuration);
      tone(speaker, winPitch, winDuration);
      delay(winDelayDuration);
      noTone(speaker);
    }
    displayscore(score);
  }
  if (showHigh & !skipHigh) {
    tone(speaker,1100,600);
    displayscore(highscore);
  }
  score = 0;
}

//writes scores by ticking up the 9 LED's and resetting, one tick for each score
void displayscore(int score) {
  delay(1000);
  for (int k = 0; k < 10; k++) {
    digitalWrite(led[k], LOW);
  }
  int current = score;
  int ledNum = 0;
  while (score > 0) {
    Serial.println(score);
    digitalWrite(led[ledNum], HIGH);
    delay(500);
    score += -1;
    if(score == 0) break;
    ledNum += 1;
    if (ledNum == 9) {
      delay(200);
      for (int j = 0; j < 10; j++) {
        digitalWrite(led[j], LOW);
      }
      ledNum = 0;
    }
  }
  for (int j = 0; j < 10; j++) {
    digitalWrite(led[j], LOW);
  }
  delay(1500);
}







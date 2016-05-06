//PINS
const int led[] = {13,12,11,10,9,8,7,6,5}; //CHANGE
const int speaker = 2;
const int highscorebutton = 4;
const int restart = 3;

//constants
const int threshold = 200;
const int winDuration = 75;
const int winDelayDuration = 75;
const int winPitch = 1500;
const int missPitch = 2000;
const int missDuration = 100;

//global variables
int timeOn = 1000;
int highscore = 0;
int score = 0;
int timeAlive[] = {0,0,0};
int missed = 0;
int frog[] = {-1,-1,-1};
boolean setTime[] = {true,false,false};
boolean touch[] = {false,false,false,false,false,false};

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
  pinMode(led[9], OUTPUT); 
  pinMode(led[10], OUTPUT); 
  pinMode(led[11], OUTPUT); 

  //touch areas
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);

  Serial.begin(9600);  // connect to the serial port
}

void loop () {
  for(int i=0; i<6; i++){
    touch[i] = false;
  }

  if(missed > 3) {
    gameover(true,true);
  }
  if(digitalRead(highscorebutton)){
    gameover(false,true);
  }
  if(digitalRead(restart)){
    gameover(false,false);
  }


  //NEED TIMERS TO STAGER SETTIMES


  
  if(setTime[0]) {
    frog[0] = random(0,5);
    digitalWrite(led[frog[0]],HIGH);
    timeAlive[0] = millis();
    setTime[0] = false;
  }
  else {
    int timetmp = millis()-timeAlive[0];
    if(timetmp > timeOn) {
      tone(speaker, missPitch, missDuration);
      digitalWrite(led[missed+6],HIGH);
      missed += 1;
      setTime[0] = true;
      digitalWrite(led[frog[0]],LOW);
    }
  }
  
  if(setTime[1]) {
    frog[1] = random(0,5);
    digitalWrite(led[frog[1]],HIGH);
    timeAlive[1] = millis();
    setTime[1] = false;
  }
  else {
    int timetmp = millis()-timeAlive[1];
    if(timetmp > timeOn) {
      tone(speaker, missPitch, missDuration);
      digitalWrite(led[missed+6],HIGH);
      missed += 1;
      setTime[1] = true;
      digitalWrite(led[frog[1]],LOW);
    }
  }
  
  if(setTime[2]) {
    frog[2] = random(0,5);
    digitalWrite(led[frog[2]],HIGH);
    timeAlive[2] = millis();
    setTime[2] = false;
  }
  else {
    int timetmp = millis()-timeAlive[2];
    if(timetmp > timeOn) {
      tone(speaker, missPitch, missDuration);
      digitalWrite(led[missed+6],HIGH);
      missed += 1;
      setTime[2] = true;
      digitalWrite(led[frog[2]],LOW);
    }
  }
  
  if(analogRead(A0) > threshold) {
    touch[0] = true;
  }
  else if(analogRead(A1) > threshold) {
    touch[1] = true;
  }
  else if(analogRead(A2) > threshold) {
    touch[2] = true;
  }
  else if(analogRead(A3) > threshold) {
    touch[3] = true;
  }
  else if(analogRead(A4) > threshold) {
    touch[4] = true;
  }
  else if(analogRead(A5) > threshold) {
    touch[5] = true;
  }

  for(int i=0; i<6; i++) {
    checkHit(i,0);
    checkHit(i,1);
    checkHit(i,2);
  }
  
}//end of loop

void checkHit(int i, int frogNum) {
  if(touch[i] & (frog[frogNum] == i)) {
    digitalWrite(led[frog[frogNum]],LOW);
    score += 1;
    timeOn += -20;
    setTime[frogNum] = true;
  }
}

void gameover(boolean showScore, boolean showHigh) {
  boolean skipHigh = false;
  missed = 0;
  if(showScore) {
    if(score > highscore) {
      skipHigh = true;
      highscore = score;
      tone(speaker,winPitch,winDuration);
      delay(winDelayDuration);
      noTone(speaker);
      delay(winDelayDuration);
      tone(speaker,winPitch,winDuration);
      delay(winDelayDuration);
      noTone(speaker);
      delay(winDelayDuration);
      tone(speaker,winPitch,winDuration);
      delay(winDelayDuration);
      noTone(speaker);
    }
    displayscore(score);
  }
  if(showHigh & !skipHigh){
    displayscore(highscore);
  }
  score = 0;
}

void displayscore(int score) {
  int current = score;
  int ledNum = 0;
  while(score > 0) {
    digitalWrite(led[ledNum],HIGH);
    delay(100);
    score += -1;
    ledNum += 1;
    if(ledNum == 9) {
      delay(200);
      for(int j=0; j<8; j++) {
        digitalWrite(led[j],LOW);
      }
      ledNum = 0;
    }
  }
  delay(1000);
}

  





//LED pins
const int led[] = {13,12,11,10,9,8,7,6,5,4,3,2}; //CHANGE


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

  pinMode(A0,OUTPUT);

  Serial.begin(9600);  // connect to the serial port
}

void loop () {
  digitalWrite(led[0],HIGH);
  digitalWrite(led[1],HIGH);
  delay(1000);
  tone(A0,16000,500);
  digitalWrite(led[0],LOW);
  digitalWrite(led[1],LOW);  
  delay(1000);
  
}//end of loop


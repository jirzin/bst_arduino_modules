int sensor1Pin = 8;
int led1Pin = 13;

void setup(){
  pinMode(sensor1Pin, INPUT);
  pinMode(led1Pin, OUTPUT);
}

void loop(){
  digitalWrite(led1Pin, digitalRead(sensor1Pin));
}

// c code for arduino based board Eunuch
// this particular program is a light Dimmer
//
// author: Bastlit

// pin numbers

int inPin = 2;
int outPin = 9;

// input signal smoothing
int inX = 0;             // input signal
int averageOf = 20;    // number of input values for average
int xMax = 255;

int fMax =255;
//int state=0;
int fSpeed = 40;
int f = 0;

//int readingInterval = 200;

void setup(){

  pinMode(inPin,INPUT);
  pinMode(outPin,OUTPUT);

}

void loop(){
  for(int n = 0; n < fMax; n++){
    f = n;
    analogWrite(outPin,f);
    delay(fSpeed);
  }
  digitalWrite(outPin,f);
  delay(10000);
  for(int n = fMax; n > 0; n--){
    f = n;
    analogWrite(outPin,f);
    delay(fSpeed);
  }
  delay(100);
}

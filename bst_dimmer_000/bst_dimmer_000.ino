// c code for arduino based board Eunuch
// this particular program is a light Dimmer
//
// author: Bastlit

// pin numbers
int inPin = 2;
int outPin = 13;


// input signal smoothing
int inX = 0;             // input signal
int averageOf = 20;    // number of input values for average
int xMax = 255;


int readingInterval = 200;


void setup(){

  pinMode(inPin,INPUT);
  pinMode(outPin,OUTPUT);

}

void loop(){



}

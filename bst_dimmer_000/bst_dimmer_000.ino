// c code for arduino based board Eunuch
// this particular program is a light Dimmer
// logic on board is inverted
// lights are on when board is writing logical LOW on its output
// when signal on in pin is HIGH (cca 3.3v ) lights are slowly dimming to full light
// sweeping from 255 = no light to 0 = full light at speed
// when signal on in pin is LOW do an inverse sweep
//
// author: Bastlit

// pin numbers

int inPin = 2;
int outPin = 9;

int fMax =255;
int fSpeed = 12;
int f = 255;

//int readingInterval = 200;

void setup(){
  pinMode(inPin,INPUT);
  pinMode(outPin,OUTPUT);
}

void loop(){
  if(digitalRead(inPin)==LOW){
    f = min(f+1,255);
    delay(fSpeed);
  } else {
    f = max(f-1,0);
    delay(fSpeed);
  }
  analogWrite(outPin,f);
}

/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;

const int x = 20;
int c = x;
boolean b = true;
const int KEY1 = 0xa90;
const int KEY2 = 0x8aa;

void setup()
{
  //Serial.begin(9600);
}



void loop() {
  c--;
  if(c<0){
    c=x;
    b=!b;
  }

  for (int i = 0; i < 3; i++) {
    if(b){
      irsend.sendSony(KEY1, 12); // Sony TV power code
    }else{
      irsend.sendSony(KEY2, 12); // Sony TV power code
    }
    delay(40);
  }
}

/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;

const int KEY1 = 0xffffbeda;

void setup()
{
}

void loop() {
  for (int i = 0; i < 3; i++) {
    irsend.sendNEC(KEY1, 32); // Sony TV power code
    delay(40);
  }
}

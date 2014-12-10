#include <IRremote.h>

////////////////////////////// IR REMOTE LIBRARY SETUP //////////////////////////////

// real board pins are 0, 3, 5, 6
const int RECV_PIN1 = 0;           //receiver #1 data pin
const int RECV_PIN2 = 3;           //receiver #2 data pin
const int RECV_PIN3 = 5;           //receiver #3 data pin
const int RECV_PIN4 = 6;           //receiver #4 data pin

IRrecv irrecv1(RECV_PIN1);
decode_results results1;      //receiver #1 results

IRrecv irrecv2(RECV_PIN2);
decode_results results2;      //receiver #2 results

IRrecv irrecv3(RECV_PIN3);
decode_results results3;      //receiver #3 results
//
IRrecv irrecv4(RECV_PIN4);
decode_results results4;      //receiver #4 results

////////////////////////////// LOGIC TIMERS AND OUTPUT TO RPI //////////////////////////////
const int FOCUS_PIN = 4;

/*const int FPIN1 = 4;
const int FPIN2 = 8;
const int FPIN3 = 9;
const int FPIN4 = 10;
*/
unsigned long actualTime = 0;

const unsigned long globalTickInterval = 200;

unsigned long lastTick1 = 0;
unsigned long lastTick2 = 0;
unsigned long lastTick3 = 0;
unsigned long lastTick4 = 0;

int detectorFocus1 = 0;
int detectorFocus2 = 0;
int detectorFocus3 = 0;
int detectorFocus4 = 0;

const int detectorNumberLimit = 2;  // number of receiving detectors for board to be focused

int boardIsFocused = 0;

const int KEY1 = 2704;
/*const int KEY2 = 2705;
const int KEY3 = 2706;

int pattern1[] = {0,0,0};
int pattern2[] = {0,0,0};
int pattern3[] = {0,0,0};
int pattern4[] = {0,0,0};
*/
const boolean DEBUG_SERIAL = false;

void setup()
{
  if(DEBUG_SERIAL){
    Serial.begin(9600);
  }
  irrecv1.enableIRIn(); // Start the receiver #1
  irrecv2.enableIRIn(); // Start the receiver #2
  irrecv3.enableIRIn(); // Start the receiver #3
  irrecv4.enableIRIn(); // Start the receiver #4

  pinMode(FOCUS_PIN,OUTPUT);

  for(int i = 4; i > 0; i--){
    digitalWrite(FOCUS_PIN,HIGH);
    delay(100);
    digitalWrite(FOCUS_PIN,LOW);
    delay(100);
  }
  /*  pinMode(FPIN1,OUTPUT);
  pinMode(FPIN2,OUTPUT);
  pinMode(FPIN3,OUTPUT);
  pinMode(FPIN4,OUTPUT);
  */
  /*  digitalWrite(FPIN1, LOW);
  digitalWrite(FPIN2, LOW);
  digitalWrite(FPIN3, LOW);
  digitalWrite(FPIN4, LOW);*/
}

void loop() {

  actualTime = millis();

  if (irrecv1.decode(&results1)) {
    if(results1.value==KEY1){
      lastTick1 = actualTime;
      if(DEBUG_SERIAL){
        Serial.print("\n1: ");
        Serial.print(results1.value, HEX);   //print code from receiver #1
      }
    }
    irrecv1.resume(); // Receive the next value
  }

  if (irrecv2.decode(&results2)) {
    if(results2.value==KEY1){
      lastTick2 = actualTime;
      if(DEBUG_SERIAL){
        Serial.print("   2: ");
        Serial.println(results2.value, HEX);  //print code from receiver #2
      }
    }
    irrecv2.resume(); // Receive the next value
  }

  if (irrecv3.decode(&results3)) {

    if(results3.value==KEY1){
      lastTick3 = actualTime;
      if(DEBUG_SERIAL){
        Serial.print("   3: ");
        Serial.print(results3.value, HEX);   //print code from receiver #1
      }
    }
    irrecv3.resume(); // Receive the next value
  }

  if (irrecv4.decode(&results4)) {
    if(results4.value==KEY1){
      lastTick4 = actualTime;
      if(DEBUG_SERIAL){
        Serial.print("   4: ");
        Serial.print(results4.value, HEX);   //print code from receiver #1
      }
    }
    irrecv4.resume(); // Receive the next value
  }

  if(DEBUG_SERIAL){

   Serial.print("\nactual time is: ");
    Serial.print(actualTime);

    Serial.print("\nt1: ");
    Serial.print(lastTick1 );
    Serial.print("   t2: ");
    Serial.print(lastTick2 );
    Serial.print("   t3: ");
    Serial.print(lastTick3 );
    Serial.print("   t4: ");
    Serial.print(lastTick4 );

  }

  boardIsFocused = focusKeeper();

  digitalWrite(FOCUS_PIN,boardIsFocused);

  if(DEBUG_SERIAL){
    Serial.print("\nBoard is focused: ");
    Serial.print(boardIsFocused);
    Serial.print("\n");


    Serial.print("df1: ");
    Serial.print(detectorFocus1);
    Serial.print("   df2: ");
    Serial.print(detectorFocus2);
    Serial.print("   df3: ");
    Serial.print(detectorFocus3);
    Serial.print("   df4: ");
    Serial.print(detectorFocus4);
  }

  //digitalWrite(FOCUS_PIN,boardIsFocused);
  /*  digitalWrite(FPIN1,detectorFocus1);
  digitalWrite(FPIN2,detectorFocus2);
  digitalWrite(FPIN3,detectorFocus3);
  digitalWrite(FPIN4,detectorFocus4);
  */
}


int focusKeeper(){

  detectorFocus1 = timeNotExceed(lastTick1);
  detectorFocus2 = timeNotExceed(lastTick2);
  detectorFocus3 = timeNotExceed(lastTick3);
  detectorFocus4 = timeNotExceed(lastTick4);

  if(DEBUG_SERIAL){
    Serial.print("\nindividual receivers: ");
    Serial.print("d1: ");
    Serial.print(detectorFocus1);
    Serial.print("   d2: ");
    Serial.print(detectorFocus2);
    Serial.print("   d3: ");
    Serial.print(detectorFocus3);
    Serial.print("   d4: ");
    Serial.print(detectorFocus4);
  }

  if((detectorFocus1 + detectorFocus2 + detectorFocus3 + detectorFocus4) > detectorNumberLimit ){
    return 1;
  }else{
    return 0;
  }
}


int timeNotExceed(unsigned long t){
  if((t + globalTickInterval) > actualTime){
    return 1;
  }else{
    return 0;
  }
}


/*
int matchFrstKey(int actKey, int frstKey){
  if(actKey == frstKey){
    return 1;
  }else{
    return 0;
  }
}

int matchScndKey(int actKey, int scndKey){
  if(getScndNextKey(actKey) == scndKey){
    return 1;
  }else{
    return 0;
  }
}



int getPrevKey(int actKey){
  switch(actKey){
  case KEY1:
    return KEY3;
    break;
  case KEY2:
    return KEY1;
    break;
  case KEY3:
    return KEY2;
    break;
  }
}


int getFrstNextKey(int actKey){
  switch(actKey){
  case KEY1:
    return KEY2;
    break;
  case KEY2:
    return KEY3;
    break;
  case KEY3:
    return KEY1;
    break;
  }
}

int getScndNextKey(int actKey){
  switch(actKey){
  case KEY1:
    return KEY3;
    break;
  case KEY2:
    return KEY1;
    break;
  case KEY3:
    return KEY2;
    break;
  }
}

void pushTo(int val, int arr[]){
  arr[2] = arr[1];
  arr[1] = arr[0];
  arr[0] = val;
}

int matchPatt(int v1, int patt[]){
  int r = 0;
  int v2 = getPrevKey(v1);
  int v3 = getPrevKey(v2);
  if(v1==KEY1&&v2==KEY2&&v3==KEY3){
    r = 1;
  }
  if(v1==KEY2&&v2==KEY3&&v3==KEY1){
    r = 1;
  }
  if(v1==KEY3&&v2==KEY1&&v3==KEY2){
    r = 1;
  }
  return r;
}
*/
/*
void decodeAndMatch(IRrecv irr, decode_results dr, int patt[]){

  if (irr.decode(&dr)) {

    pushTo(dr.value,patt);

    if(matchFrstKey(dr.value,frstKey1) &&
       matchScndKey(results1.value,scndKey1)){

      lastTick1 = actualTime;

    }

    //frstKey1 = getFrstNextKey(results1.value);
    //scndKey1 = getFrstNextKey(frstKey1);

    Serial.print("\n1: ");
    Serial.print(results1.value, HEX);   //print code from receiver #1

    irrecv1.resume(); // Receive the next value
  }

  }*/

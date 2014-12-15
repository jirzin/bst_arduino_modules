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

const int detectorNumberLimit = 2;  // n+  of receiving detectors for board to be focused

int boardIsFocused = 0;

const int KEY1 = 0xffffbeda;

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

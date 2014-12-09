#include <IRremote.h>

////////////////////////////// IR REMOTE LIBRARY SETUP //////////////////////////////

// real board pins are 0, 3, 5, 6
int RECV_PIN1 = 8;           //receiver #1 data pin
int RECV_PIN2 = 9;           //receiver #2 data pin
int RECV_PIN3 = 10;           //receiver #3 data pin
int RECV_PIN4 = 11;           //receiver #4 data pin

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
int FOCUS_PIN = 4;

unsigned long actualTime = 0;

unsigned long globalTickInterval = 400;

unsigned long lastTick1 = 0;
unsigned long lastTick2 = 0;
unsigned long lastTick3 = 0;
unsigned long lastTick4 = 0;

int detectorFocus1 = 0;
int detectorFocus2 = 0;
int detectorFocus3 = 0;
int detectorFocus4 = 0;

int boardIsFocused = 0;

void setup()
{
  Serial.begin(9600);
  irrecv1.enableIRIn(); // Start the receiver #1
  irrecv2.enableIRIn(); // Start the receiver #2
  irrecv3.enableIRIn(); // Start the receiver #3
  irrecv4.enableIRIn(); // Start the receiver #4

  pinMode(FOCUS_PIN,OUTPUT);
  digitalWrite(FOCUS_PIN, LOW);
}

void loop() {

  actualTime = millis();

  if (irrecv1.decode(&results1)) {

    lastTick1 = actualTime;

    //    Serial.print("at ");
    //Serial.print(actualTime);
    Serial.print("\n1: ");
    Serial.print(results1.value, HEX);   //print code from receiver #1
    irrecv1.resume(); // Receive the next value
  }

  if (irrecv2.decode(&results2)) {

    lastTick2 = actualTime;

    Serial.print("   2: ");
    Serial.println(results2.value, HEX);  //print code from receiver #2
    irrecv2.resume(); // Receive the next value
  }

  if (irrecv3.decode(&results3)) {

    lastTick3 = actualTime;

    //digitalWrite(4,LOW);
    //delay(100);
    Serial.print("   3: ");
    Serial.print(results3.value, HEX);   //print code from receiver #1
    irrecv3.resume(); // Receive the next value

  }

  if (irrecv4.decode(&results4)) {

    lastTick4 = actualTime;
    Serial.print("   4: ");
    Serial.print(results4.value, HEX);   //print code from receiver #1
    //digitalWrite(4,LOW);
    irrecv4.resume(); // Receive the next value
  }

  //  digitalWrite(FOCUS_PIN, focusKeeper);

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


  boardIsFocused = focusKeeper();
  Serial.print("\nBoard is focused: ");
  Serial.print(boardIsFocused);
  digitalWrite(FOCUS_PIN,boardIsFocused);
  Serial.print("\n");
}


int focusKeeper(){

  detectorFocus1 = timeNotExceed(lastTick1);
  detectorFocus2 = timeNotExceed(lastTick2);
  detectorFocus3 = timeNotExceed(lastTick3);
  detectorFocus4 = timeNotExceed(lastTick4);

  Serial.print("\nindividual receivers: ");
  Serial.print("d1: ");
  Serial.print(detectorFocus1);
  Serial.print("   d2: ");
  Serial.print(detectorFocus2);
  Serial.print("   d3: ");
  Serial.print(detectorFocus3);
  Serial.print("   d4: ");
  Serial.print(detectorFocus4);

  if((detectorFocus1 + detectorFocus2 + detectorFocus3 + detectorFocus4) > 2 ){
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

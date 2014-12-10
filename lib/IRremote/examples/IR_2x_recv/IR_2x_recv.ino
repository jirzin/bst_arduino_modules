#include <IRremote.h>

int RECV_PIN1 = 11;           //receiver #1 data pin
int RECV_PIN2 = 12;           //receiver #2 data pin

IRrecv irrecv1(RECV_PIN1);    
decode_results results1;      //receiver #1 results
IRrecv irrecv2(RECV_PIN2);
decode_results results2;      //receiver #2 results

void setup()
{
  Serial.begin(9600);
  irrecv1.enableIRIn(); // Start the receiver #1
  irrecv2.enableIRIn(); // Start the receiver #2
}

void loop() {
  if (irrecv1.decode(&results1)) {
    Serial.print("1: ");
    Serial.println(results1.value, HEX);   //print code from receiver #1
    irrecv1.resume(); // Receive the next value
  }
  if (irrecv2.decode(&results2)) {
    Serial.print("2: ");
    Serial.println(results2.value, HEX);  //print code from receiver #2
    irrecv2.resume(); // Receive the next value
  }
}

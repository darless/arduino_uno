/* Raw IR decoder sketch!
This sketch/program uses the Arduno and a PNA4602 to
decode IR received. This can be used to make a IR receiver
(by looking for a particular code)
or transmitter (by pulsing an IR LED at ~38KHz for the
durations detected
Code is public domain, check out www.ladyada.net and adafruit.com
for more tutorials!
*/

// We need to use the 'raw' pin reading methods
// because timing is very important here and the digitalRead()
// procedure is slower!
//uint8_t IRpin = 2;
// http://arduino.cc/en/Hacking/PinMapping168 for the 'raw' pin mapping
//#define IRpin_PIN PINB
//#define IRpin 11
#define IRpin_PIN PIND
#define IRpin 2
// for MEGA use these!
//#define IRpin_PIN PINE
//#define IRpin 4
#define LED_OUT LED_BUILTIN

// the maximum pulse we'll listen for - 65 milliseconds is a long time
#define MAXPULSE 65000

// what our timing resolution should be, larger is better
// as its more 'precise' - but too large and you wont get
// accurate timing
#define RESOLUTION 20
#define PULSE_PAIRS 50

// we will store up to 100 pulse pairs (this is -a lot-)
uint16_t pulses[PULSE_PAIRS][2]; // pair is high and low pulse
uint8_t currentpulse = 0; // index for pulses we're storing

void setup(void) {
  Serial.begin(9600);
  Serial.println("Ready to decode IR!");
  pinMode(LED_OUT, OUTPUT);
}

void loop(void) {
  uint16_t highpulse, lowpulse; // temporary storage timing
  highpulse = lowpulse = 0; // start out with no pulse length


  while (IRpin_PIN & (1 << IRpin)) {
   // pin is still HIGH

   // count off another few microseconds
   highpulse++;
   delayMicroseconds(RESOLUTION);

   // If the pulse is too long, we 'timed out' - either nothing
   // was received or the code is finished, so print what
   // we've grabbed so far, and then reset
   if ((highpulse >= MAXPULSE) && (currentpulse != 0)) {
     printpulses();
     currentpulse=0;
     return;
   }
  }
  // we didn't time out so lets stash the reading
  pulses[currentpulse][0] = highpulse;

  // same as above
  while (! (IRpin_PIN & _BV(IRpin))) {
   // pin is still LOW
   lowpulse++;
   delayMicroseconds(RESOLUTION);
   if ((lowpulse >= MAXPULSE) && (currentpulse != 0)) {
     printpulses();
     currentpulse=0;
     return;
   }
  }
  pulses[currentpulse][1] = lowpulse;

  // we read one high-low pulse successfully, continue!
  currentpulse++;
}

void printpulses(void) {
  Serial.println("\n\r\n\rReceived: \n\rOFF \tON");
  /*
  for (uint8_t i = 1; i < currentpulse; i++) {
    Serial.print(pulses[i][0] * RESOLUTION, DEC);
    Serial.print(" usec, ");
    Serial.print(pulses[i][1] * RESOLUTION, DEC);
    Serial.println(" usec");
  }

  // print it in a 'array' format
  Serial.println("int IRsignal[] = {");
  Serial.println("// ON, OFF (in 10's of microseconds)");
  for (uint8_t i = 1; i < currentpulse-1; i++) {
    Serial.print("\t"); // tab
    Serial.print(pulses[i][1] * RESOLUTION / 10, DEC);
    Serial.print(", ");
    Serial.print(pulses[i+1][0] * RESOLUTION / 10, DEC);
    Serial.println(",");
  }
  Serial.print("\t"); // tab
  Serial.print(pulses[currentpulse-1][1] * RESOLUTION / 10, DEC);
  Serial.print(", 0};\n\r\n");
  */

  Serial.print("Showing pulses\n");
  uint32_t on_dur, off_dur;
  digitalWrite(LED_OUT, LOW);
  for (uint8_t ix = 1; ix < currentpulse; ix++) {
    on_dur = pulses[ix][1] * RESOLUTION * 1000;
    off_dur = pulses[ix][0] * RESOLUTION * 1000;
    Serial.print("ON: \n");
    Serial.print(on_dur);
    Serial.print("OFF: \n");
    Serial.print(off_dur);
    Serial.print("\r\n");

    digitalWrite(LED_OUT, HIGH);
    //delay(500);
    delayMicroseconds(on_dur);
    digitalWrite(LED_OUT, LOW);
    //delay(500);
    delayMicroseconds(off_dur);
  }
}

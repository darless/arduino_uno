#define BUZZER1 8
#define BUZZER2 9


void setup()
{
  Serial.begin(9600);
  Serial.println("Ready to make music!");
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
}

void do_sound_micro(uint16_t delay_micro)
{
  for(uint8_t ix = 0; ix < 100; ix++) {
    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, HIGH);
    delayMicroseconds(delay_micro);
    digitalWrite(BUZZER1, LOW);
    //delayMicroseconds(1);
    digitalWrite(BUZZER2, LOW);

    delayMicroseconds(delay_micro);
  }

}

void print_item(int item)
{
  Serial.print("Micro: ");
  Serial.print(item);
  Serial.print("\r\n");
}

void loop()
{
  int on = 100;
  int off = 200;
  for(int ix=on; ix < off;ix++) {
    print_item(ix);
    do_sound_micro(ix);
  }
  for(int ix=off; ix >= on;ix--) {
    print_item(ix);
    do_sound_micro(ix);
  }
}

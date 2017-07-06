#define LED_PIN 7
#define SENSOR_PIN A0
#define THRESHOLD 1000

int prev = LOW;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int val = analogRead(SENSOR_PIN);
  Serial.println(val);
  int over = val > THRESHOLD;
  if(prev == over) {
    return;
  }
  prev = over;
  if(over) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(5);
}

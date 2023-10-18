int led_pin = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
    
    
    digitalWrite(led_pin, HIGH);
    delay(1);
    digitalWrite(led_pin, LOW);
    delay(1);
}


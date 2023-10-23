int led_pin = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  timing();
  delay(10000);
    
}

void timing() {
  //send low for 150 microseconds, send whatever for 300 microseconds, and send high for 216 microseconds
  uint8_t array[9] = {0, 0, 1, 0, 0, 0, 0, 1, 0};
  array[9] = zeros(array);

  for(int i = 0; i < 9; i++)
  {
    digitalWrite(led_pin, 0);
    delayMicroseconds(150);
    digitalWrite(led_pin, array[i]);
    delayMicroseconds(300);
    digitalWrite(led_pin, 1);
    delayMicroseconds(200);
  }

}

int zeros(uint8_t array[]) {
  int parity = 0;
  int num = 0;
  int size = 9;//size_t size = sizeof(array) / sizeof(array[0]);
  for(int i = 0; i < size; i++)
  {
    if(array[i] == 0)
    {
      parity +=1;
    }
  }
  if(parity % 2 == 0)
  {
    num += 1;
  }
  return num;
}

void send() {

  digitalWrite(led_pin, HIGH);
  delay(1);
  digitalWrite(led_pin, LOW);
  delay(1);
}




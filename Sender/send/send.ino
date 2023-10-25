int led_pin = 3;
uint8_t mask[9] = { 0x01,
                    0x02,
                    0x04,
                    0x08,
                    0x10,
                    0x20,
                    0x40,
                    0x80} 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  String user_input;
  while(Serial.available() == 0){
  }
  user_input = Serial.readStringUntil('\n');
  Serial.flush();
  uint8_t temp;
  for(int i = 0; i < user_input.length(); i++)
  {
    temp = uint8_t((user_input[i]));
    //Serial.println(temp);

  }
  

  //timing(array);
  // delay(1000);
    
}

void timing(uint8_t array[]) {
  //send low for 150 microseconds, send whatever for 300 microseconds, and send high for 216 microseconds
  //uint8_t array[9] = {0, 0, 0, 0, 0, 0, 1, 0, 0};
  int parity = zeros(array);
  array[8] = parity;

  for(int i = 0; i < 9; i++)
  {
    digitalWrite(led_pin, 0);
    delayMicroseconds(150);
    digitalWrite(led_pin, array[i]);
    delayMicroseconds(300);
    digitalWrite(led_pin, 1);
    delayMicroseconds(200);
  }
  char ascii = binary2ascii(array);
  Serial.println(ascii);

}

int zeros(uint8_t array[]) {
  int parity = 0;
  int num = 0;
  int size = 9;//size_t size = sizeof(array) / sizeof(array[0]);
  for(int i = 0; i < size - 1; i++)
  {
    if(array[i] == 0)
    {
      parity +=1;
    }
  }
  if(parity % 2 == 0)
  {
    num = 1;
  }

  return num;
}

char binary2ascii(uint8_t array[])
{
  int arrayLength = sizeof(array) / sizeof(array[0]);
  char charArray[arrayLength + 1];
  for (int i = 0; i < arrayLength; i++) {
    charArray[i] = char(array[i]);
  }
  charArray[arrayLength] = '\0';
  Serial.println(charArray);

  return charArray;
}

void str2char(String inputString, char* data)
{
  int arrayLength = inputString.length() + 1; // +1 for the null terminator
  char outputCharArray[arrayLength];
  
  inputString.toCharArray(outputCharArray, arrayLength);
  for (int i = 0; i < arrayLength; i++)
  {
    data[i] = outputCharArray[i];
  }
  
}

void char2bin(char c)
{
   for (int i = 7; i >= 0; --i)
    {
        Serial.print( (c & (1 << i)) ? '1' : '0' );
    }
    Serial.println('\n');
  //int arrayLength = sizeof(input) / sizeof(input[0]);
  //int outputBinaryArray[arrayLength];
  //for (int i = 0; i < arrayLength; i++)
  //{
  //  outputBinaryArray[i] = int(input[i]);
  //}
  //return outputBinaryArray;
}

void send() {

  digitalWrite(led_pin, HIGH);
  delay(1);
  digitalWrite(led_pin, LOW);
  delay(1);
}




int led_pin = 2;
uint8_t mask[8] = {0x01,
                   0x02,
                   0x04,
                   0x08,
                   0x10,
                   0x20,
                   0x40,
                   0x80};
uint8_t testData[15] = {0b00000111,
                        0b00101010,
                        0b11001100,
                        0b00001101,
                        0b10101001,
                        0b01001010,
                        0b11100010,
                        0b00000111,
                        0b11111000,
                        0b01010100,
                        0b11001110,
                        0b00010100,
                        0b00000100,
                        0b11110110,
                        0b11101010};
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  uint8_t start_initial[9] = {0, 1, 1, 0, 1, 1, 1, 1, 0};
  timing(start_initial);
}

void loop()
{
  // put your main code here, to run repeatedly:
  String user_input;

  while (Serial.available() == 0)
  {
    delay(1000);

  }
  
  user_input = Serial.readString();
  Serial.println(user_input);
  Serial.flush();
  if (user_input == "test\n")
  {
    Serial.println("running test sequence");
    testRoutine();
  }
  else
  {
    uint8_t temp;
    for (int i = 0; i < user_input.length(); i++)
    {
      temp = uint8_t((user_input[i]));
      uint8_t idk[9];
      idk[8] = 0;
      byte2bit(temp, idk);
      for (int i = 7; i > -1; i--)
      {
        Serial.print(idk[i]);
      }
      Serial.println();
      Serial.print(char(temp));
      Serial.println();
      timing(idk);
      delay(70);
    }
  }
  
}

void testRoutine()
{
  for (int i = 0; i <= 15; i++)
  {
    timing(testData[i]);
    //Serial.println(testData[i]);
    Serial.print(char(testData[i]));
    delay(100);
    Serial.println(i);
  }
  timing(00001010);
}

void timing(uint8_t array[])
{
  // send low for 150 microseconds, send whatever for 300 microseconds, and send high for 216 microseconds
  // uint8_t array[9] = {0, 0, 0, 0, 0, 0, 1, 0, 0};
  int parity = zeros(array);
  array[8] = parity;

  for (int i = 0; i < 9; i++)
  {
    digitalWrite(led_pin, 0);
    delayMicroseconds(220);
    digitalWrite(led_pin, array[i]);
    delayMicroseconds(200);
    digitalWrite(led_pin, 1);
    delayMicroseconds(240);
  }
}

int zeros(uint8_t array[])
{
  int parity = 0;
  int num = 0;
  int size = 9; // size_t size = sizeof(array) / sizeof(array[0]);
  for (int i = 0; i < size - 1; i++)
  {
    if (array[i] == 0)
    {
      parity += 1;
    }
  }
  if (parity % 2 == 0)
  {
    num = 1;
  }

  return num;
}

void byte2bit(uint8_t temp, uint8_t (&array)[9])
{
  // uint8_t array[8];
  for (int i = 0; i < 8; i++)
  {
    if (temp & mask[i])
    {
      array[i] = 1;
    }
    else
    {
      array[i] = 0;
    }
  }
}

// void errorbit()

// char binary2ascii(uint8_t array[])
// {
//   int arrayLength = sizeof(array) / sizeof(array[0]);
//   char charArray[arrayLength + 1];
//   for (int i = 0; i < arrayLength; i++) {
//     charArray[i] = char(array[i]);
//   }
//   charArray[arrayLength] = '\0';
//   Serial.println(charArray);

//   return charArray;
// }

// void str2char(String inputString, char* data)
// {
//   int arrayLength = inputString.length() + 1; // +1 for the null terminator
//   char outputCharArray[arrayLength];

//   inputString.toCharArray(outputCharArray, arrayLength);
//   for (int i = 0; i < arrayLength; i++)
//   {
//     data[i] = outputCharArray[i];
//   }

// }

// void char2bin(char c)
// {
//    for (int i = 7; i >= 0; --i)
//     {
//         Serial.print( (c & (1 << i)) ? '1' : '0' );
//     }
//     Serial.println('\n');
//   //int arrayLength = sizeof(input) / sizeof(input[0]);
//   //int outputBinaryArray[arrayLength];
//   //for (int i = 0; i < arrayLength; i++)
//   //{
//   //  outputBinaryArray[i] = int(input[i]);
//   //}
//   //return outputBinaryArray;
// }

// void send() {

//   digitalWrite(led_pin, HIGH);
//   delay(1);
//   digitalWrite(led_pin, LOW);
//   delay(1);
// }

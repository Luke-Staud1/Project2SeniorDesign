int recivePin = 2;
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
}

void loop()
{

    if (digitalRead(recivePin) == 0)
    {
        Serial.println(readBit());
    }
}

bool readBit()
{
    delayMicroseconds(225);
    bool bit = digitalRead(recivePin);
    delayMicroseconds(275);
    return bit;
}

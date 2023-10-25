const int RECIVE_PIN = 6;
const int MESSAGE_SIZE = 9;
const int MESSAGE_TIMEOUT = 1000; // timeout in miliseconds
bool *fifo = new bool[MESSAGE_SIZE];
int bitTracker = 0;
int timeoutTracker = 0;
long int milisLastUpdate = 0;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    milisLastUpdate = millis();
}

void loop()
{

    if (digitalRead(RECIVE_PIN) == 0)
    {
        readBit();
        bitTracker++;
        milisLastUpdate = millis();
    }
    if (bitTracker == MESSAGE_SIZE)
    {
        bitTracker = 0;
        if (verifyByte(fifo))
        {
            convetToAscii();
            fifoFlush();
        }
        else
        {
            fifoFlush();
            Serial.println("Error in transmission detected");
        }
    }
    if (millis() - milisLastUpdate > MESSAGE_TIMEOUT)
    {
        fifoFlush();
        Serial.print("Timeout reached no update in(ms): ");
        Serial.println(millis() - milisLastUpdate);
        milisLastUpdate = millis();
    }
}

void fifoPush(bool bit)
{
    for (int i = 0; i < MESSAGE_SIZE - 1; i++)
    {
        fifo[i] = fifo[i + 1];
    }
    fifo[8] = bit;
}

void fifoFlush()
{
    for (int i = 0; i < MESSAGE_SIZE; i++)
    {
        fifo[i] = 0;
    }
}

void convetToAscii()
{
    int ascii = 0; // i dont know why this has to be a one but it makes everything work
    bool *dataSegment = new bool[MESSAGE_SIZE - 1];
    for (int i = 0; i < MESSAGE_SIZE - 1; i++)
    {
        dataSegment[i] = fifo[i];
    }
    printBinary(dataSegment, MESSAGE_SIZE - 1);
    for (int i = 0; i < MESSAGE_SIZE - 1; i++)
    {
        if (dataSegment[i])
        {
            ascii += pow(2, (MESSAGE_SIZE - 1 - i));
            Serial.println(MESSAGE_SIZE - 1 - i);
        }
    }
    Serial.println(ascii);
}

void printBinary(bool bitArray[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (bitArray[i])
        {
            Serial.print("1");
        }
        else
        {
            Serial.print("0");
        }
    }
    Serial.println();
}
bool *reverseArray(bool byteArray[])
{
    bool *reversedArray = new bool[MESSAGE_SIZE];
    for (int i = 0; i < MESSAGE_SIZE; i++)
    {
        reversedArray[i] = byteArray[MESSAGE_SIZE - i];
    }
    return reversedArray;
}

bool verifyByte(bool byteMessage[])
{
    int parity = 0;
    for (int i = 0; i < MESSAGE_SIZE; i++)
    {
        if (byteMessage[i] == 0)
        {
            parity += 1;
        }
    }
    if (parity % 2 == 0)
    {
        return true;
    }
    return false;
}

bool readBit()
{
    delayMicroseconds(225);
    fifoPush(digitalRead(RECIVE_PIN));
    delayMicroseconds(275); // we can lower this time to account for how long fifo push will take to run
}

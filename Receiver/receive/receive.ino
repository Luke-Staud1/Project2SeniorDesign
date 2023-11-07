const int RECIVE_PIN = 6;
const int MESSAGE_SIZE = 9;
const int MESSAGE_TIMEOUT = 1000; // timeout in miliseconds
bool *fifo = new bool[MESSAGE_SIZE];
int bytesRecived = 0;
int errorsFound = 0;
char match = 0x07;
char key = 0x00;
int bitTracker = 0;
bool timeoutHit = false;
long int milisLastUpdate = 0;
long int frequencyTime = 0;
long long int averageFreqTime = 0;
int threshHold = 100;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    milisLastUpdate = millis();
    Serial.println("seting up things");
}

void loop()
{

    if (!(digitalRead(RECIVE_PIN)))
    {
        frequencyTime = micros();
        readBit();
        timeoutHit = false;
        bitTracker++;
        milisLastUpdate = millis();
        averageFreqTime = averageFreqTime + (micros() - frequencyTime);
        
    }
    if (bitTracker == MESSAGE_SIZE)
    {
        bytesRecived++;
        bitTracker = 0;
//        printBinary(fifo, 9);
        if (verifyByte(fifo))
        {
            key = convetToAscii();
            delay(10);
            fifoFlush();
        }
        else
        {
            errorsFound++;
            fifoFlush();
            Serial.println("Error in transmission detected");
        }
        if(key == match)
        {
          Serial.println("test detected");
        }
    }
    if (millis() - milisLastUpdate > MESSAGE_TIMEOUT)
    {
        fifoFlush();
        if (!timeoutHit)
        {
            timeoutHit = true;
            double errorRate = float(errorsFound * 8)/float(bytesRecived * 9);
            double averageTime =  (float(averageFreqTime)/float(bytesRecived * 8))/1000;
            
            float frequency = 1000/averageTime;
            Serial.print("frequency(Hz) of tranmission: ");
            Serial.println(frequency);            
            Serial.print("error rate of last segment (percent): ");
            Serial.println(errorRate);
            Serial.print("Timeout reached no update in(ms): ");
            Serial.println(millis() - milisLastUpdate);
            milisLastUpdate = 0;
            averageFreqTime = 0;
            errorsFound = 0;
            bytesRecived = 0;
            milisLastUpdate = millis();
        }
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

char convetToAscii()
{
    char ascii = 0; // i dont know why this has to be a one but it makes everything work
    bool *dataSegment = new bool[MESSAGE_SIZE - 1];
    // bool *flipedData = new bool[MESSAGE_SIZE - 1];
    for (int i = 0; i < MESSAGE_SIZE - 1; i++)
    {
        dataSegment[i] = fifo[i];
    }

    for (int i = 0; i < MESSAGE_SIZE - 1; i++)
    {
        if (dataSegment[i])
        {
            ascii |= 1 << i;
        }
    }

    Serial.print(ascii);
    return(ascii);
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
    delayMicroseconds(220);
    fifoPush(digitalRead(RECIVE_PIN));
    delayMicroseconds(300); // we can lower this time to account for how long fifo push will take to run
}

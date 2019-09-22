String fromNetwork;
int gadgetPin = 13;

//DHT11
unsigned int iRelativeHumidity, dRelativeHumidity, dataSum;
unsigned int dTemperature, iTemperature, checkSum;
const int DHTPIN = 8;

void setup() 
{
  pinMode(gadgetPin, OUTPUT);                   // Setting gadget pin (13) as an output.   
  Serial.begin(115200);// Initializing MCU's serial port speed to talk with Wi-Fi module.
  Serial.println("AT+CWMODE=2\r\n");            // Making Wi-Fi module as acceSerial point.
  delay(2000);                                  // Wait for 2 seconds.
  Serial.println("AT+CIPMUX=1\r\n");            // Making Wi-Fi module as multiplexer.
  delay(2000);                                  // Wait for 2 seconds.
  Serial.println("AT+CIPSERVER=1,1883\r\n");    // Making Wi-Fi module as TCP server on IP: 192.168.4.1, PORT: 1883
}

void requestToSensor()
{
  pinMode(DHTPIN, OUTPUT);
  digitalWrite(DHTPIN, LOW);
  delay(18);
  digitalWrite(DHTPIN, HIGH);
}

void responseFromSensor()
{
  pinMode(DHTPIN, INPUT);
  while(digitalRead(DHTPIN) == 1);
  while(digitalRead(DHTPIN) == 0);
  while(digitalRead(DHTPIN) == 1);
}

unsigned int getDataFromSensor()
{
  unsigned int rxdByte = 0;
  for (int k = 0; k < 8; k++)
  {
    while(digitalRead(DHTPIN) == 0);
    delayMicroseconds(28);
    if (digitalRead(DHTPIN) == 1)
      rxdByte = (rxdByte << 1) | (0x01);
    else
      rxdByte = (rxdByte << 1);
    while(digitalRead(DHTPIN) == 1);  
  }
  return rxdByte;
}

void loop()
{
  requestToSensor();
  responseFromSensor();
  iRelativeHumidity = getDataFromSensor();
  dRelativeHumidity = getDataFromSensor();
  iTemperature = getDataFromSensor();
  dTemperature = getDataFromSensor();
  checkSum = getDataFromSensor();
  dataSum = iRelativeHumidity + dRelativeHumidity + iTemperature + dTemperature;
  if (dataSum == checkSum)
  {
    Serial.println("AT+CIPSEND=0,4\r\n");
    delay(500);
    Serial.print(String(iRelativeHumidity));
    Serial.print(String(iTemperature));
  }
  delay(100);
}

void serialEvent()
{
 while (Serial.available() > 0)             // Waiting for incoming of any string from client over Wi-Fi network.
  {
    fromNetwork = Serial.readString();
    if(fromNetwork.indexOf("TURN ON") > -1)
      digitalWrite(gadgetPin, HIGH);
    else if(fromNetwork.indexOf("TURN OFF") > -1)
      digitalWrite(gadgetPin, LOW);
  } 
}

#include <Adafruit_BMP280.h>//Barometer

int led = 8;
char val;
Adafruit_BMP280 bmp; // I2C

void setup()
{
 
pinMode(led, OUTPUT);  // Digital pin 13 set as output Pin
Serial.begin(9600);
//barometer
  if (!bmp.begin()) { 
    while (1);
  } 
}

void loop()
{
  while (Serial.available() > 0)
  {
  val = Serial.read();
  }

  if( val == '1') // Forward
    {
      digitalWrite(led, HIGH);
    }
  else if(val == '2') // Backward
    {
 
      digitalWrite(led, LOW);
    }
  String temperature = String(bmp.readTemperature());
  Serial.print(temperature.substring(0,2));
  delay(2000);
    }

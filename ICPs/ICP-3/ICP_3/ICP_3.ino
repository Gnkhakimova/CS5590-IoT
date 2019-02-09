//Including libraries
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal_PCF8574.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>
#include <SoftwareSerial.h>


//Constants
SoftwareSerial esp8266(9,10);
Adafruit_BMP280 bmp; // I2C
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
LiquidCrystal_PCF8574 lcd(0x27);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Setted wifi name and passwrod also included write API key for ThinkSpeak and defining fields

String AP = "Supu";       // CHANGE ME
String PASS = "12345678"; // CHANGE ME
String API = "O5R2BXR7OMESYUM9";   // CHANGE ME
String HOST = "184.106.153.149";
String PORT = "80";
String Temp = "field1";
String Hum = "field2";
String BTemp = "field3";
String BPres = "field4";
String BAlt = "field5";
String Light = "field6";
String Dust = "field7";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 
int valSensor = 1;

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
int light;
int pin = 8;
unsigned long duration;
unsigned long starttime;
unsigned long sampletime_ms = 2000; 
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

void setup()
{
  Serial.begin(9600);
  //Begin temperature sensor
  dht.begin();

  // When device is connected for the first time Dislpaying not gets displayed and begin LCD
  lcd.setBacklight(255);
  lcd.begin(16, 2);
  lcd.print("circuitdigest.com");
  delay(100);
  lcd.setCursor(0,1);
  lcd.print("Connecting...");
  
  //Begin wifi and connect to Thingspeak
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");

 //Begin Baroremeter sensor
  if (!bmp.begin()) {  
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
 //Set Input for Light sesnor
  pinMode(A0,INPUT);
  
 // Set input for dust sentor
   pinMode(8,INPUT);
   starttime = millis(); 
  
  }

//Method to send values from sensor to ThingSpeak
  void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
   }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }

void loop()
{
    //Temperature Sensor
    //Displaying values from Temperature sensor
    lcd.clear();
    delay(2000);
    //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    //Display values on LCD
    lcd.setCursor(0,0);
    lcd.print("Temp & Humidity");
    lcd.setCursor(0,1);
    lcd.print("Sensor");
    delay(2000); //Delay 2 sec.
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Humidity: ");
    lcd.print(hum);
    lcd.print(" %");   
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print( (char)223);
    lcd.print("C");
    delay(5000); //Delay 2 sec.
    lcd.clear();

    //Barometer sensor
    //Display values from barometer sensor on Serial Monitor
    Serial.print("Barometer sensor");
    lcd.print("Barometer sensor");
    delay(2000);
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    //Display values on LCD
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Temp:");
    lcd.print(bmp.readTemperature());
    lcd.print(" *C");
    delay(2000);
    lcd.clear();
    //Display values for pressure on serial monitor
    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");   
    //Display Values for pressure on LCD 
    lcd.print("Pres: "); 
    lcd.print(bmp.readPressure());
    lcd.setCursor(0,1);
    lcd.print(" Pa");
    delay(2000);
    lcd.clear();
    //Display values for altitude on Serial monitor
    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); // this should be adjusted to your local forcase
    Serial.println(" m");
    //Display values for altitude on LCD
    lcd.setCursor(0,0);
    lcd.print("Alt: ");
    lcd.print(bmp.readAltitude(1013.25));
    lcd.print(" m");
    Serial.println();
    delay(2000);

   //Light sensor
   //Read data from Light sensor and display it on Serial monitor
   light=analogRead(A0);
   Serial.println("Light = " + String(light));
   //Display values from Light sensor on LCD
   lcd.clear();
   lcd.print("Light sensor");
   lcd.clear();
   lcd.print("Light: ");
   lcd.print(String(light));
   delay(5000);

  //Dust sensor
  //Read data from dust sensor
  duration = pulseIn(pin, LOW);
  lowpulseoccupancy = lowpulseoccupancy+duration;
  if ((millis()-starttime) >= sampletime_ms) //if the sampel time = = 30s
  {
    ratio = lowpulseoccupancy/(sampletime_ms*10.0);  
    concentration = 1.1*pow(ratio,3)-3.8*pow(ratio,2)+520*ratio+0.62; 
    //Print values in Serial monitor
    Serial.print("Concentration = ");
    Serial.print(concentration);
    Serial.println(" pcs/0.01cf");
    Serial.println("\n");
    lowpulseoccupancy = 0;
    starttime = millis();
    //Display values on LCD
    lcd.clear();
    lcd.print("Dust sensor");
    lcd.clear();
    lcd.print("Dust: ");
    lcd.print(concentration);
    lcd.print(" pcs/0.01cf");

   String getData1 = "GET /update?api_key="+ API +"&"+ Light +"="+String(light)+"&"+ Dust +"="+String(concentration);
   sendCommand("AT+CIPMUX=1",5,"OK");
   sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
   sendCommand("AT+CIPSEND=0," +String(getData1.length()+4),4,">");
   esp8266.println(getData1);
   countTrueCommand++;
   sendCommand("AT+CIPCLOSE=0",5,"OK");
  }  

  delay(3000);
  
  //Make a Get request to display data in Thinkspeak by passing values and field names.
  String getData = "GET /update?api_key="+ API +"&"+ Temp +"="+String(temp) +"&"+ Hum +"="+String(hum)+"&"+ BTemp +"="+String(bmp.readTemperature())+"&"+ BPres +"="+String(bmp.readPressure())+"&"+ BAlt +"="+String(bmp.readAltitude(1013.25));
  sendCommand("AT+CIPMUX=1",5,"OK");
  sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
  sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
  esp8266.println(getData);
  delay(3500);
//  String getData1 = "GET /update?api_key="+ API +"&"+ Light +"="+String(light)+"&"+ Dust +"="+String(concentration);
//  sendCommand("AT+CIPMUX=1",5,"OK");
//  sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
//  sendCommand("AT+CIPSEND=0," +String(getData1.length()+4),4,">");
//  esp8266.println(getData1);
//  countTrueCommand++;
//  sendCommand("AT+CIPCLOSE=0",5,"OK");
}


   

int white = 13;
int green = 12;

void setup()
{
pinMode(white, OUTPUT);
pinMode(green, OUTPUT);
Serial.begin(9600);

}
void loop()
{

Serial.print(analogRead(A3)); // Read Pulse sensor value
Serial.print("\n");
delay(2000);

if(analogRead(A3) > 600){
  digitalWrite(white, HIGH);
  digitalWrite(green, LOW);                                                                                                                                                                                                                                                     delay(2000);
}
else{
  digitalWrite(green, HIGH);
  digitalWrite(white, LOW);
}
}

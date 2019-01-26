int switchState = 0;
void setup() {
  //Initial set up
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
}

void loop(){
  //Reading the initial state of the button.
  switchState = digitalRead(2);
  
  if(switchState == LOW){
  // the button is not pressed Green is always ON, Red and White off

  digitalWrite(3, HIGH); //green LED
  digitalWrite(4, LOW); //Red LED
  digitalWrite(5, LOW); //White LED
  }
//button pressed Green ON, Red and White Blink
  else{
    //define loop for blinks
   while(1){
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
  
    delay(250); // wait for a quarter seconds
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(250);
  }

  }


}

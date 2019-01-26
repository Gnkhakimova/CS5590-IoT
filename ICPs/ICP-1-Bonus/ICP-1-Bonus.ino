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
  //if button state is off then we are keep LEDs off
  if(switchState == LOW){
  // the button is not pressed
  digitalWrite(3, LOW); //green LED
  digitalWrite(4, LOW); //Red LED
  digitalWrite(5, LOW); //white LED
  }
  //if the button is on then we start switch on the LED one by one.
  else{
   //Always true (continues loop)
   while(1){
      //3- GREEN
      //4- RED
      //5- White
      
      //GREEN ON, RED and WHITE OFF
      digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
  
      delay(250); // wait for a quarter seconds
      //RED ON, GREEN and WHITE OFF
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      delay(250);// wait for a quarter seconds
      
      //WHITE ON, GREEN and WHITE OFF
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      delay(250);// wait for a quarter seconds
    }
  }


}

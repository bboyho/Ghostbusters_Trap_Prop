#include <Servo.h>          //include the servo library

//"Left" Servo
int servo1Position;         //the servo will move to this position
Servo myservo1;              //create a servo object

//"Right" Servo
int servo2Position;         //the servo will move to this position
Servo myservo2;              //create a servo object

boolean doorOpen = false;   //keep track of servo position state

//Button
const int buttonPin = 2;       //reset button
const int buttonLEDPin = 13;    //green LED
int buttonState = HIGH; //set button HIGH, so not pressing
//keep track if button press when held down
boolean prev_buttonState = false;
boolean current_buttonState = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  myservo1.attach(5);        //tell the servo object that its servo is plugged into pin 5
  myservo2.attach(6);        //tell the servo object that its servo is plugged into pin 6

  Serial.println("Servo objects initialized. Armed!");

  pinMode(buttonPin, INPUT_PULLUP); //use internal pullup resistor w/ reset button
  pinMode(buttonLEDPin, OUTPUT);//big dome pushbutton LED
  digitalWrite(buttonLEDPin, HIGH);//turn LED ON

  //Make sure the Servos are closed
  closeTrap();
  delay(1000);



}//end setup()

void loop() {
  //Note: its best to avoid driving the little SIK servos all the
  //way to 0 or 180 degrees it can cause the motor to jitter, which is bad for the servo.

  //1.) Button pressed, quickly Servo positions to "open position"
  //2.) Light LEDs
  //3.) Button pressed, close servo closed Servo position

  buttonState = digitalRead(buttonPin);//check state of reset button
  //if button pressed, open servos
  if (buttonState == LOW) {
    current_buttonState = true; //button has been pressed

    if (prev_buttonState != current_buttonState) {
      digitalWrite(buttonLEDPin, LOW);//turn LED OFF

      if (doorOpen == false) {
        openTrap();
      }
      else { //doorOpen == true
        closeTrap();
      }

    }
    prev_buttonState = current_buttonState;//update button's state

  }

  else if (buttonState == HIGH) {
    current_buttonState = false;//button has not been pressed
    if (prev_buttonState != current_buttonState) {
      digitalWrite(buttonLEDPin, HIGH);//turn LED back on
      Serial.println("turn led back on");
    }
    prev_buttonState = current_buttonState;//update Reset button's state
  }


}//end loop



void openTrap() {
  servo1Position = 25;
  myservo1.write(servo1Position);

  servo2Position = 125;
  myservo2.write(servo2Position);

  doorOpen = true;
  Serial.println("Servo's open!");

}



void closeTrap() {
  servo1Position = 125;
  myservo1.write(servo1Position);

  servo2Position = 25;
  myservo2.write(servo2Position);
  doorOpen = false;

  Serial.println("Servo's closed!");

}

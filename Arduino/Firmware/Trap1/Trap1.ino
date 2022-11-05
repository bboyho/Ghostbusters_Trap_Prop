#include <Servo.h>          //include the servo library

//"Left" Servo
int servo1Position;         //the servo will move to this position
Servo myservo1;              //create a servo object

//"Right" Servo
int servo2Position;         //the servo will move to this position
Servo myservo2;              //create a servo object


void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  myservo1.attach(5);        //tell the servo object that its servo is plugged into pin 5
  myservo2.attach(6);        //tell the servo object that its servo is plugged into pin 6

  Serial.println("Servo objects initialized. Armed!");

  servo1Position = 125;
  myservo1.write(servo1Position);

  servo2Position = 25;
  myservo2.write(servo2Position);

  Serial.println("Servo's closed!");
  delay(1000);




  servo1Position = 25;
  myservo1.write(servo1Position);

  servo2Position = 125;
  myservo2.write(servo2Position);


  Serial.println("Servo's open!");
  delay(3000);



  servo1Position = 125;
  myservo1.write(servo1Position);

  servo2Position = 25;
  myservo2.write(servo2Position);

  Serial.println("Servo's closed!");
  delay(3000);

}

void loop() {
  //Note: its best to avoid driving the little SIK servos all the
  //way to 0 or 180 degrees it can cause the motor to jitter, which is bad for the servo.

  //1.) Quickly Servo positions to "open position"
  //2.) Slowly sweep Servoss to "close position"
  //3.) Closed Servo position





}

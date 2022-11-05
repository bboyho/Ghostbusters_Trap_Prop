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

//Addressable LEDs
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN       8 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 7 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel strip(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 250 // Time (in milliseconds) to pause between pixels



void setup() {
  Serial.begin(115200);
  Serial.println("Initializing...");

  myservo1.attach(5);        //tell the servo object that its servo is plugged into pin 5
  myservo2.attach(6);        //tell the servo object that its servo is plugged into pin 6

  Serial.println("Servo objects initialized. Armed!");

  //Make sure the Servos are closed
  closeTrap();
  delay(1000);

  //Initialize button and LED
  pinMode(buttonPin, INPUT_PULLUP); //use internal pullup resistor w/ reset button
  pinMode(buttonLEDPin, OUTPUT);//big dome pushbutton LED
  digitalWrite(buttonLEDPin, HIGH);//turn LED ON


  //initialize Addressabl LEDs
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.clear(); // Set all pixel colors to 'off'
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)




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




  if (doorOpen == true) {
    Serial.println("Turn LEDs ON");

    // The first NeoPixel in a strand is #0, second is 1, all the way up
    // to the count of pixels minus one.
    for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      strip.setPixelColor(i, strip.Color(0, 150, 0));

      strip.show();   // Send the updated pixel colors to the hardware.


    }
    strip.show();   // Send the updated pixel colors to the hardware.
    //delay(DELAYVAL); // Pause before next pass through loop
  }
  else {
    Serial.println("Turn LEDs OFF");
    strip.clear();
    strip.show();
    //delay(DELAYVAL); // Pause before next pass through loop

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

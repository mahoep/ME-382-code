
 /*
 * RC Control
 * Control for Tri-Athalon Robot
 * Used in conjunction with FS-i6 wireless RC controller
 * ME 382 - OREGON STATE
 * Motor library courtesy of
 * https://github.com/goodmajo/
 */

#include <MotorDrv.h> // Sweet custom class
#include <Servo.h>

#define ch2_INPUT 2 // right stick y axis
#define ch3_INPUT 3 // left stick y axis
#define ch5_INPUT 5 // channel 5 pin number
#define ch6_INPUT 6  //channel 6 pin number

// Define floor and ceiling values for the transmitter here. MUST DETERMINE THESE ON YOUR OWN! They vary from transmitter to transmitter. These values also might change depending on the reciever. Always check these values after purchasing new a new transmitter or receiver.
#define transMin 950
#define transMax 1890
#define range 927

#define channel_5 5    //channel 5 pin number
#define channel_6 6    //channel 6 pin number

// right motor driver
#define m1pwmr 22   // Right Side PWM pin number
#define m1pwml 24   // Left PWM pin number
#define m1enr  26 // Right side enable pin number
#define m1enl  28 // Left side enable pin number


// Left motor driver
#define m2pwmr 23   // Right Side PWM
#define m2pwml 25   // Left PWM
#define m2enr  27 // Right side enable
#define m2enl  29   // Left side enable

#define fan 51      // fan control pin number
#define compressor 50 // air compressor pin number




// xmchn = "transmitter channel n". This is where I'll store transmitter channel values, which will then be changed into usable control values.
int rightStick;     // right stick
int leftStick;      //left stick
int ch5mode;
int ch6mode;
int barrelState;   
int triggerState;

MotorDrv robot ; // define class 
Servo barrel;   // define servo class name
Servo trigger;

void setup() {
  Serial.begin(57600);
  
  // Reciever inputs go here.
  pinMode(ch2_INPUT, INPUT);
  pinMode(ch3_INPUT, INPUT);
  pinMode(ch5_INPUT, INPUT);
  pinMode(ch6_INPUT, INPUT);

  // right motor
  pinMode(m1pwmr, OUTPUT) ;
  pinMode(m1pwml, OUTPUT) ;
  pinMode(m1enl, OUTPUT) ;
  pinMode(m1enr, OUTPUT) ;
  // left motor
  pinMode(m2pwmr, OUTPUT) ;
  pinMode(m2pwml, OUTPUT) ;
  pinMode(m2enl, OUTPUT) ;
  pinMode(m2enr, OUTPUT) ;

  //BarrelServo
  barrel.attach(40);
 
  // Trigger servo
  trigger.attach(41);
 
  // Fan
  pinMode(fan, OUTPUT);
 
  // compressor
  pinMode(compressor, OUTPUT);
  Serial.print("Setup is complete! \n");
}

void DriveServos()
{
  if (triggerState == 1) {
    trigger.write(90);
  }
  else {
    trigger.write(5);
  }
    
  if (barrelState == 1) {
    trigger.write(90);
  }
  else {
    barrel.write(5);
  }
}
void loop() {
 
  rightStick = pulseIn(ch2_INPUT, HIGH, 100000);
  leftStick = pulseIn(ch3_INPUT, HIGH, 100000);
  ch5mode = pulseIn(channel_5, HIGH, 100000) ;
  ch6mode = pulseIn(channel_6, HIGH, 100000);

  if ((ch5mode >1700)) // Switch C in backwards position
  {
  digitalWrite(compressor, LOW); // compressor off
  triggerState = 1;           // firing servo in fire state
  }
  else if ((ch5mode > 1200) && (ch5mode < 1600)) // Switch C in middle position
  {
  digitalWrite(compressor, HIGH);  // copmressor on
  triggerState = 0;             // firing servo in rest state
  }
  else // Siwtch C forward most position
  {
  digitalWrite(compressor, LOW);  //compressor off
  triggerState = 0;             // firing servo in rest state
  }

  if ((ch6mode < 1200)) ///Switch A in forward state
  {
    digitalWrite(fan, LOW);  //fan off
    barrelState = 1;      // barrel in firing state
  }
  else  /// Switch A in backward state
   {
   digitalWrite(fan, HIGH); // fan on
    barrelState = 0;        // barrel in pick up state
  }

  // Usage: MotorDrv.IBT( <left transmitter channel>, <right transmitter channel>, <motor 1 Lpwm>, <motor 1 Rpwm>, <motor 1 L enable >, <motor 1 R enable>, <motor 2 Lpwm>, <motor 2 Rpwm>, motor 2 L enable >, <motor 2 R enable>, <% of max possible motor strength>)
  robot.IBT2(transMin, transMax, leftStick, rightStick, m1pwml, m1pwmr, m1enl, m1enr, m2pwml, m2pwmr, m2enl, m2enr, 100);

  
  Serial.print(ch5mode);
  Serial.print("\n");
  
}


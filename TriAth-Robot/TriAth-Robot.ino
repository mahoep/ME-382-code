
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
#define ch5_INPUT 4 // channel 5 pin number
#define ch6_INPUT 5  //channel 6 pin number

// Define floor and ceiling values for the transmitter here. MUST DETERMINE THESE ON YOUR OWN! They vary from transmitter to transmitter. These values also might change depending on the reciever. Always check these values after purchasing new a new transmitter or receiver.
#define transMin 950
#define transMax 1890
#define range 927

// right motor driver
#define m1pwmr 9  // Right Side PWM pin number
#define m1pwml 8   // Left PWM pin number
#define m1enr  27 // Right side enable pin number
#define m1enl  29 // Left side enable pin number


// Left motor driver
#define m2pwmr 7   // Right Side PWM
#define m2pwml 6   // Left PWM
#define m2enr  40 // Right side enable
#define m2enl  42   // Left side enable

#define fan 51      // fan control pin number
#define compressor 50 // air compressor pin number


// xmchn = "transmitter channel n". This is where I'll store transmitter channel values, which will then be changed into usable control values.
int rightStick;     // right stick
int leftStick;      //left stick
int ch5mode;        // channel 5 operating state
int ch6mode;        // channel 6 operating state
int barrelState;   
int triggerState;

MotorDrv robot ; // define function name from MotorDrv library
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
  barrel.attach(13);
 
 
  // Trigger servo
  trigger.attach(12);
 
  // Fan
  pinMode(fan, OUTPUT);
 
  // compressor
  pinMode(compressor, OUTPUT);
  Serial.print("Setup is complete! \n");
}

void DriveServos()
// this used to have conditionals with the barrel state and trigger state but was deemed unnecessary
void loop() {
 
  rightStick = pulseIn(ch2_INPUT, HIGH, 100000); // converts radio transmittion to readable PWM
  leftStick = pulseIn(ch3_INPUT, HIGH, 100000);
  ch5mode = pulseIn(ch5_INPUT, HIGH, 100000) ;
  ch6mode = pulseIn(ch6_INPUT, HIGH, 100000);
  // This is a small deadzone so the motors won't drive
  if (rightStick > 1400 && rightStick < 1550){
    rightStick = 1420;
    }
  else{
    rightStick = rightStick;
    }
  
   if (leftStick > 1400 && leftStick < 1550){
    leftStick = 1420;
    }
  else {
    leftStick = leftStick;
    }
// this stuff controls air compressor operation and firing 
  if ((ch5mode >1700)) { // Switch C in backwards position
  
    digitalWrite(compressor, HIGH); // compressor off
    trigger.write(110);  // firing servo in fire state
  }
 
  else if ((ch5mode > 1200) && (ch5mode < 1600)) // Switch C in middle position
    {
    trigger.write(10);     // firing servo in rest state
    digitalWrite(compressor, LOW);
    }
    
 
  else { // Siwtch C forward most position
    digitalWrite(compressor, HIGH);  //compressor off
    trigger.write(10);             // firing servo in rest state
    }
    
// this stuff controls the fan and barrel position
  if ((ch6mode < 1500)){ ///Switch A in forward state
    digitalWrite(fan, LOW);  //fan on
    barrel.write(53);     // barrel in pick up state
    }
  else {  /// Switch A in backward state
   
   digitalWrite(fan, HIGH); // fan off
    barrel.write(110);  // barrel in firing state
    }

  // Usage: MotorDrv.IBT( <left transmitter channel>, <right transmitter channel>, <motor 1 Lpwm>, <motor 1 Rpwm>, <motor 1 L enable >, <motor 1 R enable>, <motor 2 Lpwm>, <motor 2 Rpwm>, motor 2 L enable >, <motor 2 R enable>, <% of max possible motor strength>)
  robot.IBT2(transMax, transMin, leftStick, rightStick, m1pwml, m1pwmr, m1enl, m1enr, m2pwml, m2pwmr, m2enl, m2enr, 100);

  
  Serial.print(rightStick);
  Serial.print("\n");
  //
  Serial.print(leftStick);
  Serial.print("\n");
  
  
}




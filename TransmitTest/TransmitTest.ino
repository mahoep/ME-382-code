
#define ch2_INPUT 2 // right stick y axis
#define ch3_INPUT 3 //left stick y axis

// Define floor and ceiling values for the transmitter here. MUST DETERMINE THESE ON YOUR OWN! They vary from transmitter to transmitter. These values also might change depending on the reciever. Always check these values after purchasing new a new transmitter or receiver.
#define transMin 950
#define transMax 1890
#define range 927


#define channel_5 5 // auxillary channel to control air compressor and firing
#define channel_6 6 // auxillary channel to control fan and barrel position

// Initializing variables at the top like a good programmer
// xmchn = "transmitter channel n". This is where I'll store transmitter channel values, which will then be changed into usable control values.
int rightStick;     // right stick
int leftStick;      //left stick
int ch5mode;        
int ch6mode;


void setup() {
 
  // Reciever inputs go here.
  pinMode(ch2_INPUT, INPUT);
  pinMode(ch3_INPUT, INPUT);
  pinMode(channel_5, INPUT);
  pinMode(channel_6, INPUT);

 

  Serial.begin(57600);
  Serial.print("Setup is complete! \n");
}

void loop() {
 
  rightStick = pulseIn(ch2_INPUT, HIGH, 100000); // converts RC signal to PWM
  leftStick = pulseIn(ch3_INPUT, HIGH, 100000);
 
  Serial.print(leftStick);
  Serial.print("\n");
 
}


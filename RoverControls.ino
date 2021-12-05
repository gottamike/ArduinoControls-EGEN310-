
// include libraries
#include <PS2X_lib.h>

// These are used to set the direction of the bridge driver.
#define ENA 3      //ENA
#define MOTORA_1 4 //IN3
#define MOTORA_2 5 //IN4
#define MOTORB_1 8 //IN1
#define MOTORB_2 7 //IN2
#define ENB 6      //ENB

PS2X ps2x; // create PS2 Controller Class

//right now, the library does NOT support hot pluggable controllers, meaning 
//you must always either restart your Arduino after you conect the controller, 
//or call config_gamepad(pins) again after connecting the controller.
int error = 0; 
byte type = 0;
byte vibrate = 0;

void setup(){

 // Configure output pins
 pinMode(ENA, OUTPUT);
 pinMode(MOTORA_1, OUTPUT);
 pinMode(MOTORA_2, OUTPUT);
 pinMode(ENB, OUTPUT);
 pinMode(MOTORB_1, OUTPUT);
 pinMode(MOTORB_2, OUTPUT);

 // Disable both motors
 digitalWrite(ENA,0);
 digitalWrite(ENB,0);

 // Start serial communication
 Serial.begin(57600);
  
 error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
}

// Main loop
void loop(){
   
 if(error == 1) //skip loop if no controller found
  return; 
  
 else { //DualShock Controller
  
    ps2x.read_gamepad(false, vibrate); // disable vibration of the controller
     
     // all ahead full Captain! (move forward)
     if(ps2x.Button(PSB_BLUE)) {
        digitalWrite(MOTORA_1,LOW);
        digitalWrite(MOTORA_2,HIGH);
        digitalWrite(MOTORB_1,HIGH);
        digitalWrite(MOTORB_2,LOW);
        analogWrite(ENB, 1023);
        analogWrite(ENA, 1023);
      }

      //all ahead slow Captain! (move forward slowly)
      if(ps2x.Button(PSB_PINK)) {
        digitalWrite(MOTORA_1,LOW);
        digitalWrite(MOTORA_2,HIGH);
        digitalWrite(MOTORB_1,HIGH);
        digitalWrite(MOTORB_2,LOW);
        analogWrite(ENB, 950);
        analogWrite(ENA, 950);
      }

      // full astern captain! (move rearward)
      if(ps2x.Button(PSB_RED)){
        digitalWrite(MOTORA_1,HIGH);
        digitalWrite(MOTORA_2,LOW);
        digitalWrite(MOTORB_1,LOW);
        digitalWrite(MOTORB_2,HIGH);
        analogWrite(ENB, 1023);
        analogWrite(ENA, 1023);         
        Serial.println("Move back");
      }  
      
      // Hard a starboard captain! (move right)
      if(ps2x.Button(PSB_R1)){
        digitalWrite(MOTORA_1,HIGH);
        digitalWrite(MOTORA_2,LOW);
        digitalWrite(MOTORB_1,HIGH);
        digitalWrite(MOTORB_2,LOW);
        analogWrite(ENB, 1023);
        analogWrite(ENA, 1023);
        Serial.println("Turn right");
      }

      //Half to starboard captain! (move right slowly)
      if(ps2x.Button(PSB_R2)){
        digitalWrite(MOTORA_1,HIGH);
        digitalWrite(MOTORA_2,LOW);
        digitalWrite(MOTORB_1,HIGH);
        digitalWrite(MOTORB_2,LOW);
        analogWrite(ENB, 1000);
        analogWrite(ENA, 1000);
        Serial.println("Turn right");
      }
      // Hard to port captain! (move left)
      if(ps2x.Button(PSB_L1)){
        digitalWrite(MOTORA_1,LOW);
        digitalWrite(MOTORA_2,HIGH);
        digitalWrite(MOTORB_1,LOW);
        digitalWrite(MOTORB_2,HIGH);
        analogWrite(ENB, 1023);
        analogWrite(ENA, 1023);
        Serial.println("Turn left");
      }

      // Half to port Captain! (move left slowly)
      if(ps2x.Button(PSB_L2)){
        digitalWrite(MOTORA_1,LOW);
        digitalWrite(MOTORA_2,HIGH);
        digitalWrite(MOTORB_1,LOW);
        digitalWrite(MOTORB_2,HIGH);
        analogWrite(ENB, 1000);
        analogWrite(ENA, 1000);
        Serial.println("Turn left");
      }
      
      // this if statement keeps the machine from running constantly if I press a button. It serves as a kill switch
      if (!ps2x.Button(PSB_RED) && !ps2x.Button(PSB_BLUE) && !ps2x.Button(PSB_R1) && !ps2x.Button(PSB_L1) && !ps2x.Button(PSB_PINK) && !ps2x.Button(PSB_L2) && !ps2x.Button(PSB_R2)) {
        analogWrite(ENB, 0);
        analogWrite(ENA, 0);
      }
          
 delay(50);
 }    
}

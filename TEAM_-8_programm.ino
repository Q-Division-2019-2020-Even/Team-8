#include "Arduino.h"
#include "DCMDriverL298.h"
#include "Servo.h"
#include "StepperMotor.h"

//TEAM-EIGHT(8)
// Pin Definitions
#define DCMOTORDRIVERL298_PIN_INT1  4
#define DCMOTORDRIVERL298_PIN_ENB 3
#define DCMOTORDRIVERL298_PIN_INT2  5
#define DCMOTORDRIVERL298_PIN_ENA 2
#define DCMOTORDRIVERL298_PIN_INT3  6
#define DCMOTORDRIVERL298_PIN_INT4  7
#define SERVO360MICRO_PIN_SIG 8
#define STEPPERGEARED_1_PIN_STEP  10
#define STEPPERGEARED_1_PIN_DIR 9
#define STEPPERGEARED_2_PIN_STEP  12
#define STEPPERGEARED_2_PIN_DIR 11



// Global variables and defines
#define stepperGeared_1DelayTime  1000
#define stepperGeared_2DelayTime  1000
// object initialization
DCMDriverL298 dcMotorDriverL298(DCMOTORDRIVERL298_PIN_ENA,DCMOTORDRIVERL298_PIN_INT1,DCMOTORDRIVERL298_PIN_INT2,DCMOTORDRIVERL298_PIN_ENB,DCMOTORDRIVERL298_PIN_INT3,DCMOTORDRIVERL298_PIN_INT4);
Servo servo360Micro;
StepperMotor stepperGeared_1(STEPPERGEARED_1_PIN_STEP,STEPPERGEARED_1_PIN_DIR);
StepperMotor stepperGeared_2(STEPPERGEARED_2_PIN_STEP,STEPPERGEARED_2_PIN_DIR);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    // enable the stepper motor, use .disable() to disable the motor
    stepperGeared_1.enable();
    // set stepper motor speed by changing the delay value, the higher the delay the slower the motor will turn
    stepperGeared_1.setStepDelay(stepperGeared_1DelayTime);
    // enable the stepper motor, use .disable() to disable the motor
    stepperGeared_2.enable();
    // set stepper motor speed by changing the delay value, the higher the delay the slower the motor will turn
    stepperGeared_2.setStepDelay(stepperGeared_2DelayTime);
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // L298N Motor Driver with Dual Hobby DC motors - Test Code
    //Start both motors. note that rotation direction is determined by the motors connection to the driver.
    //You can change the speed by setting a value between 0-255, and set the direction by changing between 1 and 0.
    dcMotorDriverL298.setMotorA(200,1);
    dcMotorDriverL298.setMotorB(200,0);
    delay(2000);
    //Stop both motors
    dcMotorDriverL298.stopMotors();
    delay(2000);

    }
    else if(menuOption == '2') {
    // Continuous Rotation Micro Servo - FS90R - Test Code
    // The servo will rotate CW in full speed, CCW in full speed, and will stop  with an interval of 2000 milliseconds (2 seconds) 
    servo360Micro.attach(SERVO360MICRO_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servo360Micro.write(180);  // 2. turns servo CW in full speed. change the value in the brackets (180) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 3. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro.write(0);    // 4. turns servo CCW in full speed. change the value in the brackets (0) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 5. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro.write(90);    // 6. sending 90 stops the servo 
    delay(2000);                              // 7. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro.detach();                    // 8. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    }
    else if(menuOption == '3') {
    // Small Reduction Stepper Motor with EasyDriver - 5VDC 32-Step 1/16 Gearing #1 - Test Code
    // the higher the time value the slower the motor will run
    stepperGeared_1.step(1, 1000);  // move motor 1000 steps in one direction
    delay(1000);            // short stop
    stepperGeared_1.step(0, 1000);  // move motor 1000 steps in the other dirction
    delay(1000);            //short stop
    }
    else if(menuOption == '4') {
    // Small Reduction Stepper Motor with EasyDriver - 5VDC 32-Step 1/16 Gearing #2 - Test Code
    // the higher the time value the slower the motor will run
    stepperGeared_2.step(1, 1000);  // move motor 1000 steps in one direction
    delay(1000);            // short stop
    stepperGeared_2.step(0, 1000);  // move motor 1000 steps in the other dirction
    delay(1000);            //short stop
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) L298N Motor Driver with Dual Hobby DC motors"));
    Serial.println(F("(2) Continuous Rotation Micro Servo - FS90R"));
    Serial.println(F("(3) Small Reduction Stepper Motor with EasyDriver - 5VDC 32-Step 1/16 Gearing #1"));
    Serial.println(F("(4) Small Reduction Stepper Motor with EasyDriver - 5VDC 32-Step 1/16 Gearing #2"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing L298N Motor Driver with Dual Hobby DC motors"));
        else if(c == '2') 
          Serial.println(F("Now Testing Continuous Rotation Micro Servo - FS90R"));
        else if(c == '3') 
          Serial.println(F("Now Testing Small Reduction Stepper Motor with EasyDriver - 5VDC 32-Step 1/16 Gearing #1"));
        else if(c == '4') 
          Serial.println(F("Now Testing Small Reduction Stepper Motor with EasyDriver - 5VDC 32-Step 1/16 Gearing #2"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}

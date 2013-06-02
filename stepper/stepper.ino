/*
 * MotorKnob
 *
 * A stepper motor follows the turns of a potentiometer
 * (or other sensor) on analog input 0.
 *
 * http://www.arduino.cc/en/Reference/Stepper
 * This example code is in the public domain.
 */

#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 48

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
//--Stepper stepper(STEPS, 8, 10, 9, 11);
Stepper stepper(STEPS, 8, 10, 9, 11);
/*
Stepper stepper2(STEPS, 8, 10, 11, 9);
Stepper stepper3(STEPS, 10, 8, 11, 9);
Stepper stepper3(STEPS, 10, 8, 9, 11);
Stepper stepper = stepper1;
*/
//--Stepper stepper(STEPS, 8, 10, 9, 11);
//Stepper stepper(STEPS, 8, 10, 9, 11);

void setup()
{
  // set the speed of the motor to 30 RPMs

  Serial.begin(9600);
}

int last_read = LOW;
int stepping = 0;

void loop()
{

  // move a number of steps equal to the change in the
  // sensor reading
  int tmp_read = digitalRead(12);
  if(tmp_read == HIGH && last_read != HIGH) {
    stepping = !stepping;
    Serial.print("Stepping ");
    Serial.print(stepping ? "HIGH" : "LOW");
    Serial.print("\n");
    Serial.flush();
  }
  last_read = tmp_read;
  
  if(stepping) {
   // Look at dip switches to determine which stepper 
   // settings to use
    int pin1, pin2, pin3, pin4;
    if(digitalRead(2)) {
      pin1 = 8; pin2 = 10;
    } else {
      pin1 = 10; pin2 = 8;
    }
    if(digitalRead(3)) {
      pin3 = 9; pin4 = 11;
    } else {
      pin3 = 11; pin4 = 9;
    }
    if(digitalRead(4)) {
      stepper = Stepper(STEPS, pin1, pin2, pin3, pin4);
    } else {
      stepper = Stepper(STEPS, pin3, pin4, pin1, pin2);
    }
    stepper.setSpeed(120);    
    stepper.step(48);
  }
}


// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
//--Stepper stepper(STEPS, 8, 10, 9, 11);


void wave_drive(int phase) 
{
  switch(phase % 4) {
    case 0:
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      break;
    case 1:
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      break;
    case 2:
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      break;
    case 3:
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, HIGH);
      break;
  }
}
void step_drive(int phase)
{
  switch(phase % 4) {
    case 0:
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
      digitalWrite(pin3, HIGH);
      break;
    case 1:
      digitalWrite(pin1, HIGH);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, LOW);
      break;
    case 2:
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      break;
    case 3:
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, LOW);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, HIGH);
      break;
  }
}

void setup()
{
  Serial.begin(9600);
}

int last_read = LOW;
int stepping = 0;
int phase = 0;
int pin1, pin2, pin3, pin4;

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

    if(digitalRead(5)) {
      wave_drive(phase);
    } else {
      step_drive(phase);
    }
    phase++;
  }
}

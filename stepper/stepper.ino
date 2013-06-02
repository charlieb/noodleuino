
// create an instance of the stepper class, specifying
// the number of steps of the motor and the vars it's
// attached to
//--Stepper stepper(STEPS, 8, 10, 9, 11);

int var1, var2, var3, var4;

void wave_drive(int phase) 
{
  switch(phase % 4) {
    case 0:
      digitalWrite(var1, HIGH);
      digitalWrite(var2, LOW);
      digitalWrite(var3, LOW);
      digitalWrite(var4, LOW);
      break;
    case 1:
      digitalWrite(var1, LOW);
      digitalWrite(var2, HIGH);
      digitalWrite(var3, LOW);
      digitalWrite(var4, LOW);
      break;
    case 2:
      digitalWrite(var1, LOW);
      digitalWrite(var2, LOW);
      digitalWrite(var3, HIGH);
      digitalWrite(var4, LOW);
      break;
    case 3:
      digitalWrite(var1, LOW);
      digitalWrite(var2, LOW);
      digitalWrite(var3, LOW);
      digitalWrite(var4, HIGH);
      break;
  }
}
void step_drive(int phase)
{
  switch(phase % 4) {
    case 0:
      digitalWrite(var1, HIGH);
      digitalWrite(var2, LOW);
      digitalWrite(var3, LOW);
      digitalWrite(var3, HIGH);
      break;
    case 1:
      digitalWrite(var1, HIGH);
      digitalWrite(var2, HIGH);
      digitalWrite(var3, LOW);
      digitalWrite(var4, LOW);
      break;
    case 2:
      digitalWrite(var1, LOW);
      digitalWrite(var2, HIGH);
      digitalWrite(var3, HIGH);
      digitalWrite(var4, LOW);
      break;
    case 3:
      digitalWrite(var1, LOW);
      digitalWrite(var2, LOW);
      digitalWrite(var3, HIGH);
      digitalWrite(var4, HIGH);
      break;
  }
}


int last_read = LOW;
int stepping = 0;
int phase = 0;
int pin1, pin2, pin3, pin4;
int out1, out2, out3, out4;

void setup()
{
  Serial.begin(9600);
  out1 = pin1 = var1 = 8;
  out2 = pin2 = var2 = 10;
  out3 = pin3 = var3 = 9;
  out4 = pin4 = var4 = 11;
}

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
      out1 = pin1; out2 = pin2;
    } else {
      out1 = pin2; out2 = pin1;
    }
    if(digitalRead(3)) {
      out3 = pin3; out4 = pin4;
    } else {
      out3 = pin4; out4 = pin3;
    }
    if(digitalRead(4)) {
      var1 = out1;
      var2 = out2;
      var3 = out3;
      var4 = out4;
    } else {
      var1 = out3;
      var2 = out4;
      var3 = out1;
      var4 = out2;
    }

    if(digitalRead(5)) {
      wave_drive(phase);
    } else {
      step_drive(phase);
    }
    phase++;
  }
}


// create an instance of the stepper class, specifying
// the number of steps of the motor and the vars it's
// attached to
//--Stepper stepper(STEPS, 8, 10, 9, 11);

int var1, var2, var3, var4;

void wave_drive(int phase) 
{
  switch(phase % 4) {
    case 0:
      Serial.println("0");
      digitalWrite(var1, LOW);
      digitalWrite(var2, HIGH);
      digitalWrite(var3, HIGH);
      digitalWrite(var4, HIGH);
      break;
    case 1:
      Serial.println("1");
      digitalWrite(var1, HIGH);
      digitalWrite(var2, LOW);
      digitalWrite(var3, HIGH);
      digitalWrite(var4, HIGH);
     
      break;
    case 2:
       Serial.println("2");
      digitalWrite(var1, HIGH);
      digitalWrite(var2, HIGH);
      digitalWrite(var3, LOW);
      digitalWrite(var4, HIGH);
      break;
    case 3:
      Serial.println("3");
      digitalWrite(var1, HIGH);
      digitalWrite(var2, HIGH);
      digitalWrite(var3, HIGH);
      digitalWrite(var4, LOW);
      break;
  }
}
void step_drive(int phase)
{
  switch(phase % 4) {
    case 0:
      //Serial.println("0");
      digitalWrite(var1, HIGH);
      digitalWrite(var2, LOW);
      digitalWrite(var3, HIGH);
      digitalWrite(var4, LOW);
      break;
    case 1:
      //Serial.println("1");
      digitalWrite(var1, LOW);
      digitalWrite(var2, HIGH);
      digitalWrite(var3, HIGH);
      digitalWrite(var4, LOW);
      break;
    case 2:
      //Serial.println("2");
      digitalWrite(var1, LOW);
      digitalWrite(var2, HIGH);
      digitalWrite(var3, LOW);
      digitalWrite(var4, HIGH);
      break;
    case 3:
      //Serial.println("3");    
      digitalWrite(var1, HIGH);
      digitalWrite(var2, LOW);
      digitalWrite(var3, LOW);
      digitalWrite(var4, HIGH);
      break;
  }
}


int last_read = LOW;
int stepping = 0;
int phase = 0;
int pin1, pin2, pin3, pin4;
int out1, out2, out3, out4;

int combo = 0;

void setup()
{
  Serial.begin(9600);
  out1 = pin1 = var1 = 8;
  out2 = pin2 = var2 = 9;
  out3 = pin3 = var3 = 10;
  out4 = pin4 = var4 = 11;
  
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
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
    if(phase % 100 == 0) {
      if(combo % 2 == 0) {
        out1 = pin1; out2 = pin2;
      } else {
        out1 = pin2; out2 = pin1;
      }
      if(combo % 4 ==0) {
        out3 = pin3; out4 = pin4;
      } else {
        out3 = pin4; out4 = pin3;
      }
      if(combo % 8 == 0) {
        var1 = out1;
        var2 = out2;
        var3 = out3;
        var4 = out4;
      } else {
        var1 = out1;
        var2 = out3;
        var3 = out4;
        var4 = out2;
      }
      Serial.print(var1);
      Serial.print(" ");
      Serial.print(var2);
      Serial.print(" ");
      Serial.print(var3);
      Serial.print(" ");
      Serial.println(var4);
    }

    /*

    if(!digitalRead(5)) {
      wave_drive(phase);
      Serial.println("Wave");
    } else {
      step_drive(phase);
      Serial.println("Step");
    }
    */
    //wave_drive(phase);
    step_drive(phase);
    /*
    switch(phase) {
      case 0: phase = 1; break;
      case 1: phase = 3; break;
      case 2: phase = 0; break;
      case 3: phase = 2; break;
    }
    */
    phase++;
    //delay(500);
  } else { // not stepping 
    digitalWrite(var1, HIGH);
    digitalWrite(var2, HIGH);
    digitalWrite(var3, HIGH);
    digitalWrite(var4, HIGH);
  }
}


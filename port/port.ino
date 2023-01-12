const int pin0 = 13;

const int pin1 = 11;
const int pin2 = 10;
const int pin3 = 9;

int value;
int increment = 0;

void setup() {
  pinMode(pin0,OUTPUT);
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  
  // analogWrite(pin1,255);

  // char buffer[] = {' ',' ',' '}; // Receive up to 7 bytes
  // while (!Serial.available()); // Wait for characters
  // Serial.readBytesUntil('\n', buffer, 3);
  // int value = atoi(buffer);
  // analogWrite(pin1,value);

  // digitalWrite(pin0,HIGH);

  if (Serial.available()) {
    value = Serial.read();
    analogWrite(pin1,value);
    analogWrite(pin2,value);
    analogWrite(pin3,value);

    digitalWrite(pin0,value > 4 ? HIGH : LOW);
    
    // digitalWrite(pin1,value);
  }

  // Serial.print(increment);
  // increment = increment + 1;
  // delay(1000);
}

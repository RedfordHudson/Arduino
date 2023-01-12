int LED_pin = 13;
int toggle = 0;
// int port = 115200;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin,HIGH);
  // Serial.print('test');
}

void loop()
{
  // toggle = 1 - toggle;
  // // Serial.println(Serial.available());
  // Serial.println(toggle);
  // digitalWrite(LED_pin, toggle ? HIGH : LOW);
  // delay(2000);

  // if (Serial.available()) {
  //   int value1 = Serial.read();
  //   Serial.println(value1);
  //   if(value1 == 1){
  //     digitalWrite(LED_pin, HIGH);
  //   }
  //   else if (value1 == 0){
  //     digitalWrite(LED_pin, LOW);
  //   }
    
  // }
}
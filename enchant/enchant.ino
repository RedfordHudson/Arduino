char assembledBytes[17];

const byte dimensions = 3;
int values[dimensions];

void setup() {
  Serial.begin(9600);

  // pinMode(11,OUTPUT);
  // pinMode(10,OUTPUT);
  // pinMode(9,OUTPUT);

  // digitalWrite(11,LOW);
  // digitalWrite(10,LOW);
  // digitalWrite(9,HIGH);
}

void loop() {
  Serial.print(Serial.available());
  
  if (Serial.available()) {
    Serial.println("running");
    assembleBytes();
    Serial.println("*");
    processBytes();
    // assignValues();
    printValues();
  }
}

void assignValues() {
  analogWrite(11,values[0]);
  analogWrite(10,values[1]);
  analogWrite(9,values[2]);
}

void printValues() {
  Serial.print("values:");

  for (unsigned int i = 0; i < dimensions; i++) {
    Serial.print(" " + String(values[i]));
  }

  Serial.println();
}

void processBytes() {
  unsigned int currentByte;
  unsigned int value = 0,
                bufferIndex = 0,
                valueIndex = 0;

  while (valueIndex < dimensions) {
    currentByte = assembledBytes[bufferIndex];

    if (currentByte == 32 || currentByte == '\0') {
      // Serial.println("capturing value: " + String(value));
      values[valueIndex] = value;
      valueIndex++;
      value = 0;
    } else {
      value = value*10 + (currentByte - '0');
    }

    if (currentByte == '\0') {
      // Serial.println("breaking");
      break;
    }

    bufferIndex++;
  }
}

void assembleBytes() {
  // Serial.println("reading buffer");
  int i = Serial.readBytesUntil('\n', assembledBytes, sizeof(assembledBytes) - 1);
  assembledBytes[i] = '\0';
  // Serial.println("cutting buffer at index: " + String(i));
}
char assembledBytes[17];

const byte dimensions = 3;
int values[dimensions];

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Serial.print(Serial.available());
  
  if (Serial.available()) {
    // Serial.println("running");
    assembleBytes();
    Serial.println("*");
    processBytes();
    printValues();
  }
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

void loadValues() {
  // my unsuccessful attempt at readBytesUntil()

  int i = 0;
  int currentByte;

  // oddly, the correct values are ONLY returned if all three Serial.println statements are included

  while (Serial.available()) {
    Serial.println("queue length -> " + String(Serial.available()));

    currentByte = Serial.read();
    Serial.println("value -> " + String(currentByte));
    
    if (currentByte == (13||10) || i >= dimensions) {
      // Serial.println("breaking");
      break;
    }
    if (currentByte == 32) continue;
    
    Serial.println("index: " + String(i));
    // values[i] = currentByte;
    i++;
  }
}
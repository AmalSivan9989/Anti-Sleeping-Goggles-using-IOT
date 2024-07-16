const int eyeBlinkPin = 10; // Eye blink sensor pin
const int buzzerPin = 9;    // Buzzer pin
const int threshold = 3000;  // Threshold for open eyes (5 seconds)

void setup() {
  pinMode(eyeBlinkPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  // Check if eyes are open
  if (digitalRead(eyeBlinkPin) == HIGH) {
    // Eyes are open, start counting
    int openTime = 0;
    while (openTime < threshold) {
      delay(100); // Wait for 100 milliseconds
      if (digitalRead(eyeBlinkPin) == LOW) {
        // Eyes closed before 5 seconds, reset the timer
        openTime = 0;
        break; // Exit the loop if eyes close
      } else {
        openTime += 100; // Increment timer
      }
    }
    
    // Activate the buzzer if eyes remain open for 5 seconds
    if (openTime >= threshold) {
      digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
      Serial.println("Eyes closed! WAKEUP! Buzzer activated!");
      Serial.println(); // Print an empty line for gap
      delay(1000); // Buzzer duration (1 second)
      digitalWrite(buzzerPin, LOW); // Turn off the buzzer
    }
  }
  else {
    // Eyes are closed, print a message
    Serial.println("Eyes are open!");
    Serial.println(); // Print an empty line for gap
    delay(500); // Add a delay to avoid continuous printing
  }
}

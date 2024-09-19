#define TRIG_PIN 41  // Trigger pin for HC-SR04
#define ECHO_PIN 42  // Echo pin for HC-SR04

// Variables for calibration
float calibration_factor = 1.05;  // Adjust this factor based on real-world measurements

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float measureDistance() {
  // Send a 10us pulse to the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the time for the echo pulse
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm (speed of sound is 343m/s)
  float distance = (duration * 0.034) / 2;

  // Apply calibration factor
  distance *= calibration_factor;

  return distance;
}

void loop() {
  float distance = measureDistance();
  
  Serial.print("Measured Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000);  // Delay 1 second between measurements
}

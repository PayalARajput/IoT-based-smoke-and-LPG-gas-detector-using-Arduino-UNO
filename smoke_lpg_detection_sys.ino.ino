/*
  Field Project: IoT-Based Smart LPG Gas & Smoke Detection System
  Target Hardware: Arduino Uno R3
  Sensors: MQ-2 Gas/Smoke Sensor
  Peripherals: Dual LEDs, Piezo Buzzer
*/

const int sensorPin   = A0; // MQ-2 Analog Output connected to A0
const int buzzerPin   = 8;  // Piezo Buzzer connected to Digital Pin 8
const int redLedPin   = 7;  // Red Alert LED connected to Digital Pin 7
const int greenLedPin = 6;  // Green Safe LED connected to Digital Pin 6

// Calibrated Threshold Value (Range: 0 - 1023)
const int threshold   = 250; 

void setup() {
  // Initialize Serial Telemetry
  
  Serial.begin(9600);
  
  // Pin Mode Configurations
  pinMode(sensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);

  // Initial State Setup
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(redLedPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  // Read analog voltage from MQ-2 sensor
  int sensorValue = analogRead(sensorPin);
  
  // Output telemetric data to Serial Monitor
  Serial.print("MQ-2 Sensor Value: ");
  Serial.println(sensorValue);

  // Threshold Logic Evaluation
  if (sensorValue > threshold) {
    // HAZARD DETECTED: Deactivate Safe LED, activate alert pattern
    digitalWrite(greenLedPin, LOW);
    
    // Pulse Cycle Phase 1: Alarm ON
    digitalWrite(redLedPin, HIGH);
    tone(buzzerPin, 1000); 
    delay(150);            

    // Pulse Cycle Phase 2: Alarm OFF
    digitalWrite(redLedPin, LOW);
    noTone(buzzerPin);
    digitalWrite(buzzerPin, LOW); 
    delay(150);            


  } else {
    // NORMAL STATE: Maintain Safe Status
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, HIGH);
    noTone(buzzerPin);
    digitalWrite(buzzerPin, LOW);
    
    // Sampling Interval
    delay(500); 
  }
}

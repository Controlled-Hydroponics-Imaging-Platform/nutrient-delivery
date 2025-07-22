/*
  CHIP & PRD hydroponic system
  SEN0549 Water Flow Sensor paired with Solenoid Valve
  2025-07-18
  Alice Liang
*/

// Flow sensor variables
volatile unsigned int pulseCount = 0;
float flowRate_L_per_h = 0;
float totalLiters = 0;
float pulsesPerLiter = 540.0; // Default, will be updated by calibration
float wantedLiters = 0;

// Timing
unsigned long lastUpdateTime = 0;
const unsigned long interval = 1000;  // in ms

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(3), pulse, RISING);
  pinMode(12,OUTPUT); // RELAY PIN   
  digitalWrite(12,HIGH); // Normally OFF Only For Chanies Relay Module
  Serial.println("Ready, Set, Grow!");

  delay(2000); 

  // Calibration Method
  Serial.println("Press any key to start calibration...");
  while (!Serial.available());  // wait for key press
  Serial.read(); // clear input

  pulseCount = 0;
  Serial.println("Start calibration: Let exactly 1L of water flow... Manually turn off water right after.");
  digitalWrite(12,LOW); //relay ON
  delay(20000);  // wait 20 seconds while user pours water

  noInterrupts();
  unsigned int pulsesMeasured = pulseCount;
  interrupts();

  pulsesPerLiter = pulsesMeasured / 1.0; // assumes 1 liter flowed
  Serial.print("Calibration complete. New pulsesPerLiter = ");
  Serial.println(pulsesPerLiter);

  Serial.println("Enter how many liters of water you would like to be sent to the tank, Press ENTER");
  while (Serial.available() == 0) ;    
  wantedLiters = Serial.parseFloat();
  Serial.println("Please turn on water manually. Solenoid valve is still open.");
  delay(1000); // pause before loop (could add testing script)
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= interval) {
    noInterrupts();
    unsigned int count = pulseCount;
    pulseCount = 0;
    interrupts();

    // Convert pulses to liters in 1 second
    float flow_L_per_s = count / pulsesPerLiter;
    totalLiters += flow_L_per_s;

    // Convert to L/h
    flowRate_L_per_h = flow_L_per_s * 3600.0;

    // Output
    Serial.print("Flow rate: ");
    Serial.print(flow_L_per_s, 3);
    Serial.print(" L/s\t");

    Serial.print("Flow rate: ");
    Serial.print(flowRate_L_per_h, 2);
    Serial.print(" L/h\t");

    Serial.print("Total consumed: ");
    Serial.print(totalLiters, 3);
    Serial.println(" L");

    lastUpdateTime = currentTime;
  }

  sendLiters(wantedLiters); // check if enough water is sent

}

void pulse() {
  pulseCount++;
}
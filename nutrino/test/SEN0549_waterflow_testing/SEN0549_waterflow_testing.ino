/*
  CHIP & PRD hydroponic system
  SEN0549 Water Flow Sensor to measure flow rate in hydroponic system water tank
  help from chat
  2025-06-03
  Alice Liang
  total water volume that has passed through flow sensor since turned on (L) AND flow rate (L/h) 
*/

// Flow sensor variables
volatile unsigned int pulseCount = 0;
float flowRate_L_per_h = 0;
float totalLiters = 0;

// Timing
unsigned long lastUpdateTime = 0;
const unsigned long interval = 1000;  // in ms (update every 1 second)

// Flow sensor settings
const float pulsesPerLiter = 540.0;

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(3), pulse, RISING);  // Flow sensor on pin 3
  Serial.println("Ready, Set, Grow!");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastUpdateTime >= interval) {
    noInterrupts(); // pause counting
    unsigned int count = pulseCount;
    pulseCount = 0;
    interrupts();

    // Convert pulses to liters in 1 second
    float flow_L_per_s = count / pulsesPerLiter;
    totalLiters += flow_L_per_s;

    // Convert to L/h (liters/hour)
    flowRate_L_per_h = flow_L_per_s * 3600.0;

    // Output
    Serial.print("Flow rate: ");
    Serial.print(flow_L_per_s, 2);
    Serial.print(" L/s\t");

    Serial.print("Flow rate: ");
    Serial.print(flowRate_L_per_h, 2);
    Serial.print(" L/h\t");

    Serial.print("Total consumed: ");
    Serial.print(totalLiters, 3);
    Serial.println(" L");

    lastUpdateTime = currentTime;
  }
}

// Interrupt service routine
void pulse() {
  pulseCount++;
}

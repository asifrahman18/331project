// Output LED pin variables
int O0LED = 10; // O0 LED connected to pin 10
int O1LED = 11; // O1 LED connected to pin 11
int O2LED = 12; // O2 LED connected to pin 12
int O3LED = 13; // O3 LED connected to pin 13

// Input switch pin variables
int I0Switch = 5; // Switch O0 connected to pin 5
int I1Switch = 4; // Switch O1 connected to pin 4
int I2Switch = 3; // Switch O2 connected to pin 3
int I3Switch = 2; // Switch O3 connected to pin 2

// Define constants for LED states
const boolean LED_ON = HIGH;
const boolean LED_OFF = LOW;

void setup() {
  // Set switch pins as inputs
  pinMode(I0Switch, INPUT);
  pinMode(I1Switch, INPUT);
  pinMode(I2Switch, INPUT);
  pinMode(I3Switch, INPUT);

  // Set LED pins as outputs
  pinMode(O0LED, OUTPUT);
  pinMode(O1LED, OUTPUT);
  pinMode(O2LED, OUTPUT);
  pinMode(O3LED, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  unsigned long startTime = millis();

  // Read switch states
  boolean I0State = digitalRead(I0Switch);
  boolean I1State = digitalRead(I1Switch);
  boolean I2State = digitalRead(I2Switch);
  boolean I3State = digitalRead(I3Switch);

  // Calculate LED states using K-map equations
  boolean O0State = (!I0State & I1State & I3State) |
                    (I1State & !I1State & I3State) |
                    (I0State & !I2State & I1State) |
                    (!I3State & !I2State & !I1State & !I0State);

  boolean O1State = (I2State & !I0State) |
                    (!I3State & I1State) |
                    (!I0State & !I1State & I3State) |
                    (I0State & !I2State & I3State);

  boolean O2State = (!I3State & !I1State) |
                    (!I3State & I2State) |
                    (!I2State & !I1State & !I0State);

  boolean O3State = (!I3State & !I2State) |
                    (!I3State & I0State) |
                    (!I1State & I3State & !I0State) |
                    (I1State & I2State & I0State);

  // Update LEDs
  digitalWrite(O0LED, O0State);
  digitalWrite(O1LED, O1State);
  digitalWrite(O2LED, O2State);
  digitalWrite(O3LED, O3State);

  // Print LED states to the serial monitor
  Serial.print(O3State);
  Serial.print(O2State);
  Serial.print(O1State);
  Serial.println(O0State);

  unsigned long endTime = millis();
  Serial.print("Code Execution Time: ");
  Serial.print(endTime - startTime);
  Serial.println(" ms");
}
